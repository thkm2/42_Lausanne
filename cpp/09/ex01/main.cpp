#include "RPN.hpp"

//normal : 3 + 4 -> RPN : 3 4 +
//normal : (5 - 2) * (8 + 3) -> RPN : 5 2 - 8 3 + *

// tests sympa :
// "4 2 5 * + 1 3 2 * + /" -> 2
// "5 3 3 - /" -> Error
// "   3    4   +   " -> 7

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try {
		std::cout << RPN::calculate(av[1]) << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return (0);
}