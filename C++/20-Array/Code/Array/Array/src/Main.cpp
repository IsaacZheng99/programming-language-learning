#include <iostream>
#include <array>


// 4. why need new
//int* Function()
//{
//	int array[5];
//	int* ptr = array;
//
//	return ptr;
//}

int* FunctionWithNew()
{
	int* ptr = new int[5];

	return ptr;
}

// 5. memory indirection
class Entity1
{
public:
	int example[5];

	Entity1()
	{
		example[2] = 1;
	}
};

class Entity2
{
public:
	int* example = new int[5];

	Entity2()
	{
		example[2] = 1;
	}
};

// 6. size of array
class Entity3
{
public:
	int example[5];

	int GetCount()
	{
		return sizeof(example) / sizeof(int);  // count = 5 * 4 / 4
	}
};

class Entity4
{
public:
	int* example = new int[5];

	int GetCount()
	{
		return sizeof(example) / sizeof(int);  // count = 4 / 4
	}
};

class Entity5
{
public:
	static const int exampleElementCount = 5;
	int* example = new int[exampleElementCount];

	int GetCount()
	{
		return exampleElementCount;
	}
};

// 6. std::array<>
class Entity6
{
public:
	std::array<int, 5> example;

	int GetCount()
	{
		return example.size();
	}

};

int main()
{
	// 3. how array stores data
	int example[5];
	int* ptr = example;

	example[2] = 1;  // set the third element to 1
	std::cout << example[2] << std::endl;
	*(ptr + 2) = 2;  // set the third element to 2
	std::cout << example[2] << std::endl;
	*(int*)((char*)ptr + 8) = 100000;  // set the third element to 10000
	std::cout << example[2] << std::endl;
	*((char*)ptr + 8) = 100000;
	std::cout << example[2] << std::endl;

	// 4. why need new
	//int* returnPtr = Function();  // Warning!
	int* ptrToNew = FunctionWithNew();
	delete[] ptrToNew;

	// 5. memory indirection
	Entity1 e1;
	Entity2 e2;

	// 6. size of array
	Entity3 e3;
	std::cout << e3.GetCount() << std::endl;
	Entity4 e4;
	std::cout << e4.GetCount() << std::endl;
	Entity5 e5;
	std::cout << e5.GetCount() << std::endl;
	Entity6 e6;
	std::cout << e6.GetCount() << std::endl;
}
