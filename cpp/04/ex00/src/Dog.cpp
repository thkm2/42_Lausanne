#include "../includes/Dog.hpp"

Dog::Dog() : Animal() {
	_type = "Dog";
	std::cout << "Chien créé" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
	std::cout << "Chien copié" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
	if (this != &other) {
		_type = other._type;
		std::cout << "Chien assigné" << std::endl;
	}
	return *this;
}

Dog::~Dog() {
	std::cout << "Chien détruit" << std::endl;
}


void Dog::makeSound(void) const {
	std::cout << "wooouuuhouuuuuuhouffff (c'est un aboiement de chien)" << std::endl;
}
