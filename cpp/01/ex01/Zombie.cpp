#include "Zombie.hpp"

Zombie::Zombie() : _name("inconnu") {}

Zombie::~Zombie() {
	std::cout << _name << " destroyed" << std::endl;
}

void Zombie::set_name(std::string name) {
	_name = name;
}

void Zombie::announce(void) const {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}