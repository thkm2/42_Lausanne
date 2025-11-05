#include "FragTrap.hpp"
#include <iostream>

int main() {
	FragTrap bob("Bob");

	bob.highFivesGuys();

	for (int i = 0; i < 100; ++i)
		bob.attack("Cible");

	bob.attack("épuisé");

	for (int i = 0; i < 100; ++i)
		bob.takeDamage(1);
	bob.attack("encore");

	return 0;
}
