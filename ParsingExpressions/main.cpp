#include "Tokenization.h"
#include "Parsing.h"
#include "RPN.h"
#include <iostream>
#include "AST.h"

int main()
{
	auto RPN = [](const std::string& expr){return calculate(parse(Tokenize(expr))).second; };
	auto AST = [](const std::string& expr){return makeTree(parse(Tokenize(expr))); };

	std::cout << AST("9/(3*(2-1))")->evaluate() << "\n";
	std::cout << AST("(1+1)*(33-12 * (2 - 1))")->evaluate() << "\n";

	std::cout << "yey!";  
}

