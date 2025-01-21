#include <iostream>
#include <fstream>


// 2.2 copy the object
struct Vector2
{
	float x, y;

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

// 3. shallow copy with custom class String
// 3.1 create a custom class String
class String
{
private:
	char* m_Buffer;
	int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}

	String(const String& other)
		: m_Size(other.m_Size)
	{
		std::cout << "Copied String!" << std::endl;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}


	~String()
	{
		delete[] m_Buffer;
	}

	char& operator[](int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void PrintString(const String& string)
{
	std::cout << string << std::endl;
}

int main()
{
	// 2. examples of copy
	// 2.1 copy the primitive-typed object
	int a = 1;
	int b = a;
	b = 2;
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	// 2.2 copy the non-primitive-typed object
	Vector2 v1 = { 1, 2 };
	v1.Print();
	Vector2 v2 = v1;
	v2.Print();
	v2.x = 2;
	v2.Print();


	// 2.3 copy the pointer
	Vector2* p1 = new Vector2();
	Vector2* p2 = p1;
	p1->x = 1;
	p1->Print();
	p2->Print();

	p2++;

	// 3. shallow copy with custom class String
	// 4. copy constructor
	String string = "xiaoli";
	String second = string;
	string[0] = 'a';
	// 4.4 how many times the copy happens
	PrintString(string);
	PrintString(second);
}
