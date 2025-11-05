#include "../includes/Dog.hpp"

Dog::Dog() : Animal() {
	_type = "Dog";
	_brain = new Brain();
	std::cout << "Chien créé" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
	_brain = new Brain(*other._brain);
	std::cout << "Chien copié" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
	if (this != &other) {
		_type = other._type;
		delete _brain;
		_brain = new Brain(*other._brain);
		std::cout << "Chien assigné" << std::endl;
	}
	return *this;
}

Dog::~Dog() {
	delete _brain;
	std::cout << "Chien détruit" << std::endl;
}


void Dog::makeSound(void) const {
	std::cout << "wooouuuhouuuuuuhouffff (c'est un aboiement de chien)" << std::endl;
}
