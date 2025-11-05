#ifndef PB_HPP
#define PB_HPP

#include "Contact.hpp"

#include <iostream>

class PhoneBook {
	private:
		Contact _contacts[8];
		int		_nb_contact;
		int 	_i_oldest;
	public:
		PhoneBook();
		void print_instructions() const;
		void print() const;
		void add_choice();
};

#endif