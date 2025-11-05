#include "ClapTrap.hpp"

int main() {
	ClapTrap a("kim");
	ClapTrap b("claude");
	a.attack("claude");
	b.takeDamage(7);
	b.beRepaired(2);
	a.attack("claude");
	b.takeDamage(7);
	return (0);
}