#include <iostream>
#include <BitcoinExchange.hpp>

/*
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | 1
2012-01-11 | 2
2013-03-15 | 500.5
2013-03-15 | 1000
2009-01-02 | 1
2024-12-31 | 0.5
2012-01-11 | -1
2012-01-11 | 2147483648
2012-01-11 | 1001
2012-01-11 | 0
2001-42-42
2011-13-01 | 1
2011-00-01 | 1
2011-01-32 | 1
2011-01-00 | 1
2011/01/03 | 1
2011-01-03 | abc
2011-01-03 | 1.2abc
2011-01-03 | 1 2
2008-01-01 | 1
   | 1
2011-01-03 |
| 1
2011-01-03 | -0.5
*/

int	main(int ac, char *av[]) {
	if (ac != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}

	BitcoinExchange btc;

	if (!btc.loadDatabase("data.csv"))
		return (1);
	btc.processInput(av[1]);

	return 0;
}