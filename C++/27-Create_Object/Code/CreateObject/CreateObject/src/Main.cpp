#include <iostream>


// 1. how much memory an object costs
class Example1
{

};

class Example2
{
private:
	int x;
};

// 2. when memory is freed
using String = std::string;

class Entity
{
private:
	String m_Name;
public:
	Entity()
		: m_Name("Unknown") {
	}

	Entity(const String& name)
		: m_Name(name) {
	}

	const String& GetName() const
	{
		return m_Name;
	}
};


int main()
{
	// 1. how much memory an object costs
	Example1 example1;
	std::cout << sizeof(example1) << std::endl;
	std::cout << sizeof(Example1) << std::endl;
	Example2 example2;
	std::cout << sizeof(example2) << std::endl;
	std::cout << sizeof(Example2) << std::endl;

	// 2. when memory is freed
	// 2.1 stack-based object
	Entity entity1;
	std::cout << entity1.GetName() << std::endl;
	Entity entity2 = Entity();
	std::cout << entity2.GetName() << std::endl;
	Entity entity3("xiaoli");
	std::cout << entity3.GetName() << std::endl;
	Entity entity4 = Entity("xiaoli");
	std::cout << entity4.GetName() << std::endl;

	Entity* e1;
	{
		Entity entity5("xiaoli");
		e1 = &entity5;
		std::cout << e1->GetName() << std::endl;
	}
	std::cout << e1->GetName() << std::endl;  // We will see "m_Name=""".

	// 2.2 heap-based object
	Entity* e2;
	{
		Entity* entity6 = new Entity("xiaoli");
		e2 = entity6;
	}
	std::cout << e2->GetName() << std::endl;
}
