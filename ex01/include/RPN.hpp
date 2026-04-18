#pragma once

# include <string>
# include <stack>

class RPN
{
	private:
		bool isOperator(const std::string &token) const;
		bool isOperand(const std::string &token) const;
		int  applyOperator(const std::string &op, int a, int b) const;
	public:
		RPN();
		RPN(const RPN &rhs);
		RPN &operator=(const RPN &rhs);
		~RPN();

		void evaluate(const std::string &expression);

};