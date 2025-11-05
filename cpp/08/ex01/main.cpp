#include "Span.hpp"

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	Span notEnough(1);
	notEnough.addNumber(17);
	try {
		std::cout << "Exception : " << notEnough.shortestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	Span big(10000);
	std::vector<int> v;
	for (int i = 0; i < 10000; i++)
		v.push_back(i);
	big.addRange(v.begin(), v.end());
	std::cout << big.longestSpan() << std::endl;
	return 0;
}