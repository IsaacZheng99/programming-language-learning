#pragma once

#include <iostream>

// 2.4 use macro to write the function names automatically
#define PROFILING_4 1
#if PROFILING_4
#define PROFILE_SCOPE_4(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION_4() PROFILE_SCOPE_4(__FUNCTION__)
#else
#define PROFILE_SCOPE_4(name)
#define PROFILE_FUNCTION_4()
#endif

void Function7()
{
	PROFILE_FUNCTION_4();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}

void Function8()
{
	PROFILE_FUNCTION_4();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks4()
{
	PROFILE_FUNCTION_4();
	std::cout << "Running Benchmarks...\n";

	Function7();
	Function8();
}
