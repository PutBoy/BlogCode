#pragma once

#include <string>
#include <vector>
#include <set>

std::vector<std::string> Tokenize(const std::string& str)
{
	bool nextUnary = true;
	std::vector<std::string> tokens;
	std::string currentNumber;
	std::set<char> operators;
	for (auto op : "+-/*()")
	{
		operators.insert(op);
	}
	for (auto chr: str)
	{
		if (chr <= ' ')
			continue;
		if (chr >= '0' && chr <= '9')
		{
			currentNumber.push_back(chr);
			nextUnary = false;
		}
		else if (operators.count(chr) == 1)
		{
			std::string token;
			if (!currentNumber.empty())
				tokens.push_back(currentNumber);
			if (nextUnary && chr == '-')
				token.push_back('U');
			token.push_back(chr);
			tokens.push_back(token);
			currentNumber.clear();
			nextUnary = true;
		}
	}

	return std::move(tokens);
}