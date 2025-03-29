#include <iostream>


// 2. how std::string allocates
static uint32_t s_AllocCount = 0;

void* operator new(size_t size)  // overloading "operator new" is a good way to track the allocation
{
	s_AllocCount += 1;
	std::cout << "Allocating " << size << " bytes\n";
	return malloc(size);
}

void PrintName(const std::string& name)
{
	std::cout << name << std::endl;
}

// 3. std::string_view
void PrintNameByStringview(std::string_view name)
{
	std::cout << name << std::endl;
}

int main()
{
	// 2. how std::string allocates
	// 2.1 print a std::string
	std::string name1 = "xiaoli";
	PrintName(name1);
	std::cout << s_AllocCount << " allocations\n";

	// 2.2 directly pass a const char*
	PrintName("xiaoli");
	std::cout << s_AllocCount << " allocations\n";

	// 2.3 a more complicated example
	std::string name2 = "xiaoli";
	std::string firstName1 = name2.substr(0, 4);
	std::string lastName1 = name2.substr(4, 6);
	PrintName(firstName1);
	PrintName(name2.substr(0, 4));
	std::cout << s_AllocCount << " allocations\n";

	// 3. std::string_view
	std::string name3 = "xiaoli";  // create a std::string at first
	std::string_view firstName2(name3.c_str(), 4);
	std::string_view lastName2(name3.c_str() + 4, 2);
	PrintNameByStringview(firstName2);
	std::cout << s_AllocCount << " allocations\n";

	const char* name4 = "xiaoli";  // directly use a const char*
	std::string_view firstName3(name4, 4);
	std::string_view lastName3(name4 + 4, 2);
	PrintNameByStringview(firstName3);
	PrintNameByStringview("xiaoli");
	std::cout << s_AllocCount << " allocations\n";
}
