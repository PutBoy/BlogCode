#pragma once

#include <memory>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

template <class T, class ... Params>
class Factory
{
public:
	std::shared_ptr<T> create(const std::string& str, Params... params)
	{
		auto found = creators.find(str);
		if (found != creators.end())
			return found->second(params...);
		else
			return nullptr;
	}

	template <class U>
	void addCreator(std::string str)
	{
		creators.insert(std::make_pair(str, [&](Params... params) -> std::shared_ptr<U> {return std::make_shared<U>(params...); }));
	}

private:
	std::map<std::string, std::function<std::shared_ptr<T>(Params...)>> creators;
};
