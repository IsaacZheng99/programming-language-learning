#pragma once

#include <iostream>


// 2.5 use __FUNCSIG__ to avoid same names of functions
#define PROFILING_5 1
#if PROFILING_5
#define PROFILE_SCOPE_5(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION_5() PROFILE_SCOPE_5(__FUNCSIG__)
#else
#define PROFILE_SCOPE_5(name)
#define PROFILE_FUNCTION_5()
#endif

void Function9(int value)
{
	PROFILE_FUNCTION_5();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i + value << std::endl;
}

void Function9()
{
	PROFILE_FUNCTION_5();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks5()
{
	PROFILE_FUNCTION_5();
	std::cout << "Running Benchmarks...\n";

	Function9(1);
	Function9();
}
