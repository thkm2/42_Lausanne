#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern &other) {
	(void)other;
}

Intern &Intern::operator=(const Intern &other) {
	(void)other;
	return (*this);
}

Intern::~Intern() {}

static AForm *makeShrubbery(const std::string &target) {
	return new ShrubberyCreationForm(target);
}

static AForm *makeRobotomy(const std::string &target) {
	return new RobotomyRequestForm(target);
}
static AForm *makePardon(const std::string &target) {
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const {
	std::string key[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm *(*fns[3])(const std::string &) = {&makeShrubbery, &makeRobotomy, &makePardon};
	for (int i = 0; i < 3; i++) {
		if (name == key[i]) {
			AForm *f = fns[i](target);
			 std::cout << "Intern creates " << f->getName() << std::endl;
			return f;
		}
	}
	std::cout << "Unknown form name '" << name << "'" << std::endl;
	return (NULL);
}