#include "Tokenization.h"
#include "Parsing.h"
#include "RPN.h"
#include <iostream>

int main()
{
	auto RPN = [](const std::string& expr){return calculate(parse(Tokenize(expr))).second; };
	
	std::cout << RPN("3*-(2+1)") << "\n";  //should equal -9
	std::cout << RPN("9/(3*(2-1))") << "\n";  //should equal 3
	std::cout << RPN("(1+1)*(33-12)") << "\n";  //should equal 42
	std::cout << "yey!";  

}

