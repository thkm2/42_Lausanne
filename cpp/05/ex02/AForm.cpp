#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("undefined"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : _name(name),
	_isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (AForm::GradeTooLowException());
	else if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (AForm::GradeTooHighException());
}

AForm::AForm(const AForm &other) : _name(other._name),
	_isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw (AForm::GradeTooLowException());
	else if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw (AForm::GradeTooHighException());
}

AForm &AForm::operator=(const AForm &other) {
	if (this != &other) {
		_isSigned = other._isSigned;
	}
	return (*this);
}

AForm::~AForm() {}

const char *AForm::GradeTooHighException::what() const throw() {
	return ("Grade too high");
}

const char *AForm::GradeTooLowException::what() const throw() {
	return ("Grade too low");
}

const std::string &AForm::getName() const {
	return (_name);
}

bool AForm::getIsSigned() const {
	return (_isSigned);
}

int AForm::getGradeToSign() const {
	return (_gradeToSign);
}

int AForm::getGradeToExecute() const {
	return (_gradeToExecute);
}

std::ostream &operator<<(std::ostream &out, const AForm &f) {
	std::string isSigned = f.getIsSigned() ? "yes" : "no"; 
	out << "Form " << f.getName() << ", signed: "<< isSigned
	<< ", grade to sign : " << f.getGradeToSign() << ", grade to execute : " << f.getGradeToExecute();
	return (out);
}

void AForm::beSigned(const Bureaucrat &b) {
	if (b.getGrade() <= _gradeToSign)
		_isSigned = true;
	else
		throw (AForm::GradeTooLowException());
}

const char *AForm::FormNotSignedException::what() const throw() {
	return ("Form not signed");
}