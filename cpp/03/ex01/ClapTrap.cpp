#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
	: _name(name), _hit_points(10), _energy_points(10), _attack_damage(0) {
		std::cout << "ClapTrap " << _name << " créé !" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) {
	*this = other;
	std::cout << "ClapTrap " << _name << " copié !" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
	if (this != &other) {
		_name = other._name;
		_hit_points = other._hit_points;
		_energy_points = other._energy_points;
		_attack_damage = other._attack_damage;
		std::cout << "ClapTrap " << _name << " assigné !" << std::endl;
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << _name << " détruit..." << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (_energy_points > 0 && _hit_points > 0) {
		_energy_points--;
		std::cout << _name << " attaque " << target << " !" << std::endl;
	} 
	else _hit_points < 1 ? std::cout << _name << " ne peut plus attaquer car il est mort..." << std::endl
		: std::cout << _name << " n'a plus assez d'énergie pour attaquer" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (_hit_points > 0) {
		_hit_points -= amount;
		std::cout << _name << " a pris des dégats ! " << RED << "-" << amount << RESET 
		<< " points de vie";
		if (_hit_points < 1)
			std::cout << std::endl << _name << " est mort..." << std::endl;
		else
			std::cout << ", il ne lui en reste plus que : " << BLUE << _hit_points << RESET << std::endl;
	}
	else std::cout << _name << " est déjà mort, donc il prends aucun dégat" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (_hit_points > 0 && _energy_points > 0) {
		_hit_points += amount;
		_energy_points--;
		std::cout << _name << " se répare. " << GREEN << "+" << amount << RESET
		<< " points de vie, il a maintenant " << BLUE << _hit_points << RESET << " points de vie" << std::endl;
	}
	else _hit_points < 1 ? std::cout << _name << " ne peut plus se réparer car il est mort..." << std::endl
		: std::cout << _name << " n'a plus assez d'énergie pour se réparer" << std::endl;
}
