#include "../includes/Cat.hpp"

Cat::Cat() : Animal() {
	_type = "Cat";
	std::cout << "Chat créé" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other) {
	std::cout << "Chat copié" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
	if (this != &other) {
		_type = other._type;
		std::cout << "Chat assigné" << std::endl;
	}
	return *this;
}

Cat::~Cat() {
	std::cout << "Chat détruit" << std::endl;
}


void Cat::makeSound(void) const {
	std::cout << "Miaaoooooouuuuu" << std::endl;
}
