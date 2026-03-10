#ifndef SOCKETMANAGER_HPP
#define SOCKETMANAGER_HPP
#include "lib.hpp"
#include "Config.hpp"

class SocketManager {
    private:
        std::vector<int> _server_fds;
        ServerConfig _config;
        std::vector<pollfd> _fds;
        std::vector<std::string> _request_parts;
        std::vector<time_t> _last_activity;

        void addClient(int client_fd);
        void removeClient(size_t index);
        void setupServerSocket(int port);
        void handleNewConnection(int server_fd);
        void handleClientData(int client_fd);

    public:
        SocketManager(ServerConfig config);
        ~SocketManager();

        void run(int& running);
};

#endif