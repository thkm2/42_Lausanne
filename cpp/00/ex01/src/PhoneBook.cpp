#include "../includes/Contact.hpp"
#include "../includes/PhoneBook.hpp"

PhoneBook::PhoneBook() : _nb_contact(0), _i_oldest(0) {}

void PhoneBook::print_instructions() const {
	std::cout << "Entrez votre choix (ADD, SEARCH et EXIT) :" << std::endl;
}

void PhoneBook::print() const {
	if (!_nb_contact) {
		std::cout << RED << "Votre repertoire est vide..." << RESET << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "INDEX" << "|" <<std::setw(10) << "PRENOM" << "|" <<std::setw(10) << "NOM" << "|" <<std::setw(10) << "SURNOM" << std::endl;
	for (int i = 0; i < 8; i++) {
		_contacts[i].print_table(i);
	}
	std::cout << "Entrez l'index du contact que vou cherchez :" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	if (input.length() != 1 || input[0] < '0' || input[0] > '7') {
		std::cout << RED << "Index invalide, recherche annulée..." << RESET << std::endl;
		return ;
	}
	_contacts[std::atoi(input.c_str())].print_info();
}

void PhoneBook::add_choice() {
	if (_nb_contact == 8) {
		_contacts[_i_oldest].set_infos();
		_i_oldest = (_i_oldest + 1) % 8;
	}
	else {
		_contacts[_nb_contact].set_infos();
		_nb_contact++;
	}
	std::cout << GREEN << "Contact ajouté !" << RESET << std::endl;
}