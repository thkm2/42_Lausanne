#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    Bureaucrat b1("b1", 1);
    Bureaucrat b2("b2", 150);
    Form f1("form one", 50, 20);
    Form f2("f2", 1, 1);

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;

    try {
        Form bad1("bad1", 0, 10);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        Form bad2("bad2", 10, 151);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    b1.signForm(f2);
    std::cout << f2 << std::endl;

    b2.signForm(f1);
    std::cout << f1 << std::endl;

    return 0;
}

