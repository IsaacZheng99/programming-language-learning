#pragma once

#include <iostream>


// 2.6 add a namespace to specify the scope
#define PROFILING_6 1
#if PROFILING_6
#define PROFILE_SCOPE_6(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION_6() PROFILE_SCOPE_6(__FUNCSIG__)
#else
#define PROFILE_SCOPE_6(name)
#define PROFILE_FUNCTION_6()
#endif

namespace Benchmark6 {

	void Function10(int value)
	{
		PROFILE_FUNCTION_6();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << i + value << std::endl;
	}

	void Function10()
	{
		PROFILE_FUNCTION_6();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << sqrt(i) << std::endl;
	}

	void RunBenchmarks6()
	{
		PROFILE_FUNCTION_6();
		std::cout << "Running Benchmarks...\n";

		Function10(1);
		Function10();
	}
}
