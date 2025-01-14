#include <iostream>


void Increment1(int value)
{
	value++;
}

void Increment2(int& value)
{
	value++;
}

void Increment3(int* value)
{
	(*value)++;
}

int main()
{
	// 1. reference
	int a = 1;
	int& ref = a;
	std::cout << ref << std::endl;
	ref = 2;
	std::cout << a << std::endl;
	std::cout << ref << std::endl;

	// 2. pass by value, reference, pointer (address)
	int value1 = 1;
	int value2 = 1;
	int value3 = 1;
	Increment1(value1);
	Increment2(value2);
	Increment3(&value3);
	std::cout << value1 << std::endl;
	std::cout << value2 << std::endl;
	std::cout << value3 << std::endl;

	// 4. when declare a reference, it should be initialized
	int v = 1;
	int& r1 = v;

	// int& r2;  // Wrong!

	// 5. don't change what a reference references
	int v1 = 1;
	int v2 = 2;
	int& r = v1;
	r = v2;
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << r << std::endl;
}