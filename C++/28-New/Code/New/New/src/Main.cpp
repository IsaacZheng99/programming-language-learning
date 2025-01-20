#include <iostream>


// 1. what does new do
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
	// 1. what does new do
	Entity* e1 = new Entity();
	//Entity* e2 = (Entity*)malloc(sizeof(Entity));
	delete e1;

	// 2. what are new and delete
	// 3. what are new[] and delete[]
	int* a = new int;
	delete a;

	int* array = new int[5];
	delete[] array;

	Entity* entities = new Entity[5];
	delete[] entities;

	// 4. placement new
	int* bigArray = new int[1000];
	Entity* e = new(bigArray) Entity();  // note the size
	delete[] bigArray;
	std::cout << sizeof(Entity) << std::endl;
}
