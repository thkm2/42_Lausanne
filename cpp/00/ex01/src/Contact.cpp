#include "../includes/Contact.hpp"

Contact::Contact() : _first_name("-"), _last_name("-"), _nickname("-"), _phone_number("-"), _darkest_secret("-") {}

std::string get_info(std::string phrase) {
	std::string input = "";

	std::cout << phrase << std::endl;
	std::getline(std::cin, input);
	while (!input.length()) {
		std::cout << RED << "Une information vide n'est pas autorisée" << RESET << std::endl;
		std::cout << phrase << std::endl;
		std::getline(std::cin, input);
	}
	return input;
}

void Contact::set_infos() {
	
	_first_name = get_info("Entrez le prénom du contact :");
	_last_name = get_info("Entrez le nom du contact :");
	_nickname = get_info("Entrez le surnom du contact :");
	_phone_number = get_info("Entrez le numéro de téléphone du contact :");
	_darkest_secret = get_info("Entrez le secret du contact :");
}

std::string f9(std::string s) {
	if (s.length() > 10)
		return s.substr(0, 9) + ".";
	return (s);
}

void Contact::print_table(int i) const {
	std::cout << std::setw(10) << i << "|"
	<< std::setw(10) << f9(_first_name) << "|"
	<< std::setw(10) << f9(_last_name) << "|"
	<< std::setw(10) << f9(_nickname) << std::endl;
}

void Contact::print_info() const {
	std::cout << std::left << std::setw(8) << "PRENOM" << " : " << _first_name << std::endl;
	std::cout << std::left << std::setw(8) << "NOM" << " : " << _last_name << std::endl;
	std::cout << std::left << std::setw(8) << "SURNOM" << " : " << _nickname << std::endl;
	std::cout << std::left << std::setw(8) << "TEL" << " : " << _phone_number << std::endl;
	std::cout << std::left << std::setw(8) << "SECRET" << " : " << _darkest_secret << std::endl;
}

Contact::~Contact() {
	std::cout << RED << "Contact " << _first_name << _last_name << " supprimé" << RESET << std::endl;
}