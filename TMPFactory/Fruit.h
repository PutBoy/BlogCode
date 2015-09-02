#pragma once

#include <string>
#include "Factory.h"

struct Fruit
{
	static void addCreators(Factory<Fruit, int>& factory);
	virtual ~Fruit() {};
	virtual int ripeness() = 0;
	virtual std::string what() = 0;
};