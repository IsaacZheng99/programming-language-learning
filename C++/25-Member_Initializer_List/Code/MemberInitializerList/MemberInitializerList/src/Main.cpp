#include <iostream>


// 1. initialization order
class Entity1
{
public:
	int x, y;

	Entity1()
		: y(1), x(y) {
	}
};

class Entity2
{
public:
	int x, y;

	Entity2()
		: x(1), y(x) {
	}
};

// 2. why need member initializer list
class Example
{
public:
	Example()
	{
		std::cout << "Created Example" << std::endl;
	}

	Example(int x)
	{
		std::cout << "Created Example with " << x << std::endl;
	}
};

class EntityWithExample1
{
private:
	std::string m_Name;
	Example m_Example;
public:
	EntityWithExample1()
	{
	}
};

class EntityWithExample2
{
private:
	std::string m_Name;
	Example m_Example;
public:
	EntityWithExample2()
	{
		m_Example = Example(1);
	}
};

class EntityWithExample3
{
private:
	std::string m_Name;
	Example m_Example;
public:
	EntityWithExample3()
		: m_Example(Example(1))
	{
	}
};

class EntityWithExample4
{
private:
	std::string m_Name;
	Example m_Example;
public:
	EntityWithExample4()
		: m_Example(1)
	{
	}
};

int main()
{
	// 1. initialization order
	Entity1 e1;
	std::cout << e1.x << ", " << e1.y << std::endl;
	Entity2 e2;
	std::cout << e2.x << ", " << e2.y << std::endl;

	// 2. why need member initializer list
	EntityWithExample1 ee1;
	EntityWithExample2 ee2;
	EntityWithExample3 ee3;
	EntityWithExample4 ee4;
}
