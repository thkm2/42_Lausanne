#include "PmergeMe.hpp"

// ./PmergeMe 9 2 7 5

// putPendInMain avec jacobstal
// régler si y'a des problèmes avec 4 chiffres
// truc du temps et affichage comme dans le sujet
// sortMain en récursif pour plus de nb

int main(int ac, char **av) {
	std::vector<int> vec;
	std::deque<int> deq;

	try {
		PmergeMe::inputIsCorrect(ac, av);
		PmergeMe::parseArgsToContainer(ac, av, vec);
		if (PmergeMe::inputIsAlreadySorted(vec)) return 0;
		PmergeMe::parseArgsToContainer(ac, av, deq);
		PmergeMe::printContainer(vec, "Before:");

		clock_t vt1 = clock();
		PmergeMe::fordJohnson(vec);
		clock_t vt2 = clock();

		clock_t dt1 = clock();
		PmergeMe::fordJohnson(deq);
		clock_t dt2 = clock();

		PmergeMe::printContainer(vec, "After:");
		PmergeMe::printTime(vec.size(), "vector", vt1, vt2);
		PmergeMe::printTime(deq.size(), "deque", dt1, dt2);
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}