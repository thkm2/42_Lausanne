#include "../incl/lib.hpp"
#include "../incl/SocketManager.hpp"
#include "../incl/RequestManager.hpp"

SocketManager::SocketManager(ServerConfig config) {
    _config = config;
    for (size_t i = 0; i < config.listens.size(); ++i)
    {
        for (size_t j = i + 1; j < config.listens.size(); ++j)
        {
            if (config.listens[i].port == config.listens[j].port)
            {
                std::cout << "Duplicate listen port" << std::endl;
                exit(1);
            }
        }
    }
    for (size_t i = 0; i < config.listens.size(); i++)
    {
        int port = config.listens[i].port;
        setupServerSocket(port);

        std::cout << "server listening on port " << port << std::endl;
    }
}

SocketManager::~SocketManager() {
    for (size_t i = 0; i < _fds.size(); i++)
        close(_fds[i].fd);
}

void SocketManager::setupServerSocket(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == -1)
        throw std::runtime_error("socket failed");
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        close(server_fd);
        throw std::runtime_error("bind failed");
    }
        
    
    if (listen(server_fd, SOMAXCONN) == -1)
    {
        close(server_fd);
        throw std::runtime_error("listen failed");
    }

    _server_fds.push_back(server_fd);

    struct pollfd server_poll;
    server_poll.fd = server_fd;
    server_poll.events = POLLIN;
    _fds.push_back(server_poll);
    _request_parts.push_back("");
    _last_activity.push_back(time(NULL));
}

void SocketManager::addClient(int client_fd) {
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    struct pollfd client_poll;
    client_poll.fd = client_fd;
    client_poll.events = POLLIN;
    client_poll.revents = 0;
    _fds.push_back(client_poll);
    _request_parts.push_back("");
    _last_activity.push_back(time(NULL));
}

void SocketManager::removeClient(size_t i) {
    close(_fds[i].fd);
    _fds.erase(_fds.begin() + i);
    _request_parts.erase(_request_parts.begin() + i);
    _last_activity.erase(_last_activity.begin() + i);
}

void SocketManager::handleNewConnection(int server_fd) {
    int client_fd = accept(server_fd, NULL, NULL);
    addClient(client_fd);
    std::cout << "[CONNECTION] New client connected: fd=" << client_fd << std::endl;
}

void SocketManager::handleClientData(int client_fd) {
    char buf[16];
    size_t i;
    for (i = _server_fds.size(); i < _fds.size(); i++)
        if (_fds[i].fd == client_fd)
            break;
    ssize_t r = 1;
    while (r > 0)
    {
        r = read(client_fd, buf, 15);
        if (r > 0)
            _request_parts[i].append(buf, r);
        _last_activity[i] = time(NULL);
        if (r == 0 || r == -1)
            break;
    }

    if (_request_parts[i].find("\r\n\r\n") == std::string::npos)
        return;
    size_t body_len = 0;
    if (_request_parts[i].find("Transfer-Encoding: chunked") != std::string::npos)
    {
        if (_request_parts[i].find("0\r\n\r\n") == std::string::npos)
            return;
        size_t body_start = _request_parts[i].find("\r\n\r\n") + 4;
        std::string raw_body = _request_parts[i].substr(body_start);
        std::string clean_body;

        size_t pos = 0;
        while (pos < raw_body.length()) {
            size_t line_end = raw_body.find("\r\n", pos);
            if (line_end == std::string::npos) break;

            std::string size_str = raw_body.substr(pos, line_end - pos);
            size_t chunk_size = strtoul(size_str.c_str(), NULL, 16);
            if (chunk_size == 0) break;

            pos = line_end + 2;
            clean_body += raw_body.substr(pos, chunk_size);
            pos += chunk_size + 2;
        }

        _request_parts[i] = _request_parts[i].substr(0, body_start) + clean_body;
        body_len = clean_body.length();

    }

    if (_request_parts[i].find("Content-Length: ") != std::string::npos && _request_parts[i].find("\r\n\r\n") != std::string::npos)
    {
        size_t cl = _request_parts[i].find("Content-Length: ") + 16;
        body_len = atoi(_request_parts[i].c_str() + cl);

        if (body_len > _config.clientMaxBodySize)
        {
            size_t first_line_end = _request_parts[i].find("\r\n");
            std::string first_line = _request_parts[i].substr(0, first_line_end);
            std::cout << "[REQUEST] " << first_line << std::endl;
            std::cout << "[RESPONSE] 413 for " << first_line << std::endl;
            std::string response = "HTTP/1.1 413 Payload Too Large\r\nContent-Length: 0\r\n\r\n";
            ssize_t val = write(client_fd, response.c_str(), response.size());
            if (val == 0 || val == -1 || val > 0)
            {
                for (size_t j = 1; j < _fds.size(); j++)
                {
                    if (_fds[j].fd == client_fd)
                    {
                        removeClient(j);
                        break;
                    }
                }
            }
            return;
        }
        
        size_t body_start = _request_parts[i].find("\r\n\r\n") + 4;
        if (_request_parts[i].size() - body_start < body_len)
            return;
    }
    std::string request = _request_parts[i];
    _request_parts[i].clear();

    size_t first_line_end = request.find("\r\n");
    std::string first_line = request.substr(0, first_line_end);
    std::cout << "[REQUEST] " << first_line << std::endl;

    RequestManager request_manager(request, _config, body_len);
    std::string response = request_manager.getResponse();
    
    size_t status_start = response.find(" ");
    size_t status_end = response.find(" ", status_start + 1);
    std::string status_code = response.substr(status_start + 1, status_end - status_start - 1);
    std::cout << "[RESPONSE] " << status_code << " for " << first_line << std::endl;

    ssize_t val = write(client_fd, response.c_str(), response.size());
    if (val == 0 || val == -1 || val > 0)
    {
        for (size_t i = 1; i < _fds.size(); i++)
        {
            if (_fds[i].fd == client_fd)
            {
                removeClient(i);
                break;
            }
        }
    }
}

void SocketManager::run(int& running) {
    while (running)
    {
        poll(&_fds[0], _fds.size(), 1000);
        
        if (!running)
            break;
        
        for (size_t i = _server_fds.size(); i < _fds.size(); i++)
        {
            if (time(NULL) - _last_activity[i] > 5)
                removeClient(i);
        }
        for (size_t i = 0; i < _fds.size(); i++)
        {
            if (_fds[i].revents & POLLIN)
            {
                bool is_server = false;
                for (size_t j = 0; j < _server_fds.size(); j++)
                {
                    if (_fds[i].fd == _server_fds[j])
                    {
                        handleNewConnection(_server_fds[j]);
                        is_server = true;
                        break;
                    }
                }
                if (!is_server)
                    handleClientData(_fds[i].fd);
            }
        }
    }
}