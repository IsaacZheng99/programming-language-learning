#include <iostream>


// 2. memory allocation
// 2.1 stack
struct Vector3
{
	float x, y, z;

	Vector3()
		: x(10), y(11), z(12) {
	}
};


int main()
{
	// 2. memory allocation
	// 2.1 stack
	// check the memory
	int value = 5;
	int array[5];
	for (int i = 0; i < 5; i++)
		array[i] = i;
	Vector3 vector;
	std::cout << &value << std::endl;
	std::cout << array << std::endl;
	std::cout << &vector << std::endl;

	// 2.2 heap
	// compare the memory
	int* hvalue = new int;
	*hvalue = 5;
	int* harray = new int[5];
	for (int i = 0; i < 5; i++)
		harray[i] = i;
	Vector3* hvector = new Vector3();
	std::cout << hvalue << std::endl;
	std::cout << harray << std::endl;
	std::cout << hvector << std::endl;
	delete hvalue;
	delete[] harray;
	delete hvector;
}
