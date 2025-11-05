#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {(void)other;}

RPN &RPN::operator=(const RPN &other) {
	(void)other;
	return *this;
}

RPN::~RPN() {} // inutile mais je laisse pour le OCF

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::calculate(char *input) {
	std::string s(input);
	std::list<int> li;
	bool sp = false;
	for (std::size_t i = 0; i < s.length(); i++) {
		if (std::isspace(s[i]))
			sp = false;
		else if (std::isdigit(s[i])) {
			if (sp)
				throw std::runtime_error("Error");
			li.push_back(s[i] - '0');
			sp = true;
		}
		else if (isOperator(s[i])) {
			if (sp)
				throw std::runtime_error("Error");
			if (li.size() < 2)
				throw std::runtime_error("Error");
			int b = li.back();
			li.pop_back();
			int a = li.back();
			li.pop_back();
			long res = 0;
			if (s[i] == '+')
				res = a + b;
			else if (s[i] == '-')
				res = a - b;
			else if (s[i] == '*')
				res = a * b;
			else if (s[i] == '/') {
				if (b == 0)
					throw std::runtime_error("Error");
				res = a / b;
			}
			else
				throw std::runtime_error("Error");
			sp = true;
			li.push_back(res);
		}
		else
			throw std::runtime_error("Error");
	}
	if (li.size() != 1)
			throw std::runtime_error("Error");
	return li.back();
}