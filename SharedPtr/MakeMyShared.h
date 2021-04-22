#pragma once

#include <iostream>
#include"SharedPtr.h"

class Person
{
private:
	std::string name;
	size_t age;

public:
	Person(std::string name, size_t age)
		: name(std::move(name)), age(age)
	{
	}

	const std::string& GetName() const { return name; }
	size_t GetAge() const { return age; }
};

SharedPtr<Person> MakeMyShared(std::string name, size_t age)
{
	return SharedPtr<Person>(new Person(name, age), false);
}
