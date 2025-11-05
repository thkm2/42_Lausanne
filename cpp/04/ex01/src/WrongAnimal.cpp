#include "../includes/WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("Wronganimal") {
	std::cout << "Mauvais animal créé" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) {
	_type = other._type;
	std::cout << "Mauvais animal copié" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
	if (this != &other) {
		_type = other._type;
		std::cout << "Mauvais animal assigné" << std::endl;
	}
	return *this;
}

WrongAnimal::~WrongAnimal() {
	std::cout << "Mauvais animal détruit" << std::endl;
}

std::string WrongAnimal::getType(void) const {
	return _type;
}

void WrongAnimal::makeSound(void) const {
	std::cout << "Le mauvais animal fait du bruit" << std::endl;
}
