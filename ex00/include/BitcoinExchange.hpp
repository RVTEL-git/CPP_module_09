#pragma once

#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::map<std::string, float> _db;
		double getBitcoinRate(const std::string &date);
		bool isValidValue(const std::string &value, const std::string &line, float &out);
		bool isValidDate(const std::string &date);
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &rhs);
		BitcoinExchange& operator=(const BitcoinExchange &rhs);
		~BitcoinExchange();

		bool loadDatabase(const std::string& filename);
		void processInput(const std::string& filename);
};
