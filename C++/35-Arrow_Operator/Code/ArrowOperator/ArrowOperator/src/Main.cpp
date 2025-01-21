#include <iostream>
#include <memory>

// 1. operator-> used with pointer
class Entity
{
public:
	void Print() const
	{
		std::cout << "Hello!" << std::endl;
	}
};

// 2. overload operator->
// 2.1 leverage the convenience of "scoped pointer" and "operator->" at the same time
class ScopedPtr
{
private:
	Entity* m_Obj;
public:
	ScopedPtr(Entity* entity)
		: m_Obj(entity) {
	}

	~ScopedPtr()
	{
		delete m_Obj;
	}

	Entity* GetObject()
	{
		return m_Obj;
	}

	Entity* operator->()
	{
		return m_Obj;
	}

	// 2.2 const version of operator->
	const Entity* operator->() const
	{
		std::cout << "const version" << std::endl;
		return m_Obj;
	}
};

// 3. use operator-> to get offset
struct Vector3
{
	float x, y, z;
};


int main()
{
	// 1. operator-> used with pointer
	Entity e;
	e.Print();

	Entity* ptr = &e;
	(*ptr).Print();

	Entity& entity = *ptr;
	entity.Print();

	ptr->Print();

	// 2. overload operator->
	// 2.1 leverage the convenience of "scoped pointer" and "operator->" at the same time
	ScopedPtr scopedPtr = new Entity();
	scopedPtr.GetObject()->Print();
	scopedPtr->Print();  // cleaner

	// 2.2 const version of operator->
	const ScopedPtr constScopedPtr = new Entity();
	constScopedPtr->Print();

	// 3. use operator-> to get offset
	int offsetX = (int)(&((Vector3*)nullptr)->x);  // Warning!
	std::cout << &((Vector3*)nullptr)->x << std::endl;
	std::cout << typeid(&((Vector3*)nullptr)->x).name() << std::endl;  // &((Vector3*)nullptr)->x is "float*"
	int offsetY = (int)(&((Vector3*)nullptr)->y);  // Warning!
	int offsetZ = (int)(&((Vector3*)nullptr)->z);  // Warning!
	std::cout << offsetX << std::endl;
	std::cout << offsetY << std::endl;
	std::cout << offsetZ << std::endl;
}
