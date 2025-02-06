#include <iostream>
#include <vector>


// 1. some examples
// 1.1 distinguish your own "functions" from the "std functions"
void ForEach()
{

}

void for_each()
{

}

void find_if()
{

}

// 1.3 silent runtime error
namespace apple {

	void print(const std::string& text)
	{
		std::cout << text << std::endl;
	}
}

namespace orange {

	void print(const char* text)
	{
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}


int main()
{
	// 1. some examples
	// 1.1 distinguish your own "functions" from the "std functions"
	ForEach();
	for_each();
	find_if();
	//std::find_if();  // How to distinguish if there is not "std::" ?

	// 1.2 distinguish your own "containers" from the "std containers"
	std::vector<int> v1;
	//eastl::vector<int> v2;

	//vector<int> v3;  // Which namespace? Maybe we need to check the "using namespace" code which is far away.
	// 1.3 silent runtime error
	using namespace apple;
	using namespace orange;

	print("Hello");
	print(std::string("Hello"));
}
