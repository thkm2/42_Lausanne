#include "../includes/WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal() {
	_type = "WrongCat";
	std::cout << "Mauvais chat créé" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other) {
	std::cout << "Mauvais chat copié" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other) {
	if (this != &other) {
		_type = other._type;
		std::cout << "Mauvais chat assigné" << std::endl;
	}
	return *this;
}

WrongCat::~WrongCat() {
	std::cout << "Mauvais chat détruit" << std::endl;
}


void WrongCat::makeSound(void) const {
	std::cout << "Mauvais miaaoooooouuuuu" << std::endl;
}
