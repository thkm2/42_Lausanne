#include "../includes/Cat.hpp"

Cat::Cat() : Animal() {
	_type = "Cat";
	_brain = new Brain();
	std::cout << "Chat créé" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other) {
	_brain = new Brain(*other._brain);
	std::cout << "Chat copié" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
	if (this != &other) {
		_type = other._type;
		delete _brain;
		_brain = new Brain(*other._brain);
		std::cout << "Chat assigné" << std::endl;
	}
	return *this;
}

Cat::~Cat() {
	delete _brain;
	std::cout << "Chat détruit" << std::endl;
}


void Cat::makeSound(void) const {
	std::cout << "Miaaoooooouuuuu" << std::endl;
}
