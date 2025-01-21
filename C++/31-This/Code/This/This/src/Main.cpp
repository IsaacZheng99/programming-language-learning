#include <iostream>


// 3. usage of this
// 3.1 assign the member variable
class Entity1
{
public:
	int x, y;

	Entity1(int x, int y)
	{
		x = x;
	}
};

class Entity2
{
public:
	int x, y;

	Entity2(int x, int y)
	{
		this->x = x;
	}
};

// 3.2 this is a const pointer
class Entity3
{
public:
	int x, y;

	Entity3(int x, int y)
	{
		Entity3* e1 = this;
		Entity3* const e2 = this;  // "this" is "Entity* const"
		//this = nullptr;  // Wrong! error C2106: '=': left operand must be l-value
	}
};

// 3.3 reference this
class Entity4
{
public:
	int x, y;

	Entity4(int x, int y)
	{
		//Entity4*& e1 = this;  // Wrong! error C2440: 'initializing': cannot convert from 'Entity4 *' to 'Entity4 *&'
		Entity4* const& e2 = this;
		const Entity4* const& e3 = this;
	}
};

// 3.4 access member by this
class Entity5
{
public:
	int x, y;

	Entity5(int x, int y)
	{
		this->x = x;
		//(*this).x = x;

		Entity5* e = this;
		e->x = x;
	}
};

// 3.5 add const in method
class Entity6
{
public:
	int x, y;

	Entity6(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int GetX() const
	{
		//Entity6* e1 = this;  // Wrong! error C2440: 'initializing': cannot convert from 'const Entity6 *' to 'Entity6 *'
		const Entity6* e2 = this;
		return e2->x;
	}
};

// 3.6 this and *this
class Entity7;
void PrintEntity71(Entity7* e);
void PrintEntity72(const Entity7& e);

class Entity7
{
public:
	int x, y;

	Entity7(int x, int y)
	{
		this->x = x;
		this->y = y;

		PrintEntity71(this);
		PrintEntity72(*this);
	}
};

void PrintEntity71(Entity7* e)
{
	std::cout << "PrintEntity71" << std::endl;
}

void PrintEntity72(const Entity7& e)
{
	std::cout << "PrintEntity72" << std::endl;
}

// 3.7 delete this
class Entity8
{
public:
	int x, y;

	Entity8(int x, int y)
	{
		this->x = x;
		this->y = y;

		delete this;
	}
};


int main()
{
	// 3.1 assign the member variable
	Entity1 e1(1, 2);
	std::cout << e1.x << std::endl;
	Entity2 e2(1, 2);
	std::cout << e2.x << std::endl;

	// 3.4 access member by this
	Entity5 e5(1, 2);
	std::cout << e5.x << std::endl;

	// 3.5 add const in method
	Entity6 e6(1, 2);
	std::cout << e6.GetX() << std::endl;

	// 3.6 this and *this
	Entity7 e7(1, 2);

	// 3.7 delete this
	//Entity8 e8(1, 2);  // Wrong! Runtime error.
}
