#include <iostream>


// 2. examples of marco
// 2.1 replace a whole statement
#define WAIT std::cin.get()

#define OPEN_CURLY {

// 2.2 send parameter
//#ifdef MY_DEBUG
#if MY_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
//#else
#elif defined(MY_RELEASE)
#define LOG(x)
#endif

// 2.4 make a whole function
#define MAIN int main()\
{\
	std::cout << "MAIN marco!" << std::endl;\
}


// 2. examples of marco
// 2.1 replace a whole statement
//int main()
//OPEN_CURLY
//	WAIT;
//}


//int main()
//{
//	// 2.2 send parameter
//	LOG("Hello!");
//}


// 2.4 make a whole function
MAIN
