#include <iostream>


// 3. template parameter
template<typename T>
void Print(T value)
{
	std::cout << value << std::endl;
}

// 4. template in a class
// 4.1 template an integer
template<int N>
class Array1
{
private:
	int array[N];
public:
	int GetSize() const
	{
		return N;
	}
};

// 4.2 template the data type
template<typename T, int N>
class Array2
{
private:
	T array[N];
public:
	int GetSize() const
	{
		return N;
	}
};


int main()
{
	// 3. template parameter
	Print(5);
	Print<int>(5);

	Print("Hello");
	Print<std::string>("Hello");
	//Print<std::string>(1);  // Wrong! error C2664: 'void Print<std::string>(T)': cannot convert argument 1 from 'int' to 'T'

	Print(5.5f);

	// 4. template in a class
	// 4.1 template an integer
	Array1<5> array1;
	std::cout << array1.GetSize() << std::endl;
	// 4.2 template the data type
	Array2<int, 10> array2;
	std::cout << array2.GetSize() << std::endl;
}
