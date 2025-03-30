#pragma once

#include <iostream>
#include "Timer.h"


// 2.1.3 benchmarking
void Function1()
{
	InstrumentationTimer timer("Function1");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}

void Function2()
{
	InstrumentationTimer timer("Function2");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}
