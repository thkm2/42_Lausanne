#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	_hit_points = 100;
	_energy_points = 100;
	_attack_damage = 30;
	std::cout << "FragTrap " << _name << " créé !" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
	std::cout << "FragTrap " << _name << " copié !" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
	if (this != &other) {
		ClapTrap::operator=(other);
		std::cout << "FragTrap " << _name << " assigné !" << std::endl;
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << _name << " détruit..." << std::endl;
}

void FragTrap::highFivesGuys(void) const {
	std::cout << _name << " demande un high five ! ✋" << std::endl;
}