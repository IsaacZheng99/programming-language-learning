#include <iostream>
#include <array>
#include <vector>


// 1. use input parameters
// 1.1 use reference
void ReturnTwoStrings(std::string& outFirstString, std::string& outSecondString)
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	// this is kind of good and you just need to copy here
	outFirstString = fs;
	outSecondString = ss;
}

// 1.2 use pointer
void ReturnTwoStrings(std::string* outFirstString, std::string* outSecondString)
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	if (outFirstString)
		*outFirstString = fs;
	if (outSecondString)
		*outSecondString = ss;
}

// 2. return an array
// 2.1 return a raw array
std::string* ReturnTwoStringsWithRawArray()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return new std::string[2]{ fs,ss };  // note that in the returning place we can't know how big the array is
	// and we have done heap allocation here
}

// 2.2 return a std::array<>
std::array<std::string, 2> ReturnTwoStringsWithStdArray()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return std::array<std::string, 2>{ fs, ss };
}

// 2.3 return a std::vector<>
std::vector<std::string> ReturnTwoStringsWithStdVector()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return std::vector<std::string>{ fs, ss };
}

// 3. return a std::tuple<>
std::tuple<std::string, std::string> ReturnTwoStringsWithStdTuple()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return std::tuple<std::string, std::string>{ fs, ss };
}

// 4. return a std::pair<>
std::pair<std::string, std::string> ReturnTwoStringsWithStdPair()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return std::pair<std::string, std::string>{ fs, ss };
}

// 5. return a struct
struct TwoStrings
{
	// we can name it as we need, not like std::pair<>, here just for simplicity
	std::string FirstString;
	std::string SecondString;
};

TwoStrings ReturnTwoStringsWithStruct()
{
	// do something and get two std::string
	std::string fs = "fs";
	std::string ss = "ss";

	return { fs, ss };
}


int main()
{
	// 1. use input parameters
	// 1.1 use reference
	std::string fs, ss;
	ReturnTwoStrings(fs, ss);
	std::cout << fs << std::endl;
	std::cout << ss << std::endl;

	// 1.2 use pointer
	ReturnTwoStrings(&fs, &ss);
	std::cout << fs << std::endl;
	std::cout << ss << std::endl;
	ReturnTwoStrings(nullptr, &ss);  // only focus on the second std::string

	// 2. return an array
	// 2.1 return a raw array
	std::string* twoStrings1 = ReturnTwoStringsWithRawArray();
	std::cout << twoStrings1[0] << std::endl;
	std::cout << twoStrings1[1] << std::endl;

	// 2.2 return a std::array<>
	std::array<std::string, 2> twoStrings2 = ReturnTwoStringsWithStdArray();
	std::cout << twoStrings2[0] << std::endl;
	std::cout << twoStrings2[1] << std::endl;

	// 2.3 return a std::vector<>
	std::vector<std::string> twoStrings3 = ReturnTwoStringsWithStdVector();
	std::cout << twoStrings3[0] << std::endl;
	std::cout << twoStrings3[1] << std::endl;

	// 3. return a std::tuple<>
	std::tuple<std::string, std::string> twoStrings4 = ReturnTwoStringsWithStdTuple();
	std::cout << std::get<0>(twoStrings4) << std::endl;
	std::cout << std::get<1>(twoStrings4) << std::endl;

	// 4. return a std::pair<>
	std::pair<std::string, std::string> twoStrings5 = ReturnTwoStringsWithStdPair();
	std::cout << std::get<0>(twoStrings5) << std::endl;
	std::cout << std::get<1>(twoStrings5) << std::endl;
	std::cout << twoStrings5.first << std::endl;
	std::cout << twoStrings5.second << std::endl;

	// 5. return a struct
	TwoStrings twoStrings6 = ReturnTwoStringsWithStruct();
	std::cout << twoStrings6.FirstString << std::endl;
	std::cout << twoStrings6.SecondString << std::endl;
}
