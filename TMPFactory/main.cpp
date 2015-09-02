#include "Factory.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Fruit.h"

int main()
{
	std::vector<std::shared_ptr<Fruit>> fruits;
	Factory<Fruit, int> factory;
	Fruit::addCreators(factory);

	fruits.push_back(factory.create("Banana", 1));
	fruits.push_back(factory.create("Apple", 9000));
	fruits.push_back(factory.create("Orange", 42));
	fruits.push_back(factory.create("Apple", -14));

	for (auto& fruit : fruits)
	{
		std::cout << fruit->what() << " - " << fruit->ripeness() << "\n";
	}

}