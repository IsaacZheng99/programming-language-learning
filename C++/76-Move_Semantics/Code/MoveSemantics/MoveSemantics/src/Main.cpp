#include <iostream>


// 2. an example
// 2.1 copy
class String1
{
public:
	String1() = default;

	String1(const char* string)
	{
		printf("Created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];  // note that there is no null termination character
		memcpy(m_Data, string, m_Size);
	}

	String1(const String1& other)
	{
		printf("Copied\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];  // allocate memory on the heap
		memcpy(m_Data, other.m_Data, m_Size);
	}

	~String1()
	{
		printf("Destroyed\n");
		delete m_Data;
	}

	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);

		printf("\n");
	}
private:
	char* m_Data;
	uint32_t m_Size;
};

class Entity1
{
public:
	Entity1(const String1& name)
		: m_Name(name)  // copy: String m_Name = name;
	{
	}

	void PrintName()
	{
		m_Name.Print();
	}
private:
	String1 m_Name;
};


// 2.2 move
class String2
{
public:
	String2() = default;

	String2(const char* string)
	{
		printf("Created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}

	String2(const String2& other)
	{
		printf("Copied\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	String2(String2&& other) noexcept
	{
		printf("Moved\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	~String2()
	{
		printf("Destroyed\n");
		delete m_Data;
	}

	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);

		printf("\n");
	}
private:
	char* m_Data;
	uint32_t m_Size;
};

class Entity2
{
public:
	Entity2(const String2& name)
		: m_Name(name)
	{
	}

	Entity2(String2&& name)
		//: m_Name((String2&&)name)
		: m_Name(std::move(name))
	{
	}

	void PrintName()
	{
		m_Name.Print();
	}
private:
	String2 m_Name;
};

int main()
{
	// 2. an example
	// 2.1 copy
	Entity1 entity1("xiaoli");
	entity1.PrintName();

	// 2.2 move
	Entity2 entity2("xiaoli");
	entity2.PrintName();
}
