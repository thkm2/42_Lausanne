#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>
#include <string>

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

		const std::string	&getName() const; // return un ref constante -> pas de copie sur un type lourd (std::string) + pas de possibilité d'edit
		int					getGrade() const; // overkill de return un ref constante car la copie à quasi le meme poids

		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException: public std::exception {
			public:
				virtual const char *what() const throw(); // 'virtual' pas nécessaire -> pour indiquer que ça override
		};
		class GradeTooLowException: public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);

#endif