#include "includes/Contact.hpp"
#include "includes/PhoneBook.hpp"

int main() {
	PhoneBook 	pb;
	std::string choice;

	pb.print_instructions();
	while (1) {
		std::getline(std::cin, choice);
		if (choice == "ADD") {
			pb.add_choice();
		}
		else if (choice == "SEARCH") {
			pb.print();
		}
		else if (choice == "EXIT") {
			std::cout << BLUE << "Au revoir !" << RESET << std::endl;
			exit(0);
		}
		std::cout << std::endl;
		pb.print_instructions();
	}
	return (0);
}