#ifndef SCF_HPP
#define SCF_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "AForm.hpp"

class ShrubberyCreationForm: public AForm {
	private:
		std::string _target;
	public:
		ShrubberyCreationForm(const std::string &target); // le sujet impose un arg pour ctor par défaut, un form a du sens que si il a une cible
		ShrubberyCreationForm(const ShrubberyCreationForm &other);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
		~ShrubberyCreationForm();

		virtual void execute(Bureaucrat const &executor) const;
};

#endif