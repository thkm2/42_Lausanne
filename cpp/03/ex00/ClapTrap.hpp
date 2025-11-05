#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

class ClapTrap {
	private:
		std::string _name;
		int			_hit_points;
		int			_energy_points;
		int			_attack_damage;
	public:
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &other);
		ClapTrap &operator=(const ClapTrap &other);
		~ClapTrap();

		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};



#endif