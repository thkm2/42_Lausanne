#include "../includes/Animal.hpp"

Animal::Animal() : _type("animal") {
	std::cout << "Animal créé" << std::endl;
}

Animal::Animal(const Animal &other) {
	_type = other._type;
	std::cout << "Animal copié" << std::endl;
}

Animal &Animal::operator=(const Animal &other) {
	if (this != &other) {
		_type = other._type;
		std::cout << "Animal assigné" << std::endl;
	}
	return *this;
}

Animal::~Animal() {
	std::cout << "Animal détruit" << std::endl;
}

std::string Animal::getType(void) const {
	return _type;
}

void Animal::makeSound(void) const {
	std::cout << "l'animal fait du bruit" << std::endl;
}
