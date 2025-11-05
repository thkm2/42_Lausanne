#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	_hit_points = 100;
	_energy_points = 50;
	_attack_damage = 20;
	std::cout << "ScavTrap " << _name << " créé !" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
	std::cout << "ScavTrap " << _name << " copié !" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
	if (this != &other) {
		ClapTrap::operator=(other);
		std::cout << "ScavTrap " << _name << " assigné !" << std::endl;
	}
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap " << _name << " détruit..." << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (_energy_points > 0 && _hit_points > 0) {
		_energy_points--;
		std::cout << _name << " attaque " << target << " en ScavTrap !" << std::endl;
	} 
	else _hit_points < 1 ? std::cout << _name << " ne peut plus ScavTraper car il est mort..." << std::endl
		: std::cout << _name << " n'a plus assez d'énergie pour ScavTraper" << std::endl;
}

void ScavTrap::guardGate() const {
	std::cout << _name << " est désormais en mode 'Garde Porte'" << std::endl;
}