#include <iostream>


// 2. some examples
namespace apple {

	void print(const std::string& text)
	{
		std::cout << text << std::endl;
	}

	void print_again()
	{
		std::cout << "print again" << std::endl;
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

// 2.3 nested namespace
namespace watermelon {

	namespace functions {

		void print(const std::string& text)
		{
			std::cout << text << std::endl;
		}

		void print_again()
		{
			std::cout << "print again" << std::endl;
		}
	}
}


int main()
{
	// 2.1 using a function in a namespace
	using apple::print;
	print("Hello");
	apple::print_again();
	//print_again();  // Wrong! error C3861: 'print_again': identifier not found

	// 2.2 create an alias for a namespace
	namespace a = apple;
	a::print("Hello");
	apple::print("Hello");

	// 2.3 nested namespace
	{
		watermelon::functions::print("Hello");
	}

	{
		using namespace watermelon::functions;
		print("Hello");
	}

	{
		using namespace watermelon;
		using namespace functions;
		print("Hello");
	}

	{
		namespace wf = watermelon::functions;
		wf::print("Hello");
	}
}
