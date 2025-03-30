#pragma once

#include <string>


// 2. some examples
// 2.1 directly benchmark two functions
// 2.1.1 session
struct ProfileResult  // profile class
{
	std::string Name;
	long long Start, End;
};

// 2.7 multi-thread
// 2.7.1 session
struct MultiThreadProfileResult
{
	std::string Name;
	long long Start, End;
	uint32_t ThreadID;
};
