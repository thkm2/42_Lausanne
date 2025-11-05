#include "Harl.hpp"

int get_index(std::string level) {
	std::string	levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level)
			return (i);
	}
	std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	return (-1);
}

int	main(int ac, char **av) {
	Harl h;
	

	if (ac != 2) {
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
		return (0);
	}

	int i = get_index(av[1]);
	if (i == -1)
		return (0);

	switch (i) {
		case 0:
			h.complain("DEBUG");
			// fallthrough
		case 1:
			h.complain("INFO");
			// fallthrough
		case 2:
			h.complain("WARNING");
			// fallthrough
		case 3:
			h.complain("ERROR");
	}
	return (0);
}