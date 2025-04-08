#include <iostream>


// 2. an example
// 2.1 explicitly cast: (String&&)
class String
{
public:
	String() = default;

	String(const char* string)
	{
		printf("Created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}

	String(const String& other)
	{
		printf("Copied\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	String(String&& other) noexcept
	{
		printf("Moved\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	// 2.3 move assignment operator
	String& operator=(String&& other) noexcept
	{
		printf("Move Assignment\n");
		delete[] m_Data;  // Important!

		if (this != &other)
		{
			m_Size = other.m_Size;
			m_Data = other.m_Data;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}

		return *this;
	}

	~String()
	{
		printf("Destroyed\n");
		delete[] m_Data;
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


int main()
{
	// 2. an exmaple
	// 2.1 explicitly cast: (String&&)
	String string1 = "Hello";
	String dest1 = (String&&)string1;
	//String dest1((String&&)string1);

	// 2.2 std::move()
	String string2 = "Hello";
	String dest2 = std::move(string2);
	//String dest2(std::move(string2));

	// 2.3 move assignment operator
	String string3 = "123";
	String string4 = "456";
	std::cout << "string3: ";
	string3.Print();
	std::cout << "string4: ";
	string4.Print();

	string4 = std::move(string3);
	std::cout << "string3: ";
	string3.Print();
	std::cout << "string4: ";
	string4.Print();
}
