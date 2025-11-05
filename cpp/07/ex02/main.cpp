#include "Array.hpp"

#include <iostream>
#include <string>

template <typename T>
void printArray(const Array<T> &a, std::string name) {
	for (unsigned int i = 0; i < a.size(); i++) {
		std::cout << name << "["<< i << "] : " << a[i] << std::endl;
	}
}

int main() {
	Array<int> a(3);
	std::cout << "a size : " << a.size() << std::endl;
	printArray(a, "a");
	a[0] = 22;
	a[1] = 42;
	a[2] = 100;
	std::cout << std::endl;
	printArray(a, "a");

	std::cout << std::endl;
	std::cout << std::endl;

	Array<int> b(1);
	printArray(b, "b");
	std::cout << std::endl;
	b = a;
	printArray(b, "b");

	std::cout << std::endl;
	b[0] = 200;
	printArray(a, "a");
	std::cout << std::endl;
	printArray(b, "b");
	return 0;
}