#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(time(NULL)); // rand() nb aléatoire et srand() change la séquence

    Bureaucrat boss("boss", 1);
    Bureaucrat nullos("nullos", 140);

    ShrubberyCreationForm s("tree");
    RobotomyRequestForm r("robo");
    PresidentialPardonForm p("pardon");

    boss.executeForm(s); // sans signature

    nullos.signForm(s);
    nullos.executeForm(s); // grade trop bas
    boss.executeForm(s);

    boss.signForm(r);
	boss.executeForm(r);
	boss.executeForm(r);

    boss.signForm(p);
    boss.executeForm(p);

    return 0;
}
