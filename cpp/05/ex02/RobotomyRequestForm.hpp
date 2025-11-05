#ifndef RRF_HPP
#define RRF_HPP

#include <iostream>
#include <string>
#include "AForm.hpp"
#include <cstdlib>

class RobotomyRequestForm: public AForm {
	private:
		std::string _target;
	public:
		RobotomyRequestForm(const std::string &target);
		RobotomyRequestForm(const RobotomyRequestForm &other);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
		~RobotomyRequestForm();

		virtual void execute(Bureaucrat const &executor) const;
};

#endif