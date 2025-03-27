#include <iostream>


// 2,1 old way: std::tuple<> + std::get<>
std::tuple<std::string, int> CreatePerson()
{
	return { "xiaoli", 26 };
}

// 2.4 struct vs. structured bindings
std::tuple<std::string, std::string> ReturnTwoStrings()
{
	// do something and get two strings
	std::string fs = "fs";
	std::string ss = "ss";

	return { fs,ss };
}


int main()
{
	// 2,1 old way: std::tuple<> + std::get<>
	auto person1 = CreatePerson();
	std::string name1 = std::get<0>(person1);
	int age1 = std::get<1>(person1);
	std::cout << name1 << " " << age1 << std::endl;

	// 2.2 std::tuple<> + std::tie
	std::string name2;
	int age2;
	std::tie(name2, age2) = CreatePerson();
	std::cout << name2 << " " << age2 << std::endl;

	// 2.3 structured bindings
	auto [name3, age3] = CreatePerson();
	std::cout << name3 << " " << age3 << std::endl;

	// 2.4 struct vs. structured bindings
	auto [firstString, secondString] = ReturnTwoStrings();
	std::cout << firstString << " " << secondString << std::endl;
}
