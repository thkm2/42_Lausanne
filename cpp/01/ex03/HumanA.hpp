#ifndef HUMAN_A_HPP
#define HUMAN_A_HPP

#include "Weapon.hpp"

#include <iostream>

class HumanA {
	private:
		Weapon 		&_weapon;
		std::string _name;
	public:
		HumanA(std::string name, Weapon &weapon);
		void attack() const;
};

#endif