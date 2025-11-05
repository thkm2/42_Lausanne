#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <exception>
#include <cstdlib>
#include <cctype>

typedef struct s_input_line_values {
	std::string	date;
	double		value;
} t_input_line_values;

class BitcoinExchange {
	private:
		std::map<std::string, double> _data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void loadData();
		void parseLine(std::string line, t_input_line_values &ilv) const;
		void printOutput(t_input_line_values &ilv) const;
};

#endif