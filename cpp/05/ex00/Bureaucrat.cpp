#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("undefined"), _grade(150) {}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade) {
	if (_grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	else if (_grade > 150)
		throw (Bureaucrat::GradeTooLowException());
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {
	if (_grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	else if (_grade > 150)
		throw (Bureaucrat::GradeTooLowException());
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	if (this != &other) {
		// _name = other._name; --> Impossible car name est const et du coup le bureaucrate garde toujours le meme nom
		_grade = other._grade;
	}
	return (*this);
}

Bureaucrat::~Bureaucrat() {}

const std::string &Bureaucrat::getName() const {
	return (_name);
}

int Bureaucrat::getGrade() const {
	return (_grade);
}

void Bureaucrat::incrementGrade() {
	if (_grade == 1)
		throw (Bureaucrat::GradeTooHighException());
	else 
		_grade--;
}

void Bureaucrat::decrementGrade() {
	if (_grade == 150)
		throw (Bureaucrat::GradeTooLowException());
	else 
		_grade++;
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b) {
	out << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return (out);
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return ("Grade too high");
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return ("Grade too low");
}