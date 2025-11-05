#include "Bureaucrat.hpp"

// pour des getters, retourner une copie sur les types primitif (int, char, etc) et une ref constante sur les gros types
// 		const std::string &getName() const; // return un ref constante -> pas de copie sur un type lourd (std::string) + pas de possibilité d'edit
//		int			getGrade() const; // overkill de return un ref constante car la copie à quasi le meme poids
//
// si une méthode est virtual, toutes les méthodes enfant le sont aussi. Donc pas besoin de le spécifier, mais c'est plus clair

int main() {
	Bureaucrat bestGrade("Best", 1);
	Bureaucrat worstGrade("Worst", 150);
	Bureaucrat midGrade("mid", 42);

	std::cout << "getName test : " << midGrade.getName() << std::endl;
	std::cout << "getGrade test : " << midGrade.getGrade() << std::endl;

	std::cout << midGrade << std::endl;
	midGrade.decrementGrade();
	midGrade.decrementGrade();
	std::cout << midGrade << std::endl;
	midGrade.incrementGrade();
	std::cout << midGrade << std::endl;

	Bureaucrat copied = worstGrade;
	std::cout << copied << std::endl;

	copied = bestGrade;
	std::cout << copied << std::endl;

	try {
		Bureaucrat tooHigh("tooHigh", 0);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Bureaucrat tooLow("tooLow", 151);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		bestGrade.incrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		worstGrade.decrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
