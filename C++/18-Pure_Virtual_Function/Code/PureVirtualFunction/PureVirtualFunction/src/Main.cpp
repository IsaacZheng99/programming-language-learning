#include <iostream>


class Printable  // we can call this class as "interface"
{
public:
	virtual std::string GetClassName() = 0;  // pure virtual function
};

class Entity : public Printable
{
public:
	virtual std::string GetName()
	{
		return "Entity";
	}

	std::string GetClassName() override
	{
		return "Entity";
	}
};

class Player : public Entity
{
private:
	const std::string m_Name;
public:
	Player(std::string name)
		: m_Name(name) {
	}

	std::string GetName() override
	{
		return m_Name;
	}

	std::string GetClassName() override
	{
		return "Player";
	}
};

void PrintClassName(Printable* obj)  // just set the type of the parameter as "Printable", i.e., the "interface" type
{
	std::cout << obj->GetClassName() << std::endl;
}


int main()
{
	Entity* e = new Entity();
	PrintClassName(e);
	Player* p = new Player("p");
	PrintClassName(p);
}
