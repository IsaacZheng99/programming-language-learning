#include <iostream>


// 2. some examples
void* operator new(size_t size)
{
	std::cout << "Allocating " << size << " bytes\n";
	return malloc(size);
}


int main()
{
	// 2. some examples
	// 2.1 a small string
	std::string name1 = "xiaoli";

	// 2.2 a 15-character-long string
	std::string name2 = "xiaoli666666666";

	// 2.3 a big string
	std::string name3 = "xiaoli6666666666";
}
