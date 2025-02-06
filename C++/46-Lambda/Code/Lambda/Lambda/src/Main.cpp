#include <iostream>
#include <vector>
#include <functional>


void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
	for (int value : values)
		func(value);
}


int main()
{
	// 2. when to use lambda
	std::vector<int> values = { 5, 4, 3, 2, 1 };
	int a = 10;

	// 2.1 copy capture (pass by value)
	auto lambda1 = [=](int value) { std::cout << a << std::endl; };
	ForEach(values, lambda1);

	// 2.2 key word mutable
	//auto lambda2 = [=](int value) { a = 5; std::cout << a << std::endl; };  // Wrong! error C3491: 'a': a by copy capture cannot be modified in a non-mutable lambda
	//ForEach(values, lambda2);

	auto lambda2 = [=](int value) mutable { a = 5; std::cout << a << std::endl; };
	ForEach(values, lambda2);

	// 2.3 used in std api
	std::vector<int> numbers = { 1, 4, 3, 2, 5 };
	auto it = std::find_if(numbers.begin(), numbers.end(), [](int value) { return value > 3; });
	std::cout << *it << std::endl;
}
