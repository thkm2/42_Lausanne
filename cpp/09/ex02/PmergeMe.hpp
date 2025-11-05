#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cctype>
#include <exception>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <climits>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();
	public:
		static void inputIsCorrect(int ac, char **av);

		static bool inputIsAlreadySorted(const std::vector<int> &v);

		template <typename C>
		static void parseArgsToContainer(int ac, char **av, C &c);

		template <typename C>
		static void printContainer(C &c, const std::string &pre);

		template <typename C>
		static void sortPairsAndPush(C &c, C &main, C &pend);

		template <typename C>
		static void putPendInMain(C &main, C &pend, C &ogMain);

		static void jacobsthalOrder(std::size_t k, std::vector<int> &order);

		template <typename C>
		static void fordJohnson(C &c);

		static void printTime(std::size_t size, std::string c, clock_t clock_1, clock_t clock_2);
};

template <typename C>
void PmergeMe::parseArgsToContainer(int ac, char **av, C &c) {
	for (int i = 1; i < ac; i++) {
		int nb = atoi(av[i]);
		c.push_back(nb);
	}
	if (c.empty()) throw std::runtime_error("Error");
}

template <typename C>
void PmergeMe::printContainer(C &c, const std::string &pre) {
	std::cout << pre;
	typename C::const_iterator it = c.begin();
	while (it != c.end()) {
		std::cout << " " << *it;
		it++;
	}
	std::cout << std::endl;
}

template <typename C>
void PmergeMe::sortPairsAndPush(C &c, C &main, C &pend) {
	for (std::size_t i = 0; i + 1 < c.size(); i += 2) {
		if (c[i] > c [i + 1]) {
			int tmp = c[i];
			c[i] = c[i + 1];
			c[i + 1] = tmp;
		}
		pend.push_back(c[i]);
		main.push_back(c[i + 1]);
	}
}

template <typename C>
typename C::iterator findPair(typename C::iterator big, C &c) {
	if (c.size() < 2) return c.end();
	for (std::size_t i = 0; i + 1 < c.size(); i += 2) {
		if (c[i + 1] == *big)
			return c.begin() + i;
	}
	return c.end();
}

template <typename C>
static void insertSmallBeforeBig(C &main, int small, int big) {
    typename C::iterator itBig = std::find(main.begin(), main.end(), big);
    if (itBig == main.end()) return;

    typename C::iterator pos = std::lower_bound(main.begin(), itBig, small);
    main.insert(pos, small);
}

template <typename C>
void PmergeMe::putPendInMain(C &main, C &pend, C &ogMain) {
	std::size_t size = pend.size();
	std::vector<int> jacobOrder;
	PmergeMe::jacobsthalOrder(size, jacobOrder);

	int minBig = *main.begin();
	int first = -1;
	while (++first < static_cast<int>(size)) {
		if (ogMain[first] == minBig) break;
	}
	main.insert(main.begin(), pend[first]);
	
	for (std::size_t j = 0; j < jacobOrder.size(); j++) {
		int toDo = jacobOrder[j];
		if (toDo == first + 1) continue;

        int big   = ogMain[toDo - 1];
        int small = pend[toDo - 1];
		insertSmallBeforeBig(main, small, big);
	}
}

template <typename C>
void PmergeMe::fordJohnson(C &c) {
	if (c.size() <= 1) return;

    C main;
	C pend;
    PmergeMe::sortPairsAndPush(c, main, pend);

    bool hasStraggler = (c.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) straggler = c.back();

    // recursif pour trier main
    C ogMain = main;
    PmergeMe::fordJohnson(main);

    PmergeMe::putPendInMain(main, pend, ogMain);

    if (hasStraggler) {
        typename C::iterator pos = std::lower_bound(main.begin(), main.end(), straggler);
        main.insert(pos, straggler);
    }

    c = main;
}

#endif