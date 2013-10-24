#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include <exception>
#include <algorithm>
#include <map>

std::vector<Token> toTokens(const std::vector<std::string>& tokens)
{
	std::vector<Token> ret;
	for (auto& token : tokens)
	{
		if (token.size() == 0)
			continue;
		if (token[0] >= '0' && token[0] <= '9')
		{
			if (std::find_if(token.begin(), token.end(),
				[](char test) {return !(test >= '0' && test <= '9'); })
				!= token.end())
				continue; //not all numerals, abort!
			Token t;
			t.type = Token::Type::Number;
			t.token.value = atoi(token.c_str());
			ret.push_back(t);
		}
		else if (token[0] == 'U')
		{
			if (token.size() == 1)
				continue;
			if (token[1] == '-' || token[1] == '+')
			{
				Token t;
				t.type = Token::Type::Operator;
				t.token.op = Token::OpType::Neg;
				ret.push_back(t);
			}
		}
		else
		{
			Token t;
			t.type = Token::Type::Operator;
			switch (token[0])
			{
			case '+':
				t.token.op = Token::OpType::Add;
				break;
			case '-':
				t.token.op = Token::OpType::Sub;
				break;
			case '*':
				t.token.op = Token::OpType::Mul;
				break;
			case '/':
				t.token.op = Token::OpType::Div;
				break;
			case '\\':
				t.token.op = Token::OpType::Div;
				break;
			case '(':
				t.token.op = Token::OpType::LParen;
				break;
			case ')':
				t.token.op = Token::OpType::RParen;
				break;
			default:
				continue;
			}
			ret.push_back(t);
		}
	}
	return ret;
}

std::vector<Token> parse(const std::vector<std::string>& tokens)
{
	std::vector<Token> input = toTokens(tokens);
	std::vector<Token> operators;
	std::vector<Token> output;
	//:3 C++14:
	std::map<Token::OpType, int> precedence = 
	{ 
		{Token::Add, 4}, 
		{Token::Sub, 4},
		{Token::Pos, 2},
		{Token::Neg, 2},
		{Token::Mul, 3},
		{Token::Div, 3},
		{Token::LParen, 1},
		{Token::RParen, 1},
	};

	for (auto token : input)
	{
		if (token.type == Token::Number)
		{
			output.push_back(token);
		}
		else if (token.type == Token::Operator)
		{
			if (token.token.op == Token::OpType::LParen)
				operators.push_back(token);
			else if (token.token.op == Token::OpType::RParen)
			{
				bool foundOne = false;
				while (!operators.empty())
				{
					if (operators.back().token.op != Token::OpType::LParen)
					{
						output.push_back(operators.back());
						operators.pop_back();
					}
					else
					{
						foundOne = true;
						operators.pop_back();
						break;
					}
					if (!foundOne);
						//this is an indication of bad input. 
						//Ignore that for now
				}
			}
			else
			{
				bool unary = (token.token.op == Token::OpType::Pos ||
					token.token.op == Token::OpType::Neg);
				while (!operators.empty())
				{
					if (unary && precedence[operators.back().token.op]
						== precedence[token.token.op] &&
						operators.back().token.op != Token::OpType::LParen)
					{
						output.push_back(operators.back());
						operators.pop_back();
					}
					if (!unary && precedence[operators.back().token.op]
						>= precedence[token.token.op] &&
						operators.back().token.op != Token::OpType::LParen)
					{
						output.push_back(operators.back());
						operators.pop_back();
					}
					else
						break;
				}
				operators.push_back(token);
			}
			
		}
	}
	while (!operators.empty())
	{
		//finding any Parens  here is an indication of bad input, here
		//we simply opt out of pushing that unto the stack.
		if (operators.back().token.op != Token::OpType::LParen ||
			operators.back().token.op != Token::OpType::RParen)
			output.push_back(operators.back());
		operators.pop_back();
	}
	return output;
}