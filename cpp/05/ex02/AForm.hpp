#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <exception>
#include <string>

class Bureaucrat;

class AForm {
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExecute;
	public:
		AForm();
		AForm(std::string name, int gradeToSign, int gradeToExecute);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm();

		class GradeTooHighException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class GradeTooLowException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class FormNotSignedException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		const std::string	&getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		
		void beSigned(const Bureaucrat &b);

		virtual void execute(Bureaucrat const &executor) const = 0;
};

std::ostream &operator<<(std::ostream &out, const AForm &f);

#endif