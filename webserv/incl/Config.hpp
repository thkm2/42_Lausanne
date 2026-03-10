#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "lib.hpp"

struct ListenAddress {
	std::string host;
	int         port;
	ListenAddress() : host(""), port(0) {}
};

struct LocationConfig {
	std::string path;
	std::vector<std::string> allowedMethods;
	std::string root;
	std::vector<std::string> indexFiles;
	bool autoindex;
	
	bool uploadEnable;
	std::string uploadStore;
	
	bool hasReturn;
	int returnCode;
	std::string returnUrl;
	
	std::string cgiExtension;
	std::string cgiPass;
	
	LocationConfig() : 
		autoindex(false),
		uploadEnable(false),
		hasReturn(false),
		returnCode(0)
	{}
};

struct ServerConfig {
	std::vector<ListenAddress> listens;
	std::string root;
	std::vector<std::string> indexFiles;
	size_t clientMaxBodySize;
	std::map<int, std::string> errorPages;
	std::vector<LocationConfig> locations;
	
	ServerConfig() : clientMaxBodySize(1048576) {} // 1MB par défaut
};

class Config {
	private:
		ServerConfig _server;
	public:
		Config(std::string filename);
		~Config();
		
		ServerConfig server() const;
		void print() const;
};

#endif