#include "../incl/lib.hpp"
#include "../incl/SocketManager.hpp"
#include "../incl/Config.hpp"
#include "../incl/ConfigParser.hpp"
#include "../incl/Config.hpp"

int g_running = 1;

void signalHandler(int sig) {
	(void)sig;
	g_running = 0;
}

int main(int ac, char ** av) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv <config_file>" << std::endl;
		return 1;
	}
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	try {
		Config config(av[1]);
		config.print();

		SocketManager socketManager(config.server());
		socketManager.run(g_running);
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
    return 0;
}