#include <iostream>


// 2. hide
class Entity1
{
public:
	std::string GetName()
	{
		return "Entity1";
	}
};

class Player1 : public Entity1
{
private:
	const std::string m_Name;
public:
	Player1(const std::string name)
		: m_Name(name) {
	}

	std::string GetName()
	{
		return m_Name;
	}
};

void PrintName(Entity1* entity1)
{
	std::cout << entity1->GetName() << std::endl;
}

// 3. override
class Entity2
{
public:
	virtual std::string GetName()  // virtual
	{
		return "Entity2";
	}
};

class Player2 : public Entity2
{
private:
	const std::string m_Name;
public:
	Player2(const std::string name)
		: m_Name(name) {
	}

	// "std::string GetName()" is also fine, but the key word "override" can help check the code
	std::string GetName() override
	{
		return m_Name;
	}
};

void PrintName(Entity2* entity2)
{
	std::cout << entity2->GetName() << std::endl;
}


int main()
{
	// 2. hide
	Entity1* e1 = new Entity1();
	std::cout << e1->GetName() << std::endl;
	PrintName(e1);

	Player1* p1 = new Player1("p1");
	std::cout << p1->GetName() << std::endl;
	PrintName(p1);

	Entity1* ep1 = p1;
	std::cout << ep1->GetName() << std::endl;
	PrintName(ep1);

	std::cout << "----------" << std::endl;

	// 3. override
	Entity2* e2 = new Entity2();
	std::cout << e2->GetName() << std::endl;
	PrintName(e2);

	Player2* p2 = new Player2("p2");
	std::cout << p2->GetName() << std::endl;
	PrintName(p2);

	Entity2* ep2 = p2;
	std::cout << p2->GetName() << std::endl;
	PrintName(ep2);
}
