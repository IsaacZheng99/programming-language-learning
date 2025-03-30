#pragma once

#include <iostream>
#include "Timer.h"


// 2.2 two functions stack-printing-like run
void Function3()
{
	InstrumentationTimer timer("Function3");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}

void Function4()
{
	InstrumentationTimer timer("Function4");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks2()
{
	InstrumentationTimer timer("RunBenchmarks2");
	std::cout << "Running Benchmarks...\n";

	Function3();
	Function4();
}
