#include <iostream>
#include <array>
#include <algorithm>


// 2. advantages of std::array<>
// 2.1 keep track of the size
void PrintArray(int* array, unsigned int size)
{
	for (int i = 0; i < size; i++)
	{

	}
}

void PrintArray(const std::array<int, 5>& data)
{
	//for (int i = 0; i < 5; i++)
	for (int i = 0; i < data.size(); i++)
	{

	}
}

template <int N>
void PrintArray(const std::array<int, N>& data)
{
	for (int i = 0; i < N; i++)
	{

	}
}

template <typename T, int N>
void PrintArray(const std::array<T, N>& data)
{
	for (int i = 0; i < N; i++)
	{

	}
}

template <typename T>
void PrintArray(const T& data)
{
}


int main()
{
	// 1. std::array<>
	// 1.2 compare with C-style raw array
	int array1[5];
	array1[0] = 1;

	std::array<int, 5> array2;
	array2[0] = 1;

	// 2. advantages of std::array<>
	// 2.1 keep track of the size

	// 2.2 support the iterator
	std::array<int, 5> array3({ 1, 2, 3, 4, 5 });
	for (auto it = array3.begin() + 1; it != array3.end() - 1; it++)
		std::cout << *it << std::endl;

	// 2.3 support STL algorithms
	std::array<int, 5> array4({ 5, 2, 3, 4, 1 });
	std::sort(array4.begin(), array4.end());
	for (int value : array4)
		std::cout << value << std::endl;

	// 2.4 support bounds checking
	int array5[5];
	std::array<int, 5> array6;
	//array5[5] = 1;  // Wrong!
	//array6[5] = 1;  // Wrong!
	//std::cout << array6.at(5) << std::endl;  // Wrong!
}
