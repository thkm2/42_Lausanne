#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {(void)other;}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}

PmergeMe::~PmergeMe() {} // inutile mais je laisse pour le OCF

void PmergeMe::inputIsCorrect(int ac, char **av) {
	if (ac < 2)
		throw std::runtime_error("Error");
	for (int i = 1; i < ac; i++) {
		int j = 0;
		int inNb = 0;
		while (av[i][j]) {
			if (std::isdigit(av[i][j])) {
				if (inNb == 2)
					throw std::runtime_error("Error");
				inNb = 1;
			}
			else if (std::isspace(av[i][j])) {
				if (inNb)
					inNb = 2;
			}
			else
				throw std::runtime_error("Error"); 
			j++;
		}
		long nb = std::atol(av[i]);
		if (nb < 1 || nb > INT_MAX) {
			throw std::runtime_error("Error");
		}
	}
}

bool PmergeMe::inputIsAlreadySorted(const std::vector<int> &v) {
	if (v.size() < 1) return true;
	bool sorted = true;
	for (std::size_t i = 1; i < v.size(); i++) {
		if (v[i - 1] > v[i])
			sorted = false;
	}
	if (sorted) {
		PmergeMe::printContainer(v, "Before:");
		PmergeMe::printContainer(v, "After:");
		PmergeMe::printTime(v.size(), "vector", static_cast<clock_t>(0), static_cast<clock_t>(0));
		PmergeMe::printTime(v.size(), "deque", static_cast<clock_t>(0), static_cast<clock_t>(0));
	}
	return sorted;
}

// pour pend size = 4 :
// On met 1
// jacob suivant = 3 donc ajoute 3, 2 -> [1, 3, 2]
// Palier suivant = 5 mais size=4, donc ajoute seulement 4 -> [1, 3, 2, 4]
// ex :
// size = 5 -> 1 | (3, 2) | (5, 4) -> [1, 3, 2, 5, 4]
// size = 8 -> 1 | (3, 2) | (5, 4) | (8, 7, 6) -> [1, 3, 2, 5, 4, 8, 7, 6]
void PmergeMe::jacobsthalOrder(std::size_t k, std::vector<int> &order) {
    if (k == 0) return;

    order.push_back(1);

    std::vector<std::size_t> pal;
    pal.push_back(1);

    std::size_t j0 = 0, j1 = 1;
    while (pal.back() < k) {
        std::size_t jn = j1 + 2 * j0;
        j0 = j1; j1 = jn;

        std::size_t cur = (jn > k) ? k : jn; // max à k
        if (cur > pal.back())
            pal.push_back(cur);
    }

    for (std::size_t t = 1; t < pal.size(); ++t) {
        std::size_t prev = pal[t - 1];
        std::size_t cur  = pal[t];
        for (std::size_t x = cur; x > prev; --x)
            order.push_back(static_cast<int>(x));
    }
}

void PmergeMe::printTime(std::size_t size, std::string c, clock_t clock_1, clock_t clock_2) {
	double us = (clock_2 - clock_1) * 1e6 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << size
	<< " elements with std::" << c << " : " << us << " us" << std::endl;
}