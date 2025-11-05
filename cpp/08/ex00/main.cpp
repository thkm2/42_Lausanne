#include "easyfind.hpp"

int main() {
	std::vector<int> v;
	v.push_back(10);
	v.push_back(42);
	v.push_back(80);
	std::vector<int>::iterator it = easyfind(v, 42);

	if (it != v.end()) {
        std::cout << "Found: " << *it << "\n";
    } else {
        std::cout << "Not found\n";
    }

	std::list<int> l;
	l.push_back(2);
	l.push_back(4);
	l.push_back(6);
	l.push_back(8);
	std::list<int>::iterator lit = easyfind(l, 63);

	if (lit != l.end()) {
        std::cout << "Found: " << *lit << "\n";
    } else {
        std::cout << "Not found\n";
    }

	return 0;
}