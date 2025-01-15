#include <iostream>
#include "Log.h"

// 2. value of enum
enum Example1
{
	A1, B1, C1
};

enum Example2
{
	A2 = 1, B2, C2
};

enum Example3
{
	A3 = 2, B3 = 5, C3 = 8
};

// 3. type of enum
enum Example4  // by default, int
{
	A4, B4, C4
};

enum Example5 : char
{
	A5, B5, C5
};

//enum Example6
//{
//	A6 = 0.1f, B6, C6  // Wrong! Compiling error.
//};

// 4. enum class
enum class Example7
{
	A7, B7, C7
};

enum class Example8
{
	A8, B8, C8
};

int main()
{
	// 2. value of enum
	Example1 value1 = Example1::B1;
	//Example1 value2 = 2;  // Wrong! Compiling error.
	Example1 value3 = C1;

	// 3. type of enum
	std::cout << sizeof(Example4) << std::endl;
	std::cout << sizeof(Example5) << std::endl;

	// 4. enum class
	Example7 value7 = Example7::A7;
	//Example7 value8 = B7;  // Wrong! Compiling error.
	//Example7 value9 = 2;  // Wrong! Compiling error.
	//int b = Example7::B7;  // Wrong! Compiling error.

	// 6. improve class Log with enum
	Log log;
	log.SetLevel(Log::LevelError);
	log.Error("Hello!");
	log.Warn("Hello!");
	log.Info("Hello!");
}
