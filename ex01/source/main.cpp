#include "RPN.hpp"
#include <iostream>

/*
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   # 42
./RPN "7 7 * 7 -"                     # 42
./RPN "1 2 * 2 / 2 * 2 4 - +"        # 0

./RPN "1 1 +"                         # 2
./RPN "9 1 -"                         # 8
./RPN "3 3 *"                         # 9
./RPN "8 2 /"                         # 4

./RPN "1 9 -"                         # -8

./RPN "9 9 *"                         # 81

./RPN "5 5 -"                         # 0
./RPN "0 9 *"                         # 0

./RPN "3 4 + 2 * 7 /"                 # 2
./RPN "5 1 2 + 4 * + 3 -" 

./RPN "3 4"
./RPN "3 4 5 +"
./RPN "3 4 + 5 6"

./RPN "9"
*/

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try
	{
		RPN rpn;
		rpn.evaluate(av[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}