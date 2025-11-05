#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::ifstream input_file(av[1]);
	if (!input_file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange btc;
	try {
		btc.loadData();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::string line;
	while (std::getline(input_file, line)) {
		if (line == "date | value") continue;
		t_input_line_values ilv;
		try {
			btc.parseLine(line, ilv);
			btc.printOutput(ilv);
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}