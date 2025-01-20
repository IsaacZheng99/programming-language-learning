#include <iostream>


// 1. mutable works with const in a method
class Entity1
{
private:
	const std::string m_Name;
public:
	Entity1()
		: m_Name("Entity1") {
	}

	const std::string GetName()
	{
		return m_Name;
	}
};

class Entity2
{
private:
	const std::string m_Name;
public:
	Entity2()
		: m_Name("Entity2") {
	}

	const std::string GetName() const // add "const"
	{
		return m_Name;
	}
};

//class Entity3
//{
//private:
//	const std::string m_Name;
//	int m_DebugCount;  // We want to check how many times a method has been called.
//public:
//	Entity3()
//		: m_Name("Entity3"), m_DebugCount(0) {}
//
//	const std::string GetName() const
//	{
//		m_DebugCount++;  // Wrong! error C3490: 'm_DebugCount' cannot be modified because it is being accessed through a const object
//		return m_Name;
//	}
//};

class Entity4
{
private:
	const std::string m_Name;
	mutable int m_DebugCount;  // add "mutable"
public:
	Entity4()
		: m_Name("Entity4"), m_DebugCount(0) {
	}

	const std::string GetName() const
	{
		m_DebugCount++;
		return m_Name;
	}
};

class Entity5
{
private:
	const std::string m_Name;
	mutable int m_DebugCount;  // add "mutable"
public:
	const std::string GetName() const
	{
		m_DebugCount++;
		return m_Name;
	}
};


int main()
{
	// 1. mutable works with const in a method
	Entity1 e1;
	std::cout << e1.GetName() << std::endl;

	const Entity1 e2;
	//std::cout << e2.GetName() << std::endl;  // Wrong! error C2662: 'const std::string Entity1::GetName(void)': cannot convert 'this' pointer from 'const Entity1' to 'Entity1 &'

	const Entity2 e3;
	std::cout << e3.GetName() << std::endl;

	const Entity4 e4;
	std::cout << e4.GetName() << std::endl;

	//const Entity5 e5;  // Wrong!error C2737 : 'e5' : const object must be initialized
	//std::cout << e5.GetName() << std::endl;

	// 2. mutable works with lambda
	// without mutable
	//int x = 0;
	//auto f = [=]()
	//{
	//	x++;  // Wrong! error C3491: 'x': a by copy capture cannot be modified in a non-mutable lambda
	//	std::cout << x << std::endl;
	//};
	//f();
	//std::cout << x << std::endl;
	// with mutable
	int y = 0;
	auto f = [=]() mutable
		{
			y++;
			std::cout << y << std::endl;
		};
	f();
	std::cout << y << std::endl;
}
