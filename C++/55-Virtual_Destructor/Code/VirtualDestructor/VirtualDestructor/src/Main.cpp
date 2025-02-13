#include <iostream>


// 2. some examples
// 2.1 the normal case
class Base
{
public:
	Base() { std::cout << "Base Constructor\n"; }
	~Base() { std::cout << "Base Destructor\n"; }
};


class Derived : public Base
{
public:
	Derived() { std::cout << "Derived Constructor\n"; }
	~Derived() { std::cout << "Derived Destructor\n"; }
};


// 2.3 memory leak
class DerivedWithDynamicMemoryAllocation : public Base
{
private:
	int* m_Array;
public:
	DerivedWithDynamicMemoryAllocation()
	{
		m_Array = new int[5];
		std::cout << "Derived Constructor\n";
	}

	~DerivedWithDynamicMemoryAllocation()
	{
		delete[] m_Array;
		std::cout << "Derived Destructor\n";
	}
};


// 2.4 virtual destructor of Base
class BaseWithVirtualDestructor
{
public:
	BaseWithVirtualDestructor() { std::cout << "Base Constructor\n"; }
	virtual ~BaseWithVirtualDestructor() { std::cout << "Base Destructor\n"; }
};


class DerivedFromBaseWithVirtualDestructor : public BaseWithVirtualDestructor
{
private:
	int* m_Array;
public:
	DerivedFromBaseWithVirtualDestructor()
	{
		m_Array = new int[5];
		std::cout << "Derived Constructor\n";
	}

	~DerivedFromBaseWithVirtualDestructor()
	{
		delete[] m_Array;
		std::cout << "Derived Destructor\n";
	}
};

int main()
{
	// 2. some examples
	// 2.1 the normal case
	Base* base = new Base();
	delete base;
	std::cout << "----------\n";
	Derived* derived = new Derived();
	delete derived;
	std::cout << "----------\n";

	// 2.2 Base pointer to Derived object
	Base* poly1 = new Derived();
	delete poly1;
	std::cout << "----------\n";

	// 2.3 memory leak
	Base* poly2 = new DerivedWithDynamicMemoryAllocation();
	delete poly2;
	std::cout << "----------\n";

	// 2.4 virtual destructor of Base
	BaseWithVirtualDestructor* poly3 = new DerivedFromBaseWithVirtualDestructor();
	delete poly3;
	std::cout << "----------\n";
}
