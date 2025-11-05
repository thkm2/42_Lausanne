#ifndef PPF_HPP
#define PPF_HPP

#include <iostream>
#include <string>
#include "AForm.hpp"

class PresidentialPardonForm: public AForm {
	private:
		std::string _target;
	public:
		PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &other);
		PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
		~PresidentialPardonForm();

		virtual void execute(Bureaucrat const &executor) const;
};

#endif