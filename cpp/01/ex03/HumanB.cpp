#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _weapon(NULL), _name(name) {}

void HumanB::setWeapon(Weapon &new_weapon) {
	_weapon = &new_weapon;
}

void HumanB::attack() const {
	if (_weapon)
		std::cout << _name << " attacks with their " << (*_weapon).getType() << std::endl;
}