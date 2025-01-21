#include <iostream>


class Entity
{
public:
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}
};

// 3. funcion scope
// 3.1 pointer to local variable
//int* CreateArray1()
//{
//	int array[50];
//	return array;  // Warning! warning C4172: returning address of local variable or temporary : array
//}

// 3.2 create on the heap
int* CreateArray2()
{
	int* array = new int[50];
	return array;
}

// 3.3 define the variable outside the function scope
void CreateArray3(int* array)
{
	// fill the array
}

// 4. how to leverage the property of stack-based object
class ScopedPtr
{
private:
	Entity* m_Ptr;
public:
	ScopedPtr(Entity* ptr)
		: m_Ptr(ptr) {
	}

	~ScopedPtr()
	{
		delete m_Ptr;
	}
};

int main()
{
	// 2. create class object on the stack or heap
	{
		Entity e1;
		Entity* e2 = new Entity();
		delete e2;
	}

	// 3. function scope
	// 3.1 pointer to local variable
	//int* a1 = CreateArray1();  // Warning!

	// 3.2 create on the heap
	int* a2 = CreateArray2();

	// 3.3 define the variable outside the function scope
	int array[50];
	CreateArray3(array);

	// 4. how to leverage the property of stack-based object
	{
		ScopedPtr e = new Entity();
		//Entity* e = new Entity();  // almost the same format and we don't need to call "delete" manually
	}
}
