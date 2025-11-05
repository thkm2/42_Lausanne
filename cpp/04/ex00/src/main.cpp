#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/WrongCat.hpp"

int main() {
	Animal *a = new Animal();
	a->makeSound();
	delete a;

	std::cout << std::endl;

	Animal *c = new Cat();
	c->makeSound();
	delete c;

	std::cout << std::endl;

	Animal *d = new Dog();
	d->makeSound();
	delete d;

	std::cout << std::endl;

	// mauvais message + leak
	WrongAnimal *w = new WrongCat();
	w->makeSound();
	delete w;
	return (0);
}