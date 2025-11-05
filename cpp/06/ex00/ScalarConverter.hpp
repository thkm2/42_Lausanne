#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>
#include <iomanip> // std::fixed() + setprecision
#include <limits> // std::numeric_limits
#include <cctype> // std::isprint
#include <cstdlib> // std::atol

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);
		~ScalarConverter(); // pas besoin -> pas instanciable -> private -> mais OCF
	public:
		static void convert(const std::string &s);
};


#endif