#include <iostream>

// 1. one implicit conversion
// 1.1 create objects with implicit conversion
class Entity
{
private:
	std::string m_Name;
	int m_Age;
public:
	Entity(const std::string& name)
		: m_Name(name), m_Age(-1) {
	}

	Entity(int age)
		: m_Name("Unknown"), m_Age(age) {
	}
};

void Function(const Entity& e)
{

}

// 1.4 type conversion operator
class MyClass
{
private:
	int m_Value;
public:
	MyClass()
		: m_Value(1) {
	}

	operator int() const
	{
		return m_Value;
	}
};

// 2. explicit
class EntityWithExplicit
{
private:
	std::string m_Name;
	int m_Age;
public:
	EntityWithExplicit(const std::string name)
		: m_Name(name), m_Age(-1) {
	}

	explicit EntityWithExplicit(int age)
		: m_Name("Unknown"), m_Age(age) {
	}

	int GetAge() const
	{
		return m_Age;
	}
};


int main()
{
	// 1. one implicit conversion
	std::cout << "-----1. one implicit conversion-----" << std::endl;
	// 1.1 implicit construction
	std::cout << "-----1.1 implicit construction-----" << std::endl;
	Entity e1 = Entity("xiaoli");
	Entity e2 = (std::string)"xiaoli";
	//Entity e3 = "xiaoli";  // Wrong! error C2440: 'initializing': cannot convert from 'const char [7]' to 'Entity'
	Entity e4 = Entity(25);
	Entity e5 = 25;

	Function((std::string)"xiaoli");

	// 1.2 arithmetic conversion
	std::cout << "-----1.2 arithmetic conversion-----" << std::endl;
	// integrl promotion
	std::cout << "-----integrl promotion-----" << std::endl;
	char c1 = 10;
	int i1 = 20;
	int result1 = c1 + i1;
	std::cout << c1 + i1 << std::endl;
	std::cout << typeid(c1 + i1).name() << std::endl;
	std::cout << result1 << std::endl;
	std::cout << typeid(result1).name() << std::endl;
	// usual arithmetic conversion
	std::cout << "-----usual arithmetic conversion-----" << std::endl;
	std::cout << "-----float priority-----" << std::endl;
	int i2 = 12;
	float f1 = 1.1f;
	std::cout << i2 + f1 << std::endl;  // float priority
	std::cout << typeid(i2 + f1).name() << std::endl;
	std::cout << i2 / f1 << std::endl;
	std::cout << typeid(i2 / f1).name() << std::endl;
	std::cout << i2 / i1 << std::endl;
	std::cout << typeid(i2 / i1).name() << std::endl;
	std::cout << i1 / i2 << std::endl;
	std::cout << typeid(i1 / i2).name() << std::endl;
	int i3 = 120;
	std::cout << i3 / i2 << std::endl;
	std::cout << typeid(i3 / i2).name() << std::endl;
	double d1 = 2.2;
	std::cout << i2 + d1 << std::endl;
	std::cout << typeid(i2 + d1).name() << std::endl;
	std::cout << f1 + d1 << std::endl;
	std::cout << typeid(f1 + d1).name() << std::endl;
	
	std::cout << "-----larger-ranged number priority-----" << std::endl;
	int i4 = 1;
	long l1 = 10;
	std::cout << i4 + l1 << std::endl;  // larger-ranged number priority
	std::cout << typeid(i4 + l1).name() << std::endl;
	unsigned int ui1 = 100;
	std::cout << i4 + ui1 << std::endl;
	std::cout << typeid(i4 + ui1).name() << std::endl;

	std::cout << "-----bool conversion-----" << std::endl;
	bool b1 = true;
	bool b2 = false;
	int i5 = 99;
	std::cout << i5 + b1 << std::endl;  // bool conversion
	std::cout << typeid(i5 + b1).name() << std::endl;
	std::cout << i5 + b2 << std::endl;
	std::cout << typeid(i5 + b2).name() << std::endl;

	// floating-point promotion
	std::cout << "-----floating-point promotion-----" << std::endl;
	float f2 = 3.3f;
	double d2 = 4.4;
	std::cout << f2 + d2 << std::endl;
	std::cout << typeid(f2 + d2).name() << std::endl;

	// 1.3 assignment conversion
	std::cout << "-----1.3 assignment conversion-----" << std::endl;
	float f3 = 1.1f;
	double d3 = f3;
	char c2 = 1;
	int i6 = c2;
	char c3 = i6;

	// 1.4 type conversion operator
	std::cout << "-----1.4 type conversion operator-----" << std::endl;
	MyClass obj;
	int a = obj;
	std::cout << a << std::endl;

	// 2. explicit
	std::cout << "-----2. explicit-----" << std::endl;
	//EntityWithExplicit ee1 = 25;  // Wrong!
	EntityWithExplicit ee2 = EntityWithExplicit(25);
	std::cout << ee2.GetAge() << std::endl;
	EntityWithExplicit ee3(25);
	std::cout << ee2.GetAge() << std::endl;
	EntityWithExplicit ee4 = (EntityWithExplicit)25;
	std::cout << ee2.GetAge() << std::endl;
	EntityWithExplicit ee5 = EntityWithExplicit(25);
	std::cout << ee2.GetAge() << std::endl;
	EntityWithExplicit ee6 = (EntityWithExplicit)(25);
	std::cout << ee2.GetAge() << std::endl;
}
