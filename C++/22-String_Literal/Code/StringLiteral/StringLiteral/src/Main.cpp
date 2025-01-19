#include <iostream>


int main()
{
	// 2. const section
	//char* name1 = (char*)"xiaoli";
	//name1[0] = 'a';
	//std::cout << name1 << std::endl;

	char name2[] = "xiaoli";
	name2[0] = 'a';
	std::cout << name2 << std::endl;

	const char* name3 = "xiaoli";

	// 3. other types of character
	const char8_t* name4 = u8"xiaoi";
	const wchar_t* name5 = L"xiaoli";
	const char16_t* name6 = u"xiaoli";
	const char32_t* name7 = U"xiaoli";

	// 4. string appending
	using namespace std::string_literals;

	std::string name8 = "xiaoli"s + "Hello";
	std::wstring name9 = L"xiaoli"s + L"Hello";
	std::u32string name10 = U"xiaoli"s + U"Hello";

	const char* txt1 = R"(Line1
Line2
Line3)";
	std::cout << txt1 << std::endl;

	const char* txt2 = "Line1\n"
		"Line2\n"
		"Line3";
	std::cout << txt2 << std::endl;

	const char* txt3 = "Line1"
		"Line2"
		"Line3";
	std::cout << txt3 << std::endl;
}
