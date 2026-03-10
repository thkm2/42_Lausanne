#include "../incl/ConfigParser.hpp"

ConfigParser::ConfigParser() : _lexer(NULL) {}

ServerConfig ConfigParser::parse(const std::string &filename) {
	Lexer lexer(filename);
	_lexer = &lexer;
	_cur = _lexer->next();
	if (_lexer->isEnd()) {
		throw std::runtime_error(lineAndCol(_cur) + "Config file is empty");
	}
	if (!(_cur.type == TOKEN_WORD && _cur.value == "server")) {
		throw std::runtime_error(lineAndCol(_cur) + "Config must start with 'server'");
	}
	ServerConfig server;
	parseServer(server);
	if (!_lexer->isEnd()) {
		throw std::runtime_error(lineAndCol(_cur) + "Unexpected tokens after 'server' block");
	}
	return server;
}

// helper
void ConfigParser::advance() {
	_cur = _lexer->next();
}

// helper
void ConfigParser::expect(TokenType type, const std::string &msg, const Token &t) {
	if (_cur.type != type) {
		throw std::runtime_error(lineAndCol(t) + msg);
	}
}

// helper
std::string ConfigParser::lineAndCol(const Token &t) {
    std::ostringstream oss;
    oss << "line " << t.line << ", column " << t.column << ": ";
    return oss.str();
}

int ConfigParser::parseInt(const std::string &s, const Token &t) {
    char *end = 0;
    long v = std::strtol(s.c_str(), &end, 10);
    if (*end || v < 0 || v > 65535) {
        throw std::runtime_error(lineAndCol(t) + "Invalid integer: " + s);
    }
    return static_cast<int>(v);
}

// pas de K/M, juste en bytes
size_t ConfigParser::parseSize(const std::string &s, const Token &t) {
    char *end = 0;
    long v = std::strtol(s.c_str(), &end, 10);
    if (*end || v < 0) {
        throw std::runtime_error(lineAndCol(t) + "Invalid size: " + s);
    }
    return static_cast<size_t>(v);
}

void ConfigParser::parseServer(ServerConfig &server) {
    advance(); // consomme server kim il est homo de mehdi
    expect(TOKEN_LBRACE, "Expected '{' after 'server'", _cur);
    advance(); // consomme la brace
	while (!_lexer->isEnd() && _cur.type != TOKEN_RBRACE) {
        if (_cur.type != TOKEN_WORD) {
            throw std::runtime_error(lineAndCol(_cur) + "Unexpected token in server block");
        }
        parseServerDirective(server);
    }
	expect(TOKEN_RBRACE, "Missing '}' at end of server block", _cur);
    advance(); // consomme rbrace pour etre à end
}

void ConfigParser::parseServerDirective(ServerConfig &server) {
    std::string name = _cur.value;
    advance();

    if (name == "listen") {
		expect(TOKEN_WORD, "Expected value after 'listen'", _cur);
        std::string value = _cur.value;
        advance();
        expect(TOKEN_SEMICOLON, "Missing ';' after listen", _cur);
        advance();

        ListenAddress la;
        std::string::size_type pos = value.find(':');
        if (pos == std::string::npos) {
            // pas de host
            la.host = "";
            la.port = parseInt(value, _cur);
        } else {
            la.host = value.substr(0, pos);
            la.port = parseInt(value.substr(pos + 1), _cur);
        }
        server.listens.push_back(la);

    } else if (name == "root") {
		expect(TOKEN_WORD, "Expected path after 'root'", _cur);
        server.root = _cur.value;
        advance();
        expect(TOKEN_SEMICOLON, "Missing ';' after root", _cur);
        advance();

    } else if (name == "index") {
		expect(TOKEN_WORD, "Expected at least one file after 'index'", _cur);
        while (_cur.type == TOKEN_WORD) {
            server.indexFiles.push_back(_cur.value);
            advance();
        }
        expect(TOKEN_SEMICOLON, "Missing ';' after index", _cur);
        advance();

    } else if (name == "client_max_body_size") {
		expect(TOKEN_WORD, "Expected size after 'client_max_body_size'", _cur);
        server.clientMaxBodySize = parseSize(_cur.value, _cur);
        advance();
        expect(TOKEN_SEMICOLON, "Missing ';' after client_max_body_size", _cur);
        advance();

    } else if (name == "error_page") {
        std::vector<int> codes;
        while (_cur.type == TOKEN_WORD) {
            const std::string &v = _cur.value;
            bool isNum = true;
            for (size_t i = 0; i < v.size(); ++i) {
                if (!std::isdigit(static_cast<unsigned char>(v[i]))) {
                    isNum = false;
                    break;
                }
            }
            if (!isNum)
                break;
            codes.push_back(parseInt(v, _cur));
            advance();
        }
        if (codes.empty()) {
            throw std::runtime_error(lineAndCol(_cur) + "Expected error code(s) after 'error_page'");
        }

		expect(TOKEN_WORD, "Expected path after error codes", _cur);
        std::string path = _cur.value;
        advance();
        expect(TOKEN_SEMICOLON, "Missing ';' after error_page", _cur);
        advance();
        for (size_t i = 0; i < codes.size(); ++i) {
            server.errorPages[codes[i]] = path;
        }

    } else if (name == "location") {
		parseLocation(server);
		
	} else {
        throw std::runtime_error(lineAndCol(_cur) + "Unknown server directive: '" + name + "'");
    }
}

void ConfigParser::parseLocation(ServerConfig &server) {
	// on a déjà consommé "location"
	expect(TOKEN_WORD, "Expected location path after 'location'", _cur);
	
	LocationConfig loc;
	loc.path = _cur.value;
	advance();
	
	expect(TOKEN_LBRACE, "Expected '{' after location path", _cur);
	advance();
	
	while (!_lexer->isEnd() && _cur.type != TOKEN_RBRACE) {
		if (_cur.type != TOKEN_WORD) {
			throw std::runtime_error(lineAndCol(_cur) + "Unexpected token in location block");
		}
		parseLocationDirective(loc);
	}
	
	expect(TOKEN_RBRACE, "Missing '}' at end of location block", _cur);
	advance();
	
	server.locations.push_back(loc);
}

void ConfigParser::parseLocationDirective(LocationConfig &location) {
	std::string name = _cur.value;
	advance();
	
	if (name == "allowed_methods") {
		expect(TOKEN_WORD, "Expected at least one method after 'allowed_methods'", _cur);
		while (_cur.type == TOKEN_WORD) {
			location.allowedMethods.push_back(_cur.value);
			advance();
		}
		expect(TOKEN_SEMICOLON, "Missing ';' after allowed_methods", _cur);
		advance();

	} else if (name == "root") {
		expect(TOKEN_WORD, "Expected path after 'root'", _cur);
		location.root = _cur.value;
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after root", _cur);
		advance();
		
	} else if (name == "index") {
		expect(TOKEN_WORD, "Expected at least one file after 'index'", _cur);
		while (_cur.type == TOKEN_WORD) {
			location.indexFiles.push_back(_cur.value);
			advance();
		}
		expect(TOKEN_SEMICOLON, "Missing ';' after index", _cur);
		advance();
		
	} else if (name == "autoindex") {
		expect(TOKEN_WORD, "Expected 'on' or 'off' after 'autoindex'", _cur);
		std::string value = _cur.value;
		if (value == "on") {
			location.autoindex = true;
		} else if (value == "off") {
			location.autoindex = false;
		} else {
			throw std::runtime_error(lineAndCol(_cur) + "Invalid autoindex value: '" + value + "' (expected 'on' or 'off')");
		}
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after autoindex", _cur);
		advance();
		
	} else if (name == "upload_enable") {
		expect(TOKEN_WORD, "Expected 'on' or 'off' after 'upload_enable'", _cur);
		std::string value = _cur.value;
		if (value == "on") {
			location.uploadEnable = true;
		} else if (value == "off") {
			location.uploadEnable = false;
		} else {
			throw std::runtime_error(lineAndCol(_cur) + "Invalid upload_enable value: '" + value + "'");
		}
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after upload_enable", _cur);
		advance();
		
	} else if (name == "upload_store") {
		expect(TOKEN_WORD, "Expected path after 'upload_store'", _cur);
		location.uploadStore = _cur.value;
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after upload_store", _cur);
		advance();
		
	} else if (name == "return") {
		expect(TOKEN_WORD, "Expected status code after 'return'", _cur);
		location.returnCode = parseInt(_cur.value, _cur);
		advance();
		
		expect(TOKEN_WORD, "Expected URL after return code", _cur);
		location.returnUrl = _cur.value;
		location.hasReturn = true;
		advance();
		
		expect(TOKEN_SEMICOLON, "Missing ';' after return", _cur);
		advance();
		
	} else if (name == "cgi_extension") {
		expect(TOKEN_WORD, "Expected extension after 'cgi_extension'", _cur);
		location.cgiExtension = _cur.value;
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after cgi_extension", _cur);
		advance();
		
	} else if (name == "cgi_pass") {
		expect(TOKEN_WORD, "Expected path after 'cgi_pass'", _cur);
		location.cgiPass = _cur.value;
		advance();
		expect(TOKEN_SEMICOLON, "Missing ';' after cgi_pass", _cur);
		advance();
		
	} else {
		throw std::runtime_error(lineAndCol(_cur) + "Unknown location directive: '" + name + "'");
	}
}
