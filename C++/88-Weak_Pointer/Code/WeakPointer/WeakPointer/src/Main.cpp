#include <iostream>


// 1. how does std::weak_ptr work
// 1.1 std::shared_ptr
struct Object1
{
};

struct Manager1
{
	std::shared_ptr<Object1> Obj;
};

// 1.3 raw pointer
struct Manager2
{
	Object1* Obj;
};

struct Object2
{
	~Object2() { std::cout << "Deleted Object\n"; }

	void Func() { std::cout << 123; }
};

struct Manager3
{
	Object2* Obj;
};

// 1.4 std::weak_ptr
struct Manager4
{
	std::weak_ptr<Object2> Obj;

	void Func1()
	{
		if (std::shared_ptr<Object2> obj = Obj.lock())
		{

		}
	}

	void Func2()
	{
		if (Obj.expired())
		{

		}
	}

	void Func3()
	{
		std::cout << Obj.use_count() << std::endl;

		if (Obj.use_count())
		{

		}
	}
};

// 2. cyclical dependency
// 2.1 std::shared_ptr
struct B1;

struct A1
{
	std::shared_ptr<B1> ptrB;
	~A1() { std::cout << "A1 destroyed\n"; }
};

struct B1
{
	std::shared_ptr<A1> ptrA;
	~B1() { std::cout << "B1 destroyed\n"; }
};

// 2.1 std::weak_ptr
struct B2;

struct A2
{
	std::shared_ptr<B2> ptrB;
	~A2() { std::cout << "A2 destroyed\n"; }
};

struct B2
{
	std::weak_ptr<A2> ptrA;  // weak pointer
	~B2() { std::cout << "B2 destroyed\n"; }
};


int main()
{
	// 1. how does std::weak_ptr work
	// 1.1 std::shared_ptr
	std::shared_ptr<Object1> obj1 = std::make_shared<Object1>();
	Object1* obj2 = new Object1();
	delete obj2;

	Manager1 manager1;
	manager1.Obj = obj1;

	// 1.3 raw pointer
	Manager2 manager2;
	manager2.Obj = obj1.get();

	Manager3 manager3;
	{
		std::shared_ptr<Object2> obj = std::make_shared<Object2>();
		manager3.Obj = obj.get();
	}
	std::cout << manager3.Obj << std::endl;

	// 1.4 std::weak_ptr
	Manager4 manager4;
	{
		std::shared_ptr<Object2> obj = std::make_shared<Object2>();
		manager4.Obj = obj;
		manager4.Func3();
	}
	manager4.Func3();

	// 2. cyclical dependency
	// 2.1 std::shared_ptr
	std::shared_ptr<A1> a1 = std::make_shared<A1>();
	std::shared_ptr<B1> b1 = std::make_shared<B1>();
	a1->ptrB = b1;
	b1->ptrA = a1;

	// 2.1 std::weak_ptr
	std::shared_ptr<A2> a2 = std::make_shared<A2>();
	std::shared_ptr<B2> b2 = std::make_shared<B2>();
	a2->ptrB = b2;
	b2->ptrA = a2;
}
