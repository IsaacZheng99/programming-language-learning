#include <iostream>


// 3. const in a method or function
// 3.1 const in both method and function
class Entity1
{
private:
	int m_X, m_Y;
public:
	int GetX() const
	{
		return m_X;
	}
};

//void PrintEntity1X(const Entity1& e)
//{
//	e = Entity1();  // Wrong! error C2678: binary '=': no operator found which takes a left-hand operand of type 'const Entity1' (or there is no acceptable conversion)
//	std::cout << e.GetX() << std::endl;
//}

// 3.2 remove the const in the method
class Entity2
{
private:
	int m_X, m_Y;
public:
	int GetX()  // remove the "const" key word
	{
		return m_X;
	}
};

//void PrintEntity2X(const Entity2& e)
//{
//	std::cout << e.GetX() << std::endl;  // Wrong! error C2662: 'int Entity2::GetX(void)': cannot convert 'this' pointer from 'const Entity2' to 'Entity2 &'
//}

// 3.3 overload by const
class Entity3
{
private:
	int m_X, m_Y;
public:
	int GetX() const
	{
		std::cout << "GetX() with const" << std::endl;
		return m_X;
	}

	int GetX()
	{
		std::cout << "GetX() without const" << std::endl;
		return m_X;
	}
};

void PrintEntity3X(const Entity3& e)
{
	std::cout << e.GetX() << std::endl;
}

void PrintEntity3X(Entity3& e)
{
	std::cout << e.GetX() << std::endl;
}

int main()
{
	// 1. what const can do
	const int MAX_AGE = 100;
	std::cout << MAX_AGE << std::endl;

	int* a = new int;
	*a = 1;
	std::cout << *a << std::endl;

	// one way to break the promise of "const"
	a = (int*)&MAX_AGE;
	std::cout << *a << std::endl;
	*a = 10;
	std::cout << *a << std::endl;
	std::cout << MAX_AGE << std::endl;
	std::cout << a << std::endl;
	std::cout << &MAX_AGE << std::endl;

	// 2. const and pointer

	// 2.1 pointer to const
	// const int*
	const int* ptrToConst1 = new int;
	std::cout << *ptrToConst1 << std::endl;
	//*ptrToConst1 = 1;  // Wrong! error C3892: 'ptrToConst1': you cannot assign to a variable that is const
	int b = 2;
	ptrToConst1 = &b;
	std::cout << *ptrToConst1 << std::endl;
	// int const*
	int const* ptrToConst2 = new int;
	std::cout << *ptrToConst2 << std::endl;
	//*ptrToConst2 = 1;  // Wrong! error C3892: 'ptrToConst2': you cannot assign to a variable that is const
	ptrToConst2 = &b;
	std::cout << *ptrToConst2 << std::endl;

	// 2.2 const pointer
	int* const constPtr = new int;
	std::cout << *constPtr << std::endl;
	*constPtr = 1;
	std::cout << *constPtr << std::endl;
	//constPtr = &b;  // Wrong! error C3892: 'constPtr': you cannot assign to a variable that is const

	// 2.3
	// const int* const
	const int* const p1 = new int;
	//*p1 = 1;  // Wrong! error C3892: 'p1': you cannot assign to a variable that is const
	//p1 = &b;  // Wrong! error C3892: 'p1': you cannot assign to a variable that is const
	// int const* const
	int const* const p2 = new int;
	//*p2 = 1;  // Wrong! error C3892: 'p2': you cannot assign to a variable that is const
	//p2 = &b;  // Wrong! error C3892: 'p2': you cannot assign to a variable that is const

	// 3. const in a method or a function
	Entity3 e1;
	PrintEntity3X(e1);
	const Entity3 e2 = e1;
	PrintEntity3X(e2);
}
