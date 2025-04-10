#include <iostream>
#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"


int main()
{
	// 2. custom iterator
	// 2.1 normal traverse
	Vector1<float> values1;
	values1.EmplaceBack(1.0f);
	values1.EmplaceBack(2.0f);
	values1.EmplaceBack(3.0f);
	values1.EmplaceBack(4.0f);
	values1.EmplaceBack(5.0f);

	std::cout << "Not using iterator:\n";
	for (int i = 0; i < values1.Size(); i++)
		std::cout << values1[i] << std::endl;

	// 2.2 add iterator basics: template, pointer, begin(), and end()

	// 2.3 add operators to manipulate custom iterator
	Vector2<float> values2;
	values2.EmplaceBack(1.0f);
	values2.EmplaceBack(2.0f);
	values2.EmplaceBack(3.0f);
	values2.EmplaceBack(4.0f);
	values2.EmplaceBack(5.0f);

	std::cout << "Range-based for loop:\n";
	for (float value : values2)
		std::cout << value << std::endl;

	std::cout << "Iterator:\n";
	for (Vector2<float>::Iterator it = values2.begin(); it != values2.end(); it++)
		std::cout << *it << std::endl;

	// 2.4 fix the ReAlloc() bug
	Vector3<std::string> values3;
	values3.EmplaceBack("1");
	values3.EmplaceBack("2");
	values3.EmplaceBack("3");
	values3.EmplaceBack("4");
	values3.EmplaceBack("5");

	std::cout << "Range-based for loop:\n";
	for (std::string value : values3)
		std::cout << value << std::endl;

	std::cout << "Iterator:\n";
	for (Vector3<std::string>::Iterator it = values3.begin(); it != values3.end(); it++)
		std::cout << *it << std::endl;
}
