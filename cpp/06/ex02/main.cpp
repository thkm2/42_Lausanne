#include "Base.hpp"

int main() {
    for (int i = 0; i < 5; ++i) {
        Base* p = generate();
        std::cout << "[ptr ]: "; identify(p);
        std::cout << "[ref ]: "; identify(*p);
		std::cout << std::endl;
        delete p;
    }
    return 0;
}