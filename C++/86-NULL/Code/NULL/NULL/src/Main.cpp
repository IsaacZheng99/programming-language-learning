#include <iostream>


// 4. how does NULL work with objects
class Entity
{
public:
	Entity() = default;

	const std::string& GetName() const { return m_Name; }

	void PrintType()
	{
		std::cout << "Entity\n";
	}
private:
	Entity* m_Parent;
	std::string m_Name;
};

// 4.3 go back to C
struct EntityData
{
	Entity* m_Parent;
	std::string m_Name;
};

const std::string& Entity_GetName(const EntityData* self)
{
	// self == nullptr
	return self->m_Name;
}

void Entity_PrintName(EntityData* self)
{
	// self == nullptr
	std::cout << "Entity\n";
}


int main()
{
	// 2. what is the value of NULL
	// 2.1 the key word nullptr
	void* value1 = nullptr;
	std::cout << value1 << std::endl;

	// 2.2 the marco NULL
	void* value2 = NULL;
	std::cout << value2 << std::endl;
	int value3 = NULL;
	std::cout << value3 << std::endl;
	// the source code of NULL
	/*#ifndef NULL
		#ifdef __cplusplus
			#define NULL 0
		#else
			#define NULL ((void *)0)
		#endif
	#endif*/

	// 4. how does NULL work with objects
	// 4.1 GetName()
	Entity* entity1 = nullptr;
	//std::cout << entity1->GetName() << std::endl;  // Wrong! throw an exception: read access violation

	// 4.2 PrintType()
	Entity* entity2 = nullptr;
	entity2->PrintType();

	// 4.4 the marco offsetof
	uint64_t offset = offsetof(EntityData, m_Name);
	std::cout << offset << std::endl;
	// the source code of offsetof
	/*#if defined _MSC_VER && !defined _CRT_USE_BUILTIN_OFFSETOF
		#ifdef __cplusplus
			#define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
		#else
			#define offsetof(s,m) ((size_t)&(((s*)0)->m))
		#endif
	#else
		#define offsetof(s,m) __builtin_offsetof(s,m)
	#endif*/
	uint64_t customOffset = (uint64_t) & (((EntityData*)0)->m_Name);
	std::cout << customOffset << std::endl;
}
