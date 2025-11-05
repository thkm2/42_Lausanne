#include "ScalarConverter.hpp"

// INUTILE --------------
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) {
	(void)other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
	(void)other;
	return *this;
}
ScalarConverter::~ScalarConverter() {}
// ---------------------- (mais là au cas où)

bool isSpecial(const std::string &s) {
    if (s.empty()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return(true);
    }
    if (s == "nan" || s == "nanf") { // not a number (ex: 0/0)
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return(true);
    }
    if (s == "+inf" || s == "inf" || s == "+inff" || s == "inff") { // infini postif
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
        return(true);
    }
    if (s == "-inf" || s == "-inff") { // infini négatif
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
        return(true);
    }
    return(false);
}

bool isChar(const std::string &s) {
    if (s.length() == 1 && !std::isdigit(s[0]))
        return (true);
    return (false);
}

void toChar(const std::string &s) {
    char c = s[0];
    if (std::isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

bool isInt(const std::string &s) {
    int i = 0;
    if (s[0] == '+' || s[0] == '-') {
        if (s.length() == 1) // juste signe seul, ex: "+"
            return false;
        i = 1;
    }
    int len = s.length();
    for (; i < len; i++) {
        if (!std::isdigit(s[i]))
            return (false);
    }
    return (true);
}

void toInt(const std::string &s) {
    long value = std::atol(s.c_str());
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;   
    }
    if (value >= std::numeric_limits<char>::min() && value <= std::numeric_limits<char>::max()) {
        char c = static_cast<char>(value);
        if (std::isprint(c))
            std::cout << "char: '" << c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    std::cout << "int: " << static_cast<int>(value) << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << std::endl;
}

bool isFloat(const std::string &s) {
    if (s == "-f" || s == "+f")
        return false;
    int len = s.length() - 1;
    if (s[len] != 'f')
        return (false);
    bool hasDecimal = false;
    int i = 0;
    if (s[0] == '+' || s[0] == '-')
        i = 1;
    for (; i < len; i++) {
        if (s[i] == '.') {
            if (hasDecimal)
                return (false);
            hasDecimal = true;
        }
        else if (!std::isdigit(s[i]))
            return (false);
    }
    if (hasDecimal == false)
        return (false);
    return (true);
}

void toFloat(const std::string &s) {
    std::string str = s.substr(0, s.length() - 1);
    double value = std::atof(str.c_str());
    if (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max()) { // -max() car min = plus petit positif pour float
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }
    if (value >= std::numeric_limits<char>::min() && value <= std::numeric_limits<char>::max() && value == static_cast<int>(value)) {
        char c = static_cast<char>(value);
        if (std::isprint(c))
            std::cout << "char: '" << c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max() && value == static_cast<long>(value))
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    else {
        std::cout << "int: impossible" << std::endl;
	}
	if (value == static_cast<long>(value))
    	std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    std::cout << "double: " << value << std::endl;
}

bool isDouble(const std::string &s) {
    int len = s.length();
    bool hasDecimal = false;
    int i = 0;
    if (s[0] == '+' || s[0] == '-')
        i = 1;
    for (; i < len; i++) {
        if (s[i] == '.') {
            if (hasDecimal)
                return (false);
            hasDecimal = true;
        }
        else if (!std::isdigit(s[i]))
            return (false);
    }
    if (hasDecimal == false)
        return (false);
    return (true);
}

void toDouble(const std::string &s) {
    double value = std::atof(s.c_str());
    if (value >= std::numeric_limits<char>::min() && value <= std::numeric_limits<char>::max() && value == static_cast<int>(value)) {
        char c = static_cast<char>(value);
        if (std::isprint(c))
            std::cout << "char: '" << c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max() && value == static_cast<long>(value))
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    else {
        std::cout << "int: impossible" << std::endl;
	}
	if (value == static_cast<long>(value))
    	std::cout << std::fixed << std::setprecision(1);
    if (value >= -std::numeric_limits<float>::max() && value <= std::numeric_limits<float>::max()) {
        std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    }
    else
        std::cout << "float: impossible" << std::endl;
    std::cout << "double: " << value << std::endl;
}

void ScalarConverter::convert(const std::string &s) {
	if (isSpecial(s))
        return ;
    else if (isChar(s))
        toChar(s);
    else if (isInt(s))
        toInt(s);
    else if (isFloat(s))
        toFloat(s);
    else if (isDouble(s))
        toDouble(s);
    else {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
    return ;
}