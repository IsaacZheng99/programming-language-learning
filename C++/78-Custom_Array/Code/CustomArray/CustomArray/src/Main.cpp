#include <iostream>
#include <array>
#include "Array1.h"
#include "Array2.h"
#include "Array3.h"
#include "Array4.h"
#include "Array5.h"
#include "Array6.h"


int main()
{
	// 1. raw array
	int array1[5];

	int size = 5;
	//int array2[size];  // Wrong! Compiling error. error C2131: expression did not evaluate to a constant
	int* array3 = (int*)alloca(size * sizeof(int));

	int* heapArray1 = new int[5];
	int* heapArray2 = new int[size];

	delete[] heapArray1;
	delete[] heapArray2;

	// 2. std::array<>
	std::array<int, 5> collection;
	int arraySize = collection.size();
	for (int value : collection)
		std::cout << value << std::endl;
	for (int i = 0; i < collection.size(); i++)
		std::cout << collection[i] << std::endl;

	// 3. custom array
	// 3.1 two template arguments and Size() function
	Array1<int, 5> data1;
	//static_assert(data1.Size() < 10, "Size is too long!");  // Wrong! Compiling error. error C2131: expression did not evaluate to a constant
	//Array1<std::string, data1.Size()> newArray1;  // Wrong! Compiling error. error C2975: 'S': invalid template argument for 'Array1', expected compile-time constant expression

	// 3.2 add constexpr key word
	Array2<int, 5> data2;
	static_assert(data2.Size() < 10, "Size is too long!");
	Array1<std::string, data2.Size()> newArray2;

	// 3.3 add operator[]
	Array3<int, 5> data3;
	for (int i = 0; i < data3.Size(); i++)
	{
		std::cout << data3[i] << std::endl;
		//data3[i] = 0;  // Wrong! Compiling error. error C2106: '=': left operand must be l-value
	}

	// 3.4 add reference to the return value of operator[]
	Array4<int, 5> data4;
	for (int i = 0; i < data4.Size(); i++)
	{
		std::cout << data4[i] << std::endl;
		data4[i] = 0;
	}

	const auto& referenceArray4 = data4;
	for (int i = 0; i < referenceArray4.Size(); i++)
	{
		//std::cout << referenceArray4[i] << std::endl;  // Wrong! Compiling error. error C2678: binary '[': no operator found which takes a left-hand operand of type 'const Array4<int,5>' (or there is no acceptable conversion)
		//referenceArray4[i] = 0;  // Wrong! Compiling error. error C2678: binary '[': no operator found which takes a left-hand operand of type 'const Array4<int,5>' (or there is no acceptable conversion)
	}

	// 3.5 add const T& operator[]
	Array5<int, 5> data5;
	for (int i = 0; i < data5.Size(); i++)
	{
		std::cout << data5[i] << std::endl;
		data5[i] = 0;
	}

	const auto& referenceArray5 = data5;
	for (int i = 0; i < referenceArray5.Size(); i++)
	{
		std::cout << referenceArray5[i] << std::endl;
		//referenceArray5[i] = 0;  // Wrong! Compiling error. error C3892: 'referenceArray5': you cannot assign to a variable that is const
	}

	// 3.6 Data() function to access the data
	Array6<int, 6> data6;
	memset(data6.Data(), 0, data6.Size() * sizeof(int));
	//memset(&data6[0], 0, data6.Size() * sizeof(int));

	for (int i = 0; i < data6.Size(); i++)
	{
		std::cout << data6[i] << std::endl;
	}

	const auto& referenceArray6 = data6;
	for (int i = 0; i < referenceArray6.Size(); i++)
	{
		std::cout << referenceArray6.Data()[i] << std::endl;
	}
}
