#include <iostream>


// 4. string as parameter
void PrintString1(std::string string)
{
	string += "Hello";
	std::cout << string << std::endl;
}

void PrintString2(const std::string& string)
{
	std::cout << string << std::endl;
}

int main()
{
	// 2. raw string
	const char* name1 = "xiaoli";
	std::cout << name1 << std::endl;
	char name2[6] = { 'x', 'i','a','o','l','i' };
	std::cout << name2 << std::endl;
	char name3[7] = { 'x', 'i','a','o','l','i', '\0' };
	std::cout << name3 << std::endl;
	char name4[7] = { 'x', 'i','a','o','l','i', 0 };
	std::cout << name4 << std::endl;

	// 3. std::string
	// 3.1 size of string
	std::string name5 = "xiaoli";
	std::cout << name5.size() << std::endl;
	char* name6 = (char*)"xiaoli";
	std::cout << strlen(name6) << std::endl;

	std::string name7 = "xiao\0li";
	std::cout << name7 << std::endl;
	std::cout << name7.size() << std::endl;

	const char* name8 = "xiao\0li";
	std::cout << name8 << std::endl;
	std::cout << strlen(name8) << std::endl;
	std::cout << sizeof(name8) << std::endl;

	char name9[] = "xiao\0li";
	std::cout << name9 << std::endl;
	std::cout << strlen(name9) << std::endl;
	std::cout << sizeof(name9) << std::endl;

	std::string name10(name9, sizeof(name9) - 1);
	std::cout << name10 << std::endl;
	std::cout << name10.size() << std::endl;
	for (int i = 0; i < name10.size(); i++)
		std::cout << name10[i] << ", ";
	std::cout << std::endl;

	// 3.2 string appending
	//std::string name11 = "xiaoli" + "Hello";  // Wrong! Compiling error. Here we are trying to add two "const char*", but we can't add two pointers.

	std::string name12 = "xiaoli";
	name12 += "Hello";
	std::cout << name12 << std::endl;

	std::string name13 = (std::string)"xiaoli" + "Hello";
	std::cout << name13 << std::endl;

	// 3.3 find
	std::string name14 = "xiaoli";
	if (name14.find("oli") != std::string::npos)
		std::cout << "In!" << std::endl;

	// 4. string as parameter
	std::string name15 = "xiaoli";
	PrintString1(name15);
	std::cout << name15 << std::endl;
}
