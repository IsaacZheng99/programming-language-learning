#include <iostream>
#include <GLFW/glfw3.h>


// 3.6.4 add extern "C"
//extern "C" int glfwInit();


int main()
{
	int a = glfwInit();
	std::cout << a << std::endl;
}
