#include "Base.hpp"

Base::~Base() {}

Base* generate() {
    static bool one = false;
    if (!one) {
		std::srand(std::time(0));// init la séquence de rand
		one = true;
	}

    int r = std::rand() % 3;
    switch (r) {
        case 0: return new A;
        case 1: return new B;
        case 2: return new C;
    }
	return NULL;
}

void identify(Base *p) {
    if (!p) {
		std::cout << "Null pointer" << std::endl;
		return;
	}
    if (dynamic_cast<A*>(p)) // renvoie ptr ou 0
		std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
    else
		std::cout << "Unknown" << std::endl;
}

void identify(Base &p) {
    try {
		(void)dynamic_cast<A&>(p); // renvoie la ref ou throw
		std::cout << "A" << std::endl; return;
	} catch (...) {}
    try {
		(void)dynamic_cast<B&>(p); std::cout << "B" << std::endl;
		return;
	} catch (...) {}
    try {
		(void)dynamic_cast<C&>(p); std::cout << "C" << std::endl;
		return;
	} catch (...) {}
    std::cout << "Unknown" << std::endl;
}