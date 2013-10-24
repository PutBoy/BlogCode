#include "Fruit.h"

struct Apple;
struct Banana;
struct Orange;

void Fruit::addCreators(Factory<Fruit, int>& factory)
{
	factory.addCreator<Banana>("Banana");
	factory.addCreator<Orange>("Orange");
	factory.addCreator<Apple>("Apple");
}

struct Apple : public Fruit
{
	Apple(int ripeness) : ripeness_(ripeness) {};
	std::string what()
	{
		return "Apple!";
	}

	int ripeness()
	{
		return ripeness_;
	}

private:
	int ripeness_;
};

struct Banana : public Fruit
{
	Banana(int ripeness) : ripeness_(ripeness) {};
	std::string what()
	{
		return "Banana!";
	}

	int ripeness()
	{
		return ripeness_;
	}

private:
	int ripeness_;
};

struct Orange : public Fruit
{
	Orange(int ripeness) : ripeness_(ripeness) {};
	std::string what()
	{
		return "Orange!";
	}

	int ripeness()
	{
		return ripeness_;
	}

private:
	int ripeness_;
};
