#pragma once

#include <iostream>
#include <thread>


// 2.8 multi-thread and call a function
#define PROFILING_8 1
#if PROFILING_8
#define PROFILE_SCOPE_8(name) InstrumentationTimer timer##__LINE__(name, true)
#define PROFILE_FUNCTION_8() PROFILE_SCOPE_8(__FUNCSIG__)
#else
#define PROFILE_SCOPE_8(name)
#define PROFILE_FUNCTION_8()
#endif

namespace Benchmark7 {

	void Function12(int value)
	{
		PROFILE_FUNCTION_8();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << i + value << std::endl;
	}

	void Function12()
	{
		PROFILE_FUNCTION_8();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << sqrt(i) << std::endl;
	}

	void RunBenchmarks8()
	{
		PROFILE_FUNCTION_8();
		std::cout << "Running Benchmarks...\n";

		std::thread a([]() { Function12(1); });

		Function12();

		a.join();
	}
}
