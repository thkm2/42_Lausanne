#include "../includes/Brain.hpp"

Brain::Brain() {
	// for (int i = 0; i < 100; i++)
	// 	_ideas[i] = ""; // le constructeur de string init deja donc inutile
	std::cout << "Brain créé" << std::endl;
}

Brain::Brain(const Brain &other) {
	for (int i = 0; i < 100; i++)
		_ideas[i] = other._ideas[i];
	std::cout << "Brain copié" << std::endl;
}

Brain &Brain::operator=(const Brain &other) {
	if (this != &other) {
		for (int i = 0; i < 100; i++)
			_ideas[i] = other._ideas[i];
		std::cout << "Brain assigné" << std::endl;
	}
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain détruit" << std::endl;
}
