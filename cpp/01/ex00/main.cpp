#include "Zombie.hpp"

int main() {
	Zombie *z1 = newZombie("z1"); // allouer sur la heap (donc c'est à nous de le delete)
	z1->announce();
	delete z1;

	randomChump("z2"); // allouer sur la stack (donc il se delete automatiquement à la fin de la ft)

	return (0);
}