#include "RPN.hpp"
#include <iostream>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &rhs) { (void)rhs; }

RPN &RPN::operator=(const RPN &rhs) { (void)rhs; return *this; }

RPN::~RPN() {}

bool RPN::isOperand(const std::string &token) const
{
	return (token.length() == 1 && token[0] >= '0' && token[0] <= '9');
}

bool RPN::isOperator(const std::string &token) const
{
	return (token.length() == 1 &&
			(token[0] == '+' || token[0] == '-' ||
			token[0] == '*' || token[0] == '/'));
}

int RPN::applyOperator(const std::string &op, int a, int b) const
{
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error: division by zero.");
		return a / b;
	}
	throw std::runtime_error("Error");
}

void RPN::evaluate(const std::string &expression)
{
	std::stack<int>		stack;
	std::istringstream	iss(expression);
	std::string			token;
	int					tokenCount = 0;

	while (iss >> token)
	{
		tokenCount++;
		if (isOperand(token))
		{
			stack.push(token[0] - '0');
			continue;
		}
		if (isOperator(token))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error");

			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();

			stack.push(applyOperator(token, a, b));
			continue;
		}
		throw std::runtime_error("Error");
	}

	if (stack.size() != 1 || tokenCount == 1)
		throw std::runtime_error("Error");

	std::cout << stack.top() << std::endl;
}