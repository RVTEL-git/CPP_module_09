#include <PmergeMe.hpp>
#include <iostream>

int main(int ac, char *av[]) {
	if (ac < 3) {
		std::cerr << "Error: Not enough args" << std::endl;
		return (1);
	}
	else {
		PmergeMe toSort;
		if (!toSort.parser(av, ac))
			return (1);
		toSort.run();
		return (0);
	}
}