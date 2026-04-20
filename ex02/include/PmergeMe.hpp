#pragma once

#include <deque>
#include <vector>

class PmergeMe {
	private:
		std::vector<unsigned int>	_V;
		std::deque<unsigned int>	_D;

		std::vector<unsigned int> fordJohnson(std::vector<unsigned int> seq);
		std::deque<unsigned int> fordJohnson(std::deque<unsigned int> seq);
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &rhs);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &rhs);

		bool parser(char *arg[], int ac);
		bool insert(const std::string &toinsert);
		void run();
		void print(bool before);
		void printRunTime(const time_t &start, const time_t &end, bool vector);
};