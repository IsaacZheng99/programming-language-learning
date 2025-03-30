#pragma once

#include <iostream>
#include <thread>


// 2.7 multi-thread
#define PROFILING_7 1
#if PROFILING_7
#define PROFILE_SCOPE_7(name) InstrumentationTimer timer##__LINE__(name, true)
#define PROFILE_FUNCTION_7() PROFILE_SCOPE_7(__FUNCSIG__)
#else
#define PROFILE_SCOPE_7(name)
#define PROFILE_FUNCTION_7()
#endif

namespace Benchmark7 {

	void Function11(int value)
	{
		PROFILE_FUNCTION_7();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << i + value << std::endl;
	}

	void Function11()
	{
		PROFILE_FUNCTION_7();
		for (int i = 0; i < 1000; i++)
			std::cout << "Hello World #" << sqrt(i) << std::endl;
	}

	void RunBenchmarks7()
	{
		PROFILE_FUNCTION_7();
		std::cout << "Running Benchmarks...\n";

		std::thread a([]() { Function11(1); });
		std::thread b([]() { Function11(); });

		a.join();
		b.join();
	}
}
