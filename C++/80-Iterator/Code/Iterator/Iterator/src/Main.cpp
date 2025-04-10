#include <iostream>
#include <vector>
#include <unordered_map>


int main()
{
	// 2. some examples
	// 2.1 range-based for loop
	std::vector<int> values1 = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < values1.size(); i++)
		std::cout << values1[i] << std::endl;

	for (int value1 : values1)
		std::cout << value1 << std::endl;

	// 2.2 std::vector<>::iterator
	std::vector<int> values2 = { 1, 2, 3, 4, 5 };

	for (std::vector<int>::iterator it = values2.begin(); it != values2.end(); it++)
		std::cout << *it << std::endl;

	// 2.4 iterate std::unordered_map<>
	// 2.4.1 const_iterator
	using ScoreMap = std::unordered_map<std::string, int>;
	ScoreMap map1;
	map1["xiaoli"] = 5;
	map1["C++"] = 2;

	for (ScoreMap::const_iterator it = map1.begin(); it != map1.end(); it++)
	{
		auto& key = it->first;
		auto& value = it->second;

		std::cout << key << " = " << value << std::endl;
	}

	// 2.4.2 range-based for loop
	ScoreMap map2;
	map2["xiaoli"] = 5;
	map2["C++"] = 2;

	for (auto kv : map2)  // "kv" is a "std::pair"
	{
		auto& key = kv.first;
		auto& value = kv.second;

		std::cout << key << " = " << value << std::endl;
	}

	// 2.4.3 range-based for loop with structured binding
	ScoreMap map3;
	map3["xiaoli"] = 5;
	map3["C++"] = 2;

	for (auto [key, value] : map3)
		std::cout << key << " = " << value << std::endl;
}
