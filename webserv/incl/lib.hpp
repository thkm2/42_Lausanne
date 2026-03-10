#ifndef LIB_HPP
#define LIB_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/stat.h> 
#include <vector>
#include <fstream>
#include <exception>
#include <sstream>
#include <cctype>
#include <map>
#include <dirent.h>
#include <algorithm>
#include <cstring>
#include <sys/wait.h>
#include <csignal>

std::string itos(int value);
std::string extractQuotedValue(const std::string s);
std::string getDefaultErrorPage(int code, const std::string &message);

#endif