#include "../incl/Config.hpp"
#include "../incl/ConfigParser.hpp"

Config::Config(std::string filename) {
    ConfigParser parser;
    _server = parser.parse(filename);
}

Config::~Config() {}

ServerConfig Config::server() const {
    return _server;
}

void Config::print() const {
    std::cout << "* _Server config *" << std::endl;
    
    std::cout << "Listen addresses:" << std::endl;
    for (size_t i = 0; i < _server.listens.size(); i++) {
        std::cout << " - " << _server.listens[i].host << ":" << _server.listens[i].port << std::endl;
    }

    if (!_server.root.empty()) {
        std::cout << "Root: " << _server.root << std::endl;
    }
    
    if (!_server.indexFiles.empty()) {
        std::cout << "Index files:" << std::endl;
        for (size_t i = 0; i < _server.indexFiles.size(); i++) {
            std::cout << "  - " << _server.indexFiles[i] << std::endl;
        }
    }
    
    std::cout << "Client max body size: " << _server.clientMaxBodySize << " bytes" << std::endl;
    
    if (!_server.errorPages.empty()) {
        std::cout << "Error pages:" << std::endl;
        for (std::map<int, std::string>::const_iterator it = _server.errorPages.begin(); it != _server.errorPages.end(); ++it) {
            std::cout << " - " << it->first << " -> " << it->second << std::endl;
        }
    }
    
    if (!_server.locations.empty()) {
        std::cout << "Locations (" << _server.locations.size() << "):" << std::endl;
        for (size_t i = 0; i < _server.locations.size(); i++) {
            const LocationConfig& loc = _server.locations[i];
            std::cout << "  Location: " << loc.path << std::endl;
            
            if (!loc.allowedMethods.empty()) {
                std::cout << "    Allowed methods: ";
                for (size_t j = 0; j < loc.allowedMethods.size(); j++) {
                    std::cout << loc.allowedMethods[j];
                    if (j < loc.allowedMethods.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
            
            if (!loc.root.empty()) {
                std::cout << "    Root: " << loc.root << std::endl;
            }
            
            if (!loc.indexFiles.empty()) {
                std::cout << "    Index: ";
                for (size_t j = 0; j < loc.indexFiles.size(); j++) {
                    std::cout << loc.indexFiles[j];
                    if (j < loc.indexFiles.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
            
            std::cout << "    Autoindex: " << (loc.autoindex ? "enabled" : "disabled") << std::endl;
            
            if (loc.uploadEnable) {
                std::cout << "    Upload enabled: " << loc.uploadStore << std::endl;
            }
            
            if (loc.hasReturn) {
                std::cout << "    Redirect: " << loc.returnCode << " -> " << loc.returnUrl << std::endl;
            }
            
            if (!loc.cgiExtension.empty()) {
                std::cout << "    CGI: " << loc.cgiExtension << " -> " << loc.cgiPass << std::endl;
            }
        }
    }
}