#include <iostream>
#include <any>
#include <variant>


// 3.5 dynamic allocation
void* operator new(size_t size)
{
	return malloc(size);  // breakpoint here
}

class Custom
{
	std::string s;
	float f;
	char c;
};


int main()
{
	// 3. some example
	// 3.1 std::any
	std::any data1;
	data1 = 1;
	data1 = "xiaoli";
	data1 = std::string("xiaoli");
	//std::cout << data1 << std::endl;  // Wrong! Compiling error

	// 3.2 std::any_cast<>()
	std::any data2;
	data2 = 1;
	data2 = std::string("xiaoli");

	std::string value = std::any_cast<std::string>(data2);
	std::cout << value << std::endl;

	// 3.3 std::any vs. std::variant<>
	std::any data3;
	data3 = 1;
	data3 = "xiaoli";
	//std::string anyValue = std::any_cast<std::string>(data3);  // Wrong! Runtime error
	//std::cout << anyValue << std::endl;

	std::variant<int, std::string> data4;
	data4 = 1;
	data4 = "xiaoli";
	std::string variantValue = std::get<std::string>(data4);  // implicit conversion
	std::cout << variantValue << std::endl;

	// 3.4 reference in std::any_cast<>() and std::get<>()
	std::any data5;
	data5 = std::string("xiaoli");
	std::string& anyData1 = std::any_cast<std::string&>(data5);
	//std::string& anyData2 = std::any_cast<std::string>(data5);  // Wrong! Compiling error. error C2440: 'initializing': cannot convert from 'std::basic_string<char,std::char_traits<char>,std::allocator<char>>' to 'std::string &'

	std::variant<int, std::string> data6;
	data6 = "xiaoli";
	std::string& variantData1 = std::get<std::string>(data6);
	//std::string& variantData2 = std::get<std::string&>(data6);  // Wrong! Compiling error. error C2440: 'initializing': cannot convert from 'void' to 'std::string &'

	// 3.5 dynamic allocation
	std::any data7;
	data7 = Custom();
}
