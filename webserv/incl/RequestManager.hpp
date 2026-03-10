#ifndef REQUEST_MANAGER_HPP
#define REQUEST_MANAGER_HPP
#include "lib.hpp"
#include "SocketManager.hpp"
#include "Config.hpp"

class RequestManager {

    private:
        ServerConfig    _config;
        std::string     _request;
        std::string     _response;
        std::string     _method;
        std::string     _path;
        std::string     _content_type;
        std::string     _boundary;
        std::string     _version;
        std::string     _media_type;
        int             _loc_i;
        size_t          _content_len;
        bool            _is_chunked;

        void requestParser();
        bool Check4xx5xxErrors();
        void InitContentTypeAndBoundary();
        bool IsMethodAllow();
        void buildGETResponse();
        void buildPOSTResponse();
        void buildDELETEResponse();
        void buildErrorResponse(int code, std::string message);
        std::string getResponseContentType(std::string full_path);
        void buildRedirectResponse(int code, std::string url = "");
        bool fileResponse(std::string full_path);
        bool dirResponse(std::string full_path);
        void buildOkResponse(std::string file_path);
        std::string buildAutoIndexResponse(std::string full_path, std::string request_path);
        
        // CGI methods
        bool isCGI(std::string file_path);
        void executeCGI(std::string file_path);
        std::string parseCGIOutput(std::string cgi_output);
        bool parsePOSTHeader();

    public:
        RequestManager(std::string request, ServerConfig config, size_t content_len);
        ~RequestManager();

        std::string getResponse();
};

#endif