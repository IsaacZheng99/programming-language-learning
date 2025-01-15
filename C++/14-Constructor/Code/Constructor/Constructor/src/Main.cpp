#include <iostream>


// 2. instantiate a class to get an object
class Entity
{
public:
	float x, y;

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	void Hello() {}
};

// 3. how about calling a Init() function
class EntityWithInit
{
public:
	float x, y;

	void Init()
	{
		x = 0.0f;
		y = 0.0f;
	}
};

// 4. constructor
class Entity2
{
public:
	float x, y;

	Entity2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Entity2(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
};

// if you don't want people to create instances
class Log1
{
private:
	Log1() {}
public:
	static void Write() {}
};

class Log2
{
public:
	Log2() = delete;

	static void Write() {}
};

int main()
{
	// 2. instantiate a class to get an object
	Entity e1;
	e1.Print();

	//Entity e2;
	//std::cout << e2.x << ", " << e2.y << std::endl;  // Wrong! Compiling error.

	Entity e3;
	e3.Hello();
	std::cout << e3.x << ", " << e3.y << std::endl;

	// 3. how about calling a Init() function
	EntityWithInit e4;
	e4.Init();
	std::cout << e4.x << ", " << e4.y << std::endl;

	// 4. constructor
	Entity2 e(10.0f, 5.0f);
	std::cout << e.x << ", " << e.y << std::endl;

	Log1::Write();
	Log2::Write();
}
