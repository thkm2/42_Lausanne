#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/WrongCat.hpp"


int main() {
	const int size = 4;
	Animal* animals[size];

	std::cout << "\n=== Création des animaux ===" << std::endl;
	for (int i = 0; i < size; i++) {
		if (i < size / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	std::cout << "\n=== Test des sons ===" << std::endl;
	for (int i = 0; i < size; i++) {
		animals[i]->makeSound();
	}

	std::cout << "\n=== Destruction des animaux ===" << std::endl;
	for (int i = 0; i < size; i++) {
		delete animals[i];
	}

	return 0;
}