#include "../incl/lib.hpp"
#include "../incl/RequestManager.hpp"

RequestManager::RequestManager(std::string request, ServerConfig config, size_t content_len) {
    _config = config;
    _request = request;
    _content_len = content_len;
    _response = "";
    _method = "";
    _path = "";
    _content_type = "";
    _boundary = "";
    _version = "";
    _loc_i = 0;
    _media_type = "";
    _is_chunked = false;
    requestParser();
}

RequestManager::~RequestManager() {}

void RequestManager::requestParser() {

    if (Check4xx5xxErrors() == false)
        return;
    InitContentTypeAndBoundary();
    if (IsMethodAllow() == false)
        return;
    if (_config.locations[_loc_i].hasReturn)
    {
        buildRedirectResponse(_config.locations[_loc_i].returnCode, 
                             _config.locations[_loc_i].returnUrl);
        return;
    }
    if (_method == "GET")
        buildGETResponse();
    else if (_method == "POST")
        buildPOSTResponse();
    else if (_method == "DELETE")
        buildDELETEResponse();
    else
        buildErrorResponse(501, "Not Implemented");
}

bool RequestManager::Check4xx5xxErrors() {
    size_t pos = _request.find("\r\n");
    if (pos == std::string::npos)
    {
        buildErrorResponse(400, "Bad Request");
        return false;
    }
    
    std::string first_line = _request.substr(0, pos);
    std::stringstream ss(first_line);
    ss >> _method >> _path >> _version;
    
    if (_method.empty() || _path.empty() || _version.empty())
    {
        buildErrorResponse(400, "Bad Request");
        return false;
    }
    if (_version != "HTTP/1.0" && _version != "HTTP/1.1")
    {
        buildErrorResponse(505, "HTTP Version Not Supported");
        return false;
    }
    if (_path.length() > 8192) //8Ko (comme nginx)
    {
        buildErrorResponse(414, "URI Too Long");
        return false;
    }
    if (_version == "HTTP/1.1")
    {
        if (_request.find("Host: ") == std::string::npos)
        {
            buildErrorResponse(400, "Bad Request");
            return false;
        }
    }
    if (_request.find("\r\n\r\n") == std::string::npos || _request.find("\r\n\r\n") > 32768) // 32Ko (comme nginx)
    {
        buildErrorResponse(431, "Request Header Fields Too large");
        return false;
    }
    if (_content_len > _config.clientMaxBodySize)
    {
        buildErrorResponse(413, "Payload Too Large");
        return false;
    }
    return true;
}

void RequestManager::InitContentTypeAndBoundary() {
    size_t ct_pos = _request.find("Content-Type: ");
    if (ct_pos != std::string::npos)
    {
        ct_pos += 14;
        _media_type = _request.substr(ct_pos, 19);
        size_t ct_end = _request.find("\r\n", ct_pos);
        _content_type = _request.substr(ct_pos, ct_end - ct_pos);
        size_t b_pos = _content_type.find("boundary=");
        if (b_pos != std::string::npos)
            _boundary = "--" + _content_type.substr(b_pos + 9);
    }
}

bool RequestManager::IsMethodAllow() {
    int best_i = 0;
    size_t best_len = 0;

    for (size_t i = 0; i <  _config.locations.size(); i++)
    {
        std::string loc_path = _config.locations[i].path;
        std::string check_path = _path;
        
        // Gérer les slashes finaux : si la location a un slash final mais pas la requête
        // on ajoute temporairement un slash pour le matching
        if (loc_path.length() > 0 && loc_path[loc_path.length() - 1] == '/' &&
            (check_path.empty() || check_path[check_path.length() - 1] != '/'))
        {
            check_path += '/';
        }
        
        if (check_path.find(loc_path) == 0 && loc_path.length() > best_len)
        {
            best_len = loc_path.length();
            best_i = i;
        }
    }
    
    bool flag = false;
    for (size_t i = 0; i < _config.locations[best_i].allowedMethods.size(); i++)
    {
        if (_config.locations[best_i].allowedMethods[i] == _method)
        {   
            flag = true;
            break;
        }
    }
    _loc_i = best_i;
    if (flag == false)
    {
        buildErrorResponse(405, "Method Not Allowed");
        return false;
    }
    return true;
}

bool RequestManager::fileResponse(std::string full_path)
{
    struct stat info;
    if (stat(full_path.c_str(), &info) != 0)
    {
        buildErrorResponse(500, "Internal Server Error");
        return true;
    }

    if (S_ISREG(info.st_mode))
    {
        if (_method == "GET")
            buildOkResponse(full_path);
        return true;
    }
    return false;
}

bool RequestManager::dirResponse(std::string full_path)
{
    struct stat info;
    if (stat(full_path.c_str(), &info) != 0)
    {
        buildErrorResponse(500, "Internal Server Error");
        return true;
    }

    if (S_ISDIR(info.st_mode))
    {
        std::string path_index_html = full_path;
        if (path_index_html[path_index_html.length() - 1] != '/')
        {
            // Vérifier si la location se termine par '/' - si oui, ajouter le slash directement sans redirection
            std::string loc_path = _config.locations[_loc_i].path;
            if (loc_path.length() > 0 && loc_path[loc_path.length() - 1] == '/')
            {
                path_index_html += '/';
            }
            else
            {
                buildRedirectResponse(301);
                return true;
            }
        }
        
        // Utiliser l'index configuré pour cette location
        std::string index_file = "index.html"; // fallback par défaut
        if (!_config.locations[_loc_i].indexFiles.empty())
            index_file = _config.locations[_loc_i].indexFiles[0];
        path_index_html += index_file;

        struct stat i;
        if (stat(path_index_html.c_str(), &i) == 0 && S_ISREG(i.st_mode))
        {
            buildOkResponse(path_index_html);
            return true;
        }
        if (_config.locations[_loc_i].autoindex == true)
        {
            std::string listing = buildAutoIndexResponse(full_path, _path);
            _response = _version + " 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: " + itos(listing.length()) + "\r\n\r\n" +
                         listing;
            return true;

        }
        buildErrorResponse(404, "Not Found");
        return true;
    }
    return false;
}

void RequestManager::buildOkResponse(std::string file_path)
{
    std::ifstream file(file_path.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        buildErrorResponse(500, "Internal Server Error");
        return;
    }
    std::string content_type = getResponseContentType(file_path);
    std::string body;
    char c;
    while (file.get(c))
        body += c;
    _response = _version + " 200 OK\r\n"
                "Content-Type: " + content_type + "\r\n"
                "Content-Length: " + itos(body.length()) + "\r\n\r\n" + body;
    return;
}

void RequestManager::buildGETResponse()
{
    // pour le cgi
    std::string path_without_query = _path;
    size_t query_pos = _path.find('?');
    if (query_pos != std::string::npos) {
        path_without_query = _path.substr(0, query_pos);
    }

    std::string full_path = _config.locations[_loc_i].root + path_without_query.substr(_config.locations[_loc_i].path.length() - 1); //dsl pour la ligne de salopard

    if (access(full_path.c_str(), F_OK) == -1)
    {
        buildErrorResponse(404, "Not Found");
        return;
    }
    if (access(full_path.c_str(), R_OK) == -1)
    {
        buildErrorResponse(403, "Forbidden");
        return;
    }
    
    if (isCGI(full_path))
    {
        executeCGI(full_path);
        return;
    }
    
    if (fileResponse(full_path) == true)
        return;
    if (dirResponse(full_path) == true)
        return;

    buildErrorResponse(404, "Not Found");
}

void RequestManager::buildRedirectResponse(int code, std::string url)
{
    std::string redirect_url;
    if (url.empty())
        redirect_url = _path + "/";
    else
        redirect_url = url;
    
    std::string status_msg;
    if (code == 301)
        status_msg = "Moved Permanently";
    else if (code == 302)
        status_msg = "Found";
    else if (code == 303)
        status_msg = "See Other";
    else if (code == 307)
        status_msg = "Temporary Redirect";
    else if (code == 308)
        status_msg = "Permanent Redirect";
    else
        status_msg = "Redirect";
    
    std::string body = "<h1>" + itos(code) + " " + status_msg + " to: " + redirect_url + "</h1>";
    _response = _version + " " + itos(code) + " " + status_msg + "\r\n"
                "Location: " + redirect_url + "\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: " + itos(body.length()) + "\r\n"
                "\r\n" + body;
}

std::string RequestManager::getResponseContentType(std::string full_path)
{
    std::string ext = full_path.substr(full_path.rfind('.'));
    if (ext == ".html" || ext == ".htm")
        return "text/html";
    else if (ext == ".css") 
        return "text/css";
    else if (ext == ".js")  
        return "application/javascript";
    else if (ext == ".png") 
        return "image/png";
    else if (ext == ".jpg" || ext == ".jpeg")
        return "image/jpeg";
    else if (ext == ".gif") 
        return "image/gif";
    else if (ext == ".txt") 
        return "text/plain";
    else if (ext == ".pdf") 
        return "application/pdf";

    return "application/octet-stream";
}

void RequestManager::buildDELETEResponse() {

    std::string full_path = _config.locations[_loc_i].root + _path.substr(_config.locations[_loc_i].path.length() - 1);
    
    if (access(full_path.c_str(), F_OK) == -1)
    {
        buildErrorResponse(404, "Not Found");
        return;
    }
    if (access(full_path.c_str(), W_OK) == -1)
    {
        buildErrorResponse(403, "Forbidden");
        return;
    }
    if (fileResponse(full_path) == true)
    {   
        if (remove(full_path.c_str()) != 0)
        {
            buildErrorResponse(500, "Internal Server Error");
            return;
        }
        _response = _version + " 204 No Content\r\n"
                    "Content-Length: 0";
        return;
    }
    struct stat info;
    if (stat(full_path.c_str(), &info) != 0)
    {
        buildErrorResponse(500, "Internal Server Error");
        return;
    }
    if (S_ISDIR(info.st_mode))
    {
        if (rmdir(full_path.c_str()) != 0)
        {
            if (errno == EACCES)
            {
                buildErrorResponse(403, "Forbidden");
                return;
            }
            else if (errno == ENOTEMPTY)
            {
                buildErrorResponse(409, "Conflict");
                return;
            }
            else
            {
                buildErrorResponse(500, "Internal Server Error");
                return;
            }
        }
        _response = _version + " 204 No Content\r\n"
                    "Content-Length: 0";
        return;
    }
    buildErrorResponse(404, "Not Found");
}


void RequestManager::buildErrorResponse(int code, const std::string msg)
{
    std::string body;
    
    if (_config.errorPages.find(code) != _config.errorPages.end())
    {
        std::string error_page_path = _config.root;
        if (error_page_path[error_page_path.length() - 1] != '/')
            error_page_path += "/";
        std::string error_page_relative = _config.errorPages[code];
        if (!error_page_relative.empty() && error_page_relative[0] == '/')
            error_page_relative = error_page_relative.substr(1);
        error_page_path += error_page_relative;
        
        if (access(error_page_path.c_str(), R_OK) == 0)
        {
            std::ifstream file(error_page_path.c_str(), std::ios::binary);
            if (file.is_open())
            {
                std::string file_content;
                char c;
                while (file.get(c))
                    file_content += c;
                file.close();
                body = file_content;
            }
        }
    }
    
    if (body.empty())
        body = getDefaultErrorPage(code, msg);
    
    _response = _version + " " + itos(code) + " " + msg + "\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: " + itos(body.length()) + "\r\n"
                "\r\n" + body;
}

std::string RequestManager::getResponse() {
    return _response;
}


void RequestManager::buildPOSTResponse() {
    if (_request.find("Transfer-Encoding: chunked") != std::string::npos)
        _is_chunked = true;
    std::string full_path = _config.locations[_loc_i].root + _path.substr(_config.locations[_loc_i].path.length() - 1);
    
    if (isCGI(full_path))
    {
        if (access(full_path.c_str(), F_OK) == -1)
        {
            buildErrorResponse(404, "Not Found");
            return;
        }
        if (access(full_path.c_str(), R_OK) == -1)
        {
            buildErrorResponse(403, "Forbidden");
            return;
        }
        executeCGI(full_path);
        return;
    }
    
    if (_media_type != "multipart/form-data")
    {
        size_t headers_end = _request.find("\r\n\r\n");
        if (headers_end == std::string::npos)
        {
            buildErrorResponse(400, "Bad Request");
            return;
        }
        if (_config.locations[_loc_i].uploadEnable != true)
        {
            buildErrorResponse(403, "Forbidden");
            return;
        }
        if (access((_config.locations[_loc_i].uploadStore).c_str(), F_OK) == -1)
        {
            buildErrorResponse(404, "Not Found");
            return;
        }
        if (access((_config.locations[_loc_i].uploadStore).c_str(), W_OK) == -1)
        {
            buildErrorResponse(403, "Forbidden");
            return;
        }
        static int counter = 0;
        counter++;
        std::ostringstream oss;
        oss << "upload_" << counter;
        std::string filename = oss.str();
        std::string body = _request.substr(headers_end + 4);
        std::string file_path = _config.locations[_loc_i].uploadStore + "/" + filename;
        std::ofstream ofile(file_path.c_str(), std::ios::binary);
        if (!ofile)
        {
            buildErrorResponse(500, "Internal Server Error");
            return;
        }
        ofile << body;
        ofile.close();
        _response = _version + " 201 Created\r\n" +
                    "Location: " + _config.locations[_loc_i].path + filename + "\r\n" +
                    "Content-Type: text/html\r\n" +
                    "Content-Length: 0\r\n\r\n";
        return;
    }
    if (_boundary == "")
    {
        buildErrorResponse(400, "Bad Request");
        return;
    }
    
    size_t headers_end = _request.find("\r\n\r\n");
    if (headers_end == std::string::npos)
    {
        buildErrorResponse(400, "Bad Request");
        return;
    }
    
    if (_config.locations[_loc_i].uploadEnable != true)
    {
        buildErrorResponse(403, "Forbidden");
        return;
    }
    if (access((_config.locations[_loc_i].uploadStore).c_str(), F_OK) == -1)
    {
        buildErrorResponse(404, "Not Found");
        return;
    }
    if (access((_config.locations[_loc_i].uploadStore).c_str(), W_OK) == -1)
    {
        buildErrorResponse(403, "Forbidden");
        return;
    }
    
    std::vector<std::string> contents;
    std::vector<std::string> filenames;
    
    std::string body = _request.substr(headers_end + 4);
    size_t current_pos = body.find(_boundary);
    if (current_pos == std::string::npos)
    {
        buildErrorResponse(400, "Bad Request");
        return;
    }
    
    current_pos += _boundary.length();
    
    while (1)
    {
        if (body.substr(current_pos, 2) == "\r\n")
            current_pos += 2;
        else if (body.substr(current_pos, 2) == "--")
            break;
        
        size_t next_boundary = body.find(_boundary, current_pos);
        if (next_boundary == std::string::npos)
        {
            buildErrorResponse(400, "Bad Request");
            return;
        }
        
        std::string part = body.substr(current_pos, next_boundary - current_pos - 2);
        
        size_t part_headers_end = part.find("\r\n\r\n");
        if (part_headers_end == std::string::npos)
        {
            buildErrorResponse(400, "Bad Request");
            return;
        }
        
        std::string part_headers = part.substr(0, part_headers_end);
        std::string part_content = part.substr(part_headers_end + 4);
        
        size_t filename_pos = part_headers.find("filename=\"");
        if (filename_pos == std::string::npos)
        {
            current_pos = next_boundary + _boundary.length();
            continue;
        }
        
        filename_pos += 10;
        size_t filename_end = part_headers.find("\"", filename_pos);
        if (filename_end == std::string::npos)
        {
            buildErrorResponse(400, "Bad Request");
            return;
        }
        
        std::string filename = part_headers.substr(filename_pos, filename_end - filename_pos);
        
        if (filename.empty())
        {
            buildErrorResponse(400, "Bad Request");
            return;
        }
        
        contents.push_back(part_content);
        filenames.push_back(filename);
        
        current_pos = next_boundary + _boundary.length();
    }
    
    if (contents.empty())
    {
        buildErrorResponse(400, "Bad Request");
        return;
    }
    
    for (size_t i = 0; i < contents.size(); ++i)
    {
        std::string file_path = _config.locations[_loc_i].uploadStore + "/" + filenames[i];
        std::ofstream ofile(file_path.c_str(), std::ios::binary);
        if (!ofile)
        {
            buildErrorResponse(500, "Internal Server Error");
            return;
        }
        ofile << contents[i];
        ofile.close();
    }
    
    std::string locations;
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        if (i > 0)
            locations += ", ";
        locations += _config.locations[_loc_i].path + filenames[i];
    }
    
    _response = _version + " 201 Created\r\n" + 
                "Location: " + locations + "\r\n" +
                "Content-Type: text/html\r\n" +
                "Content-Length: 0\r\n\r\n";
}

std::string RequestManager::buildAutoIndexResponse(std::string full_path, std::string request_path) {
    DIR *dir = opendir(full_path.c_str());
    if (!dir)
        return getDefaultErrorPage(500, "Internal Server Error");
    std::stringstream html;
    html << "<!doctype html>\n"
            << "<html lang=\"fr\">\n"
            << "<head>\n"
            << "<meta charset=\"UTF-8\" />\n"
            << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n"
            << "<title>Index of " << request_path << " - Webserv</title>\n"
            << "<script src=\"https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4\"></script>\n"
            << "</head>\n"
            << "<body class=\"min-h-screen bg-zinc-950 text-zinc-50 p-8\">\n"
            << "    <div class=\"w-full max-w-4xl mx-auto\">\n"
            << "        <div class=\"relative rounded-xl border border-zinc-800 bg-zinc-900/50 shadow-2xl\">\n"
            << "            <div class=\"absolute rounded-xl inset-0 bg-gradient-to-br from-zinc-900 via-zinc-900 to-zinc-950 opacity-80\"></div>\n"
            << "            <div class=\"relative p-8\">\n"
            << "                <h1 class=\"text-3xl font-bold mb-6 bg-gradient-to-br from-zinc-100 to-zinc-400 bg-clip-text text-transparent\">\n"
            << "                    Index of " << request_path << "\n"
            << "                </h1>\n"
            << "                <div class=\"overflow-x-auto\">\n"
            << "                    <table class=\"w-full border-collapse\">\n"
            << "                        <thead>\n"
            << "                            <tr class=\"border-b border-zinc-700\">\n"
            << "                                <th class=\"text-left py-3 px-4 text-zinc-400 font-medium\">Name</th>\n"
            << "                                <th class=\"text-right py-3 px-4 text-zinc-400 font-medium\">Size</th>\n"
            << "                            </tr>\n"
            << "                        </thead>\n"
            << "                        <tbody>\n";

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        std::string name = entry->d_name;
        if (name == "." || name == "..")
            continue;

        std::string entry_path = full_path + "/" + name;
        struct stat info;
        if (stat(entry_path.c_str(), &info) != 0)
            continue;

        std::string link_path = request_path;
        if (link_path[link_path.length() - 1] != '/')
            link_path += "/";
        link_path += name;
        if (S_ISDIR(info.st_mode))
            link_path += "/";

        std::string display_name = name;
        if (S_ISDIR(info.st_mode))
            display_name += "/";

        std::string size_str = S_ISDIR(info.st_mode) ? "-" : itos((int)info.st_size);

        html << "                            <tr class=\"border-b border-zinc-800 hover:bg-zinc-800/30\">\n"
                << "                                <td class=\"py-3 px-4\">\n"
                << "                                    <a href=\"" << link_path << "\" class=\"text-blue-400 hover:text-blue-300 hover:underline\">"
                << display_name << "</a>\n"
                << "                                </td>\n"
                << "                                <td class=\"py-3 px-4 text-right text-zinc-400\">" << size_str << "</td>\n"
                << "                            </tr>\n";
    }
    closedir(dir);
    html << "                        </tbody>\n"
            << "                    </table>\n"
            << "                </div>\n"
            << "            </div>\n"
            << "        </div>\n"
            << "    </div>\n"
            << "</body>\n"
            << "</html>\n";
    return html.str();
}

bool RequestManager::isCGI(std::string file_path) {
    if (_config.locations[_loc_i].cgiExtension.empty())
        return false;
    
    std::string ext = _config.locations[_loc_i].cgiExtension;
    if (file_path.length() < ext.length())
        return false;
    
    return file_path.substr(file_path.length() - ext.length()) == ext;
}

void RequestManager::executeCGI(std::string file_path) {
    int pipe_in[2];
    int pipe_out[2];
    
    if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1) {
        buildErrorResponse(500, "Internal Server Error");
        return;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
        buildErrorResponse(500, "Internal Server Error");
        return;
    }
    
    if (pid == 0) {
        close(pipe_in[1]);
        close(pipe_out[0]);
        dup2(pipe_in[0], STDIN_FILENO);
        dup2(pipe_out[1], STDOUT_FILENO);
        close(pipe_in[0]);
        close(pipe_out[1]);
        
        std::vector<std::string> env_strings;
        env_strings.push_back("REQUEST_METHOD=" + _method);
        env_strings.push_back("SERVER_PROTOCOL=" + _version);
        env_strings.push_back("CONTENT_LENGTH=" + itos(_content_len));
        if (!_content_type.empty())
            env_strings.push_back("CONTENT_TYPE=" + _content_type);
        
        size_t query_pos = _path.find('?');
        std::string script_name = _path;
        std::string query_string = "";
        if (query_pos != std::string::npos) {
            script_name = _path.substr(0, query_pos);
            query_string = _path.substr(query_pos + 1);
            env_strings.push_back("QUERY_STRING=" + query_string);
        } else {
            env_strings.push_back("QUERY_STRING=");
        }
        env_strings.push_back("SCRIPT_NAME=" + script_name);
        env_strings.push_back("SCRIPT_FILENAME=" + file_path);
        env_strings.push_back("PATH_INFO=" + script_name);
        
        char **envp = new char*[env_strings.size() + 1];
        for (size_t i = 0; i < env_strings.size(); i++) {
            envp[i] = new char[env_strings[i].length() + 1];
            std::strcpy(envp[i], env_strings[i].c_str());
        }
        envp[env_strings.size()] = NULL;
        
        size_t last_slash = file_path.rfind('/');
        std::string script_file = file_path;
        if (last_slash != std::string::npos) {
            std::string dir = file_path.substr(0, last_slash);
            script_file = file_path.substr(last_slash + 1);
            chdir(dir.c_str());
        }
        
        char *argv[3];
        argv[0] = new char[_config.locations[_loc_i].cgiPass.length() + 1];
        std::strcpy(argv[0], _config.locations[_loc_i].cgiPass.c_str());
        argv[1] = new char[script_file.length() + 1];
        std::strcpy(argv[1], script_file.c_str());
        argv[2] = NULL;
        
        execve(_config.locations[_loc_i].cgiPass.c_str(), argv, envp);
        std::cerr << "CGI execution failed" << std::endl;
        for (size_t i = 0; i < env_strings.size(); i++) {
            delete[] envp[i];
        }
        delete[] envp;
        delete[] argv[0];
        delete[] argv[1];
        exit(1);
    }
    close(pipe_in[0]);
    close(pipe_out[1]);

    if (_method == "POST" && _content_len > 0) {
        size_t body_start = _request.find("\r\n\r\n");
        if (body_start != std::string::npos) {
            body_start += 4;
            std::string body = _request.substr(body_start);
            write(pipe_in[1], body.c_str(), body.length());
        }
    }
    close(pipe_in[1]);
    
    std::string cgi_output;
    char buffer[4096]; // convention unix askip
    ssize_t bytes_read;
    while ((bytes_read = read(pipe_out[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        cgi_output += buffer;
    }
    close(pipe_out[0]);
    
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        _response = parseCGIOutput(cgi_output);
    } else {
        buildErrorResponse(500, "Internal Server Error");
    }
}

std::string RequestManager::parseCGIOutput(std::string cgi_output) {
    size_t header_end = cgi_output.find("\r\n\r\n");
    if (header_end == std::string::npos) {
        header_end = cgi_output.find("\n\n");
        if (header_end != std::string::npos)
            header_end += 2;
    } else {
        header_end += 4;
    }
    
    std::string headers;
    std::string body;
    if (header_end != std::string::npos) {
        headers = cgi_output.substr(0, header_end);
        body = cgi_output.substr(header_end);
    } else {
        body = cgi_output;
    }
    
    if (headers.find("HTTP/") == 0) {
        return cgi_output;
    }
    
    std::string status = "200 OK";
    std::string content_type = "text/html";
    std::string other_headers;
    
    std::stringstream ss(headers);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty() || line == "\r")
            continue;
        
        if (line[line.length() - 1] == '\r')
            line = line.substr(0, line.length() - 1);
        
        size_t colon = line.find(':');
        if (colon == std::string::npos)
            continue;
        
        std::string header_name = line.substr(0, colon);
        std::string header_value = line.substr(colon + 1);
        
        while (!header_value.empty() && header_value[0] == ' ')
            header_value = header_value.substr(1);
        
        if (header_name == "Status") {
            status = header_value;
        } else if (header_name == "Content-Type" || header_name == "Content-type") {
            content_type = header_value;
        } else {
            other_headers += header_name + ": " + header_value + "\r\n";
        }
    }
    
    std::string response = _version + " " + status + "\r\n";
    response += "Content-Type: " + content_type + "\r\n";
    response += "Content-Length: " + itos(body.length()) + "\r\n";
    response += other_headers;
    response += "\r\n";
    response += body;
    
    return response;
}
