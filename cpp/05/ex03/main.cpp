#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main() {
	Intern  i;
    Bureaucrat boss("boss", 1);

    AForm* a = i.makeForm("presidential pardon", "Claude");
    AForm* b = i.makeForm("coffee request", "cofee");

    if (a) {
		boss.signForm(*a);
		boss.executeForm(*a);
	}
    if (b) {
		boss.signForm(*b);
		boss.executeForm(*b);
	}

    delete a; // b est NULL

    return (0);
}
