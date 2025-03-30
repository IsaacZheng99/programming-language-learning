#pragma once

#include <iostream>


// 2.3 use marco to open or close the timer
#define PROFILING_3 1
#if PROFILING_3
#define PROFILE_SCOPE_3(name) InstrumentationTimer timer##__LINE__(name)  // "timer##__LINE__" can give different names to these "timer variables"
#else
#define PROFILE_SCOPE_3(name)
#endif

void Function5()
{
	PROFILE_SCOPE_3("Function5");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}

void Function6()
{
	PROFILE_SCOPE_3("Function6");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks3()
{
	PROFILE_SCOPE_3("RunBenchmarks3");
	std::cout << "Running Benchmarks...\n";

	Function5();
	Function6();
}
