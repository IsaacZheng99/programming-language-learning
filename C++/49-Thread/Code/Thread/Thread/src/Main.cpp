#include <iostream>
#include <thread>
#include <chrono>


static bool s_Finished = false;


void DoWork()
{
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;

	while (!s_Finished)
	{
		std::cout << "Working...\n";
		std::this_thread::sleep_for(1s);
	}
}


int main()
{
	// 2. an example: we want to print "Working..." all the time untill we press the "enter"
	std::thread worker(DoWork);

	std::cin.get();  // manually block the main thread
	s_Finished = true;

	worker.join();

	std::cout << "Finished!" << std::endl;
	std::cout << "Started therad id = " << std::this_thread::get_id() << std::endl;
}
