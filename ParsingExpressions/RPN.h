#pragma once

#include "Token.h"
#include <vector>
#include <utility>

int pop(std::vector<int>& stack)
{
	int ret = stack.back();
	stack.pop_back();
	return ret;
}

std::pair<bool, int> calculate(const std::vector<Token>& queue)
{
	std::vector<int> stack;
	std::pair<bool, int> ret = { true, 0 };

	for (auto token : queue)
	{
		if (token.type == Token::Type::Number)
			stack.push_back(token.token.value);
		else if (token.type == Token::Type::Operator)
		{
			switch (token.token.op)
			{
			case (Token::OpType::Add):
				if (stack.size() >= 2)
					stack.push_back(pop(stack) + pop(stack));
				else
					ret.first = false;
				break;	
			case (Token::OpType::Sub) :
				if (stack.size() >= 2)
					stack.push_back(-(pop(stack) - pop(stack)));
				else
					ret.first = false;
				break;
			case (Token::OpType::Pos) :
				if (stack.size() >= 1)
					stack.push_back(pop(stack));
				else
					ret.first = false;
				break;
			case (Token::OpType::Neg) :
				if (stack.size() >= 1)
					stack.push_back(-pop(stack));
				else
					ret.first = false;
				break;
			case (Token::OpType::Mul) :
				if (stack.size() >= 2)
					stack.push_back(pop(stack) * pop(stack));
				else
					ret.first = false;
				break;
			case (Token::OpType::Div) :
				if (stack.size() >= 2)
				{
					int d = pop(stack);
					stack.push_back(pop(stack) / d);
				}
				else
					ret.first = false;
				break;
			default:
				ret.first = false;
				break;
			}
		}
	}

	if (stack.size() == 1)
		ret.second = stack.back();
	else
		ret.first = false;

	return ret;
}