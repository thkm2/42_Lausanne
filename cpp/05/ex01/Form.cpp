#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("undefined"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : _name(name),
	_isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (Form::GradeTooLowException());
	else if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (Form::GradeTooHighException());
}

Form::Form(const Form &other) : _name(other._name),
	_isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (Form::GradeTooLowException());
	else if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (Form::GradeTooHighException());
}

Form &Form::operator=(const Form &other) {
	if (this != &other) {
		_isSigned = other._isSigned;
		// _name = other._name; // etc pas possible car const
	}
	return (*this);
}

Form::~Form() {}

const char *Form::GradeTooHighException::what() const throw() {
	return ("Grade too high");
}

const char *Form::GradeTooLowException::what() const throw() {
	return ("Grade too low");
}

const std::string &Form::getName() const {
	return (_name);
}

bool Form::getIsSigned() const {
	return (_isSigned);
}

int Form::getGradeToSign() const {
	return (_gradeToSign);
}

int Form::getGradeToExecute() const {
	return (_gradeToExecute);
}

std::ostream &operator<<(std::ostream &out, const Form &f) {
	std::string isSigned = f.getIsSigned() ? "yes" : "no"; 
	out << "Form " << f.getName() << ", signed: "<< isSigned
	<< ", grade to sign : " << f.getGradeToSign() << ", grade to execute : " << f.getGradeToExecute();
	return (out);
}

void Form::beSigned(const Bureaucrat &b) {
	if (b.getGrade() <= _gradeToSign)
		_isSigned = true;
	else
		throw (Form::GradeTooLowException());
}