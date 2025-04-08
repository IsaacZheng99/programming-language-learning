#include <iostream>


// 2. an example of postfix-expression
void PrintSum(int a, int b)
{
	std::cout << a << " + " << b << " = " << a + b << std::endl;
}


int main()
{
	// 2. an example of postfix-expression
	int value = 0;
	PrintSum(value++, value++);
}
