#include <PmergeMe.hpp>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iostream>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &rhs) : _V(rhs._V), _D(rhs._D) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
	if (this != &rhs) {
		_V = rhs._V;
		_D = rhs._D;
	}
	return (*this);
}

namespace { void trim(std::string &str)
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");

	if (start == std::string::npos || end == std::string::npos)
		str.clear();
	else
		str = str.substr(start, end - start + 1);
} }

namespace { bool check_double(const std::vector<unsigned int> &vect) {
	std::vector<unsigned int> tmp(vect);
	std::vector<unsigned int>::iterator it = tmp.begin();
	std::vector<unsigned int>::iterator ite = tmp.end();
	std::sort(it, ite);
	std::vector<unsigned int>::iterator comp = std::adjacent_find(it, ite);
	if (comp != ite) {
		std::cerr << "Error: duplicate entry: " << *comp << std::endl;
		return (false);
	}
	return (true);
} }

bool PmergeMe::insert(const std::string &toinsert){
	std::istringstream	iss(toinsert);
	unsigned long		insert;
	if (!(iss >> insert))
		return (false);
	if (insert > UINT_MAX || insert == 0) {
		std::cerr << "Error: " << toinsert << " out of bound" << std::endl;
		return (false);
	}
	_V.push_back(insert);
	_D.push_back(insert);
	return (true);
}

bool PmergeMe::parser(char *arg[], int ac) {
	std::string		toparse;

	for (int i = 1; i != ac; i++) {
		toparse = arg[i];
		trim(toparse);
		if (toparse.find_first_not_of("0123456789") != std::string::npos) {
			std::cerr << "Error: arg[" << i << "] isn't a valid argument: " << arg[i] << std::endl;
			return (false);
		}
		if(!insert(toparse)) {
			std::cerr << "Error: conversion failed arg[" << i << "]: " << arg[i] << std::endl;
			return (false);
		}
	}
	if (!check_double(_V))
		return (false);
	return (true);
}

std::vector<size_t> jacobsthalOrder(size_t pendSize)
{
	std::vector<size_t> j;

	j.push_back(0);
	j.push_back(1);

	for (size_t i = 2; i <= pendSize; i++)
		j.push_back(j[i - 1] + 2 * j[i - 2]);
	return (j);
}

std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> seq) {
	if (seq.size() <= 1)
		return (seq);

	unsigned int soloVal = 0;
	bool hasSolo = seq.size() % 2;
	if (hasSolo)
		soloVal = seq.back();
	std::vector<std::pair<unsigned int, unsigned int> > pairz;
	for (size_t i = 1; i != seq.size(); i+= 2) {
		bool ordr = (seq[i] > seq[i-1]);
		pairz.push_back(std::make_pair((ordr ? seq[i-1] : seq[i]), ordr ? seq[i] : seq[i-1]));
	}
	std::vector<unsigned int> main;
	std::vector<unsigned int> pend;
	std::vector<std::pair<unsigned int, unsigned int> >::iterator it;
	for (it = pairz.begin(); it != pairz.end(); it++) {
		main.push_back(it->second);
		pend.push_back(it->first);
	}
	main = fordJohnson(main);
	std::vector<size_t>jacobsthal(jacobsthalOrder(pend.size()));
	std::vector<unsigned int>ordre;
	unsigned int k  = 1;
	while (ordre.size() != pend.size()) {
		for (size_t i = jacobsthal[k]; i != jacobsthal[k-1]+1; i--) {
			if (i <= pend.size())
				ordre.push_back(i-1);
		}
		k++;
	}
	return (main);
}

std::deque<unsigned int> fordJohnson(std::deque<unsigned int> seq) {
	
}

void PmergeMe::printRunTime(const time_t &start, const time_t &end, bool vector) {
	std::cout << "Time to process a range of " << _V.size() << " elements with std::";
	if (vector)
		std::cout << "vector<unsigned int> : ";
	else
		std::cout << "deque<unsigned int> : ";
	std::cout << start - end << " us" << std::endl;
}

void PmergeMe::run() {
	time_t start, end;

	print(true);
	start = time(NULL);
	fordJohnson(_V);
	end = time(NULL);
	print(false);
	printRunTime(start, end, true);
	start = time(NULL);
	fordJohnson(_D);
	end = time(NULL);
	printRunTime(start, end, false);
}

void PmergeMe::print(bool before) {
	if (before)
		std::cout << "Before: ";
	else
		std::cout << "After: ";
	std::vector<unsigned int>::iterator it;
	for (it = _V.begin(); it != _V.end() - 1; it++) {
		std::cout << *it << " ";
	}
	std::cout << _V.back() << std::endl;
}
