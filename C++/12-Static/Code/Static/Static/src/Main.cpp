#include <iostream>

// 1. static outside of a class or struct
static void StaticFunction1()
{

}

static void StaticFunction2();

extern int s_Variable;

// 2. static inside a class or struct
struct Entity
{
	static int x, y;
};

int Entity::x;
int Entity::y;

// 3. static in a local scope
void Function1()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

void Function2()
{
	static int i;
	i++;
	std::cout << i << std::endl;
}

void Function3()
{
	static int i = 0;
	i = 0;
	i++;
	std::cout << i << std::endl;
}

int i = 0;

void Function()
{
	i++;
	std::cout << i << std::endl;
}

// Note that the `Singleton` code is just a simple example to illustrate "static" but not a serious implementation
class Singleton1
{
private:
	static Singleton1* s_Instance;
public:
	static Singleton1& Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new Singleton1();
		return *s_Instance;
	}

	void Hello() {}
};

Singleton1* Singleton1::s_Instance;

class Singleton2
{
private:
	static Singleton2 s_Instance;
public:
	static Singleton2& Get()
	{
		return s_Instance;
	}

	void Hello() {}
};

Singleton2 Singleton2::s_Instance;

class Singleton3
{
public:
	static Singleton3& Get()
	{
		static Singleton3 instance;
		return instance;
	}

	void Hello() {}
};


int main()
{
	// 1. static outside of a class or struct
	//StaticFunction2();  // Wrong! Compiling error.

	std::cout << s_Variable << std::endl;

	// 2. static inside a class or struct
	Entity e;
	std::cout << e.x << std::endl;
	e.x = 1;
	std::cout << e.x << std::endl;

	Entity::x = 2;
	std::cout << Entity::x << std::endl;

	// 3. static in a local scope
	Function1();
	Function1();
	Function1();
	Function2();
	Function2();
	Function2();
	Function3();
	Function3();
	Function3();
	//std::cout << i << std::endl;  // Wrong! Compiling error.

	Function();
	i = 10;
	Function();
	Function();

	Singleton1::Get().Hello();
	Singleton2::Get().Hello();
	Singleton3::Get().Hello();
}
