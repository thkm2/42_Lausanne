#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		_data = other._data;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadData() {
	std::ifstream data_file("data.csv");
	if (!data_file.is_open())
		throw std::runtime_error("Error: could not open data file.");
	std::string line;
	while (std::getline(data_file, line)) {
		if (line == "date,exchange_rate") continue;
		std::string date = line.substr(0, 10);
		double		rate = std::strtod(line.substr(11).c_str(), 0);
		_data[date] = rate;
	}
}

static bool isDateYYYYMMDD(const std::string& d) {
    if (d.size() != 10) return false;
    if (d[4] != '-' || d[7] != '-') return false;
	int tab[8] = {0,1,2,3,5,6,8,9};
    for (int i = 0; i < 8; i++) {
        if (!std::isdigit((d[tab[i]]))) return false;
    }
	int y = (d[0]-'0')*1000 + (d[1]-'0')*100 + (d[2]-'0')*10 + (d[3]-'0');
    int m = (d[5]-'0')*10   + (d[6]-'0');
    int day = (d[8]-'0')*10 + (d[9]-'0');
    if (m < 1 || m > 12) return false;
    int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool biss = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
    if (biss) mdays[1] = 29;
    return day >= 1 && day <= mdays[m - 1];
}

void BitcoinExchange::parseLine(std::string line, t_input_line_values &ilv) const {
	std::string date = line.substr(0, 10);
	if (!isDateYYYYMMDD(date))
		throw std::runtime_error("Error: bad input => " + date);

	if (line.length() < 14 || line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		throw std::runtime_error("Error: bad input");

	char *end = NULL;
	std::string sub = line.substr(13);
	const char *str = sub.c_str();
	double value = std::strtod(str, &end);
	if (end == str)
		throw std::runtime_error("Error: missing number.");
	if (*end)
		throw std::runtime_error("Error: not a number.");
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (value > 1000)
		throw std::runtime_error("Error: too large a number.");

	ilv.date = date;
	ilv.value = value;
}

void BitcoinExchange::printOutput(t_input_line_values &ilv) const {
	std::map<std::string, double>::const_iterator it = _data.lower_bound(ilv.date);
	double rate = 0;
	if (it != _data.end() && it->first != ilv.date) {
		if (it == _data.begin())
			throw std::runtime_error("Error: no matching date");
		it--;
	}
	if (it == _data.end())
		it--;
	rate = it->second;
	std::cout << ilv.date << " => " << ilv.value << " = " << rate * ilv.value << std::endl;
}