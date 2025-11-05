#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>
#include <exception>
#include <cctype>

class RPN {
	private:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();
	public:
		static int calculate(char *input);
};

#endif