#include <iostream>


// 2. C++ style type casting
// 2.1 static_cast
class Base
{
public:
	Base() {}
	virtual ~Base() {}
};

class Derived : public Base
{
public:
	Derived() {}
	~Derived() {}
};

class AnotherClass : public Base
{
public:
	AnotherClass() {}
	~AnotherClass() {}
};

int main()
{
	// 1. C style type casting
	// 1.1 implicit and explicit conversion
	double d1 = 5.5;
	int i1 = d1;
	int i2 = (int)d1;
	std::cout << i1 << std::endl;
	std::cout << i2 << std::endl;

	// 1.2 implicit and explicit conversion at the same time
	double d2 = (int)d1 + 5.3;
	std::cout << d2 << std::endl;
	double d3 = (int)(d1 + 5.3);
	std::cout << d3 << std::endl;

	// 1.3 C++ style type casting: static_cast
	double d4 = static_cast<int>(d1) + 5.3;
	std::cout << d4 << std::endl;

	// 2. C++ style type casting
	// 2.1 static_cast
	Base* base1 = new Derived();
	Derived* derived1 = static_cast<Derived*>(base1);
	AnotherClass* anotherClass1 = static_cast<AnotherClass*>(base1);  // Not safe!

	//Derived* derived2 = new Derived();
	//AnotherClass* anotherClass2 = static_cast<AnotherClass*>(derived2);  // Wrong! error C2440: 'static_cast': cannot convert from 'Derived *' to 'AnotherClass *'

	// 2.2 dynamic_cast
	Derived* derived3 = new Derived();
	Base* base2 = derived3;
	Derived* de = dynamic_cast<Derived*>(base2);
	AnotherClass* ac = dynamic_cast<AnotherClass*>(base2);

	if (de)
	{
		std::cout << "Derived!" << std::endl;
	}

	if (!ac)
	{
		std::cout << "Not AnotherClass!" << std::endl;
	}

	// 2.3 reinterpret_cast
	double value1 = 1.1;
	AnotherClass* value2 = reinterpret_cast<AnotherClass*>(&value1);

	// 2.4 const_cast
	int i3 = 1;
	int* ptr1 = &i3;
	const int* ptr2 = const_cast<const int*>(ptr1);

	const int i4 = 1;
	const int* ptr3 = &i4;
	int* ptr4 = const_cast<int*>(ptr3);
	*ptr4 = 2;
	std::cout << i4 << std::endl;
	std::cout << *ptr3 << std::endl;
	std::cout << *ptr4 << std::endl;
	std::cout << ptr3 << std::endl;
	std::cout << ptr4 << std::endl;
}
