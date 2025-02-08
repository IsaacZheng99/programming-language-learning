#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
	// 2.1 ascending order by default
	std::vector<int> values1 = { 3, 5, 1, 4, 2 };
	std::sort(values1.begin(), values1.end());

	for (int value : values1)
		std::cout << value << std::endl;

	// 2.2 descending order
	std::vector<int> values2 = { 3, 5, 1, 4, 2 };
	std::sort(values2.begin(), values2.end(), std::greater<int>());

	for (int value : values2)
		std::cout << value << std::endl;

	// 2.3 ascending order by lambda
	std::vector<int> values3 = { 3, 5, 1, 4, 2 };
	std::sort(values3.begin(), values3.end(), [](int a, int b) { return a < b; });

	for (int value : values3)
		std::cout << value << std::endl;

	// 2.4 descending order by lambda
	std::vector<int> values4 = { 3, 5, 1, 4, 2 };
	std::sort(values4.begin(), values4.end(), [](int a, int b) { return a > b; });

	for (int value : values4)
		std::cout << value << std::endl;

	// 2.5 if we want to put 1 at the last place
	//std::vector<int> values5 = { 3, 5, 1, 4, 2 };
	//std::sort(values5.begin(), values5.end(), [](int a, int b) { return a > 1; });  // Wrong! runtime error

	//for (int value : values5)
	//	std::cout << value << std::endl;

	std::vector<int> values6 = { 3, 1, 1, 4, 2 };
	std::sort(values6.begin(), values6.end(), [](int a, int b)
		{
			if (a == 1)
				return false;
			if (b == 1)
				return true;
			return false;
		});

	for (int value : values6)
		std::cout << value << std::endl;
}
