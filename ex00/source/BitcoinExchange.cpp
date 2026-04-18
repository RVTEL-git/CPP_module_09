#include <BitcoinExchange.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

enum ValueError { VALUE_BAD_INPUT = -1, VALUE_NEGATIVE, VALUE_TOO_LARGE, VALUE_OK};

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs) : _db(rhs._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	if (this != &rhs)
		_db = rhs._db;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream	dataBase(filename.c_str());

	if (!dataBase) {
		std::cerr << "Data base opening failed" << std::endl;
		return (false);
	}
	std::string line;
	getline(dataBase, line);
	while (getline(dataBase, line)) {
		std::istringstream ss(line);
		std::string date;
		double price;

		if (getline(ss, date, ',') && (ss >> price))
			_db[date] = price;
	}
	dataBase.close();
	return (true);
}


void trimspace(std::string &str)
{
	size_t start = str.find_first_not_of(" ");

	size_t end = str.find_last_not_of(" ");

	if (start == std::string::npos || end == std::string::npos)
	{
		str.clear();
	}
	else
	{
		str = str.substr(start, end - start + 1);
	}
}

double BitcoinExchange::getBitcoinRate(const std::string &date)
{
	std::map<std::string, float>::iterator it = _db.lower_bound(date);

	if (it == _db.end())
	{
		--it;
	}
	else if (it->first != date)
	{
		if (it == _db.begin())
			return -1.0;
		--it;
	}
	return it->second;
}


bool BitcoinExchange::isValidValue(const std::string &value, const std::string &line, float &out)
{
	std::istringstream iss(value);
	double num;
	char leftover;
	if (!(iss >> num) || (iss >> leftover))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return false;
	}
	if (num < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (num > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	out = static_cast<float>(num);
	return true;
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int year, month, day;
	char dash1, dash2;
	std::istringstream ss(date);

	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return false;

	if (month < 1 || month > 12)
		return false;

	int daysInMonth[] = {31,
		((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28,
		31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (day < 1 || day > daysInMonth[month - 1])
		return false;

	return true;
}


void BitcoinExchange::processInput(const std::string& filename) {
	std::ifstream	InputFile(filename.c_str());

	if (!InputFile) {
		std::cerr << "Input file opening failed" << std::endl;
		return ;
	}

	std::string line;
	bool headerParsed = false;

	while (getline(InputFile, line))
	{
		if (!headerParsed) {
			headerParsed = true;
			if (line != "date | value") {
				std::cerr << "Error: Input file format is incorrect.\nFirst line must be 'date | value'." << std::endl;
				return;
			}
			continue;
		}
		if (line.empty())
			continue;

		std::istringstream ss(line);
		std::string date, valueStr;
	
		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		trimspace(date);
		trimspace(valueStr);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		float value;
		if (!isValidValue(valueStr, line, value))
			continue;

		double rate = getBitcoinRate(date);
		if (rate < 0)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
}