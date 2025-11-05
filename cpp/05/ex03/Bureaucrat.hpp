#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>
#include <string>

class AForm;

class Bureaucrat {
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		const std::string	&getName() const;
		int					getGrade() const;

		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException: public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class GradeTooLowException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		void signForm(AForm &f) const;
		void executeForm(AForm const & form) const;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);

#endif