#include "ScavTrap.hpp"
#include <iostream>

int main() {
	ScavTrap bob("Bob");

	bob.guardGate();

	for (int i = 0; i < 50; ++i)
		bob.attack("Cible");

	bob.attack("épuisé");

	for (int i = 0; i < 100; ++i)
		bob.takeDamage(1);
	bob.attack("encore");

	return 0;
}
