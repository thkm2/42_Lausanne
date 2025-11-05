#include "iter.hpp"
#include <string>
#include <iostream>

template <typename T>
void printElement(const T &e) {
	std::cout << e << std::endl;
}

void increment(int &n) {
	n++;
}

int main() {
	std::string arr[3] = {"oui", "non", "arbitre"};
	iter(arr, 3, printElement);

	int arr2[4] = {10, 19, 100, -1};
	iter(arr2, 4, increment);
	iter(arr2, 4, printElement);
	return 0;
}