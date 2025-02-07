#include <iostream>
#include <chrono>
#include <thread>


// 2. an example: we want to time two functions to compare the speeds of "std::endl" and "\n"
struct Timer
{
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << ms << "ms" << std::endl;
	}
};

void Function1()
{
	Timer timer;

	for (int i = 0; i < 100; i++)
	{
		std::cout << "Hello" << std::endl;
	}
}

void Function2()
{
	Timer timer;

	for (int i = 0; i < 100; i++)
	{
		std::cout << "Hello\n";
	}
}


int main()
{
	// 1. some std apis
	using namespace std::literals::chrono_literals;

	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1s);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;
	std::cout << duration.count() << "s" << std::endl;

	// 2. an example: we want to time two functions to compare the speeds of "std::endl" and "\n"
	Function1();
	Function2();
}
