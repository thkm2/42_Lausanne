#include "Zombie.hpp"

int main() {
	int n = 80;
	Zombie *mes_zombies = zombieHorde(n, "cool");
	if (!mes_zombies)
		return (1);
	for (int i = 0; i < n; i++) {
		mes_zombies[i].announce();
	}
	delete[] mes_zombies;
	return (0);
}