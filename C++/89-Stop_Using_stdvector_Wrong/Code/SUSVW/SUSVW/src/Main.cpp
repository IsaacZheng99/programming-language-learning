#include <iostream>
#include <vector>
#include <array>


// 2. some examples
// 2.1 fixed count of elements
struct Color
{
	int x, y, z;
};

const Color RED = { 1, 2, 3 };
const Color YELLOW = { 1, 2, 4 };
const Color BLUE = { 1, 2, 5 };

std::vector<Color> GetAllColors1()
{
	return { RED, YELLOW, BLUE };
}

std::array<Color, 3> GetAllColors2()
{
	return { RED, YELLOW, BLUE };
}

static int s_AllocationCount = 0;

static int s_CopyCount = 0;

static int s_MoveCount = 0;

// 2.2 allocation for std::vector<>
struct Data
{
	int Value = 0;

	Data() = default;

	Data(int value)
		: Value(value) {
	}

	// 2.2.3 the copy problem
	Data(const Data& other)
		: Value(other.Value)
	{
		std::cout << "Copied Data\n";
		s_CopyCount++;
	}

	// 2.2.4 the move problem
	Data(Data&& other)
		: Value(other.Value)
	{
		std::cout << "Moved Data\n";
		s_MoveCount++;
	}
};

static void PrintVector1(std::vector<Data> vector)
{
	std::cout << "Size: " << vector.size() << std::endl;

	if (vector.empty())
		return;

	std::cout << "Elements: { ";
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i].Value;
		if (i < vector.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }\n";
}

void* operator new(size_t size)
{
	std::cout << "Allocated " << size << " bytes\n";
	s_AllocationCount++;
	return malloc(size);
}

// 2.2.1 don't copy std::vector<> unless we need to
static void PrintVector2(const std::vector<Data>& vector)
{
	std::cout << "Size: " << vector.size() << std::endl;

	if (vector.empty())
		return;

	std::cout << "Elements: { ";
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i].Value;
		if (i < vector.size() - 1)
			std::cout << ", ";
	}
	std::cout << " }\n";
}


int main()
{
	// 2. some examples
	// 2.2 allocation for std::vector<>
	std::vector<Data> vector1;
	// 2.2.2 estimate the maximum size if we can
	vector1.reserve(5);

	for (int i = 0; i < 5; i++)
		vector1.push_back(Data(i));

	//PrintVector1(vector1);
	// 2.2.1 don't copy std::vector<> unless we need to
	PrintVector2(vector1);

	std::cout << s_AllocationCount << " allocations\n";

	//std::vector<Data> vector2;
	//vector2.resize(5);
	//for (int i = 0; i < 5; i++)
	//	vector2[i] = Data(i);
	//PrintVector2(vector2);
	//std::cout << s_AllocationCount << " allocations\n";

	//std::vector<Data> vector3(5);
	//for (int i = 0; i < 5; i++)
	//	vector3[i] = Data(i);
	//PrintVector2(vector3);
	//std::cout << s_AllocationCount << " allocations\n";

	// 2.2.3 the copy problem
	std::vector<Data> vector4;
	vector4.reserve(5);
	for (int i = 0; i < 5; i++)
		vector4.emplace_back(i);
	PrintVector2(vector4);
	std::cout << s_AllocationCount << " allocations\n";
	std::cout << s_CopyCount << " copies\n";

	// 2.2.4 the move problem
	std::vector<Data> vector5;
	vector5.reserve(5);
	for (int i = 0; i < 5; i++)
		vector5.push_back(Data(i));
	PrintVector2(vector5);
	std::cout << s_AllocationCount << " allocations\n";
	std::cout << s_CopyCount << " copies\n";
	std::cout << s_MoveCount << " moves\n";

	std::vector<Data> vector6;
	vector6.reserve(5);
	for (int i = 0; i < 5; i++)
		vector6.emplace_back(i);
	PrintVector2(vector6);
	std::cout << s_AllocationCount << " allocations\n";
	std::cout << s_CopyCount << " copies\n";
	std::cout << s_MoveCount << " moves\n";
}
