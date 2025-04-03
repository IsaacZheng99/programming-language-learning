#include <iostream>


// 3. implementations of singleton
// 3.1 not delete copy constructor
class Singleton1
{
public:
	static Singleton1& GetInstance()
	{
		return s_Instance;
	}

	void Function() {}
private:
	Singleton1() {}

	static Singleton1 s_Instance;
};

Singleton1 Singleton1::s_Instance;

// 3.2 delete copy constructor
class Singleton2
{
public:

	Singleton2(const Singleton2&) = delete;  // delete the copy constructor
	Singleton2& operator=(const Singleton2&) = delete;  // we usually also delete the copy assignment operator

	static Singleton2& GetInstance()
	{
		return s_Instance;
	}

	void Function() {}
private:
	Singleton2() {}

	static Singleton2 s_Instance;
};

Singleton2 Singleton2::s_Instance;

// 3.3 insance inside the Get() function
class Singleton3
{
public:

	Singleton3(const Singleton3&) = delete;
	Singleton3& operator=(const Singleton3&) = delete;

	static Singleton3& GetInstance()
	{
		static Singleton3 s_Instance;  // "instance" will be instantiated when "GetInstance()" is called for the first time
		return s_Instance;
	}

	void Function() {}
private:
	Singleton3() {}
};


// 4.examples of random number generator
// 4.1 the normal way
class Random1
{
public:
	Random1(const Random1&) = delete;

	static Random1& GetInstance()
	{
		return s_Instance;
	}

	float Float()
	{
		return m_RandomGenerator;
	}
private:
	Random1() {}

	float m_RandomGenerator = 1.1f;  // pretend this is random

	static Random1 s_Instance;
};

Random1 Random1::s_Instance;

// 4.2 more simplified calling
class Random2
{
public:
	Random2(const Random2&) = delete;

	static Random2& GetInstance()
	{
		return s_Instance;
	}

	static float Float()
	{
		return GetInstance().IFloat();
	}
private:
	Random2() {}

	float IFloat()
	{
		return m_RandomGenerator;
	}

	float m_RandomGenerator = 1.1f;

	static Random2 s_Instance;
};

Random2 Random2::s_Instance;

// 5. namespace vs. singleton
namespace RandomClass {

	static float m_RandomGenerator = 1.1f;
	static float Float() { return m_RandomGenerator; }
}


int main()
{
	// 3. implementations of singleton
	// 3.1 not delete copy constructor
	Singleton1::GetInstance().Function();
	Singleton1 anotherInstance1 = Singleton1::GetInstance();  // will copy!

	// 3.2 delete copy constructor
	Singleton2& instance2 = Singleton2::GetInstance();
	auto& instance3 = Singleton2::GetInstance();
	//Singleton2 instance = Singleton2::GetInstance();  // Wrong! Compiling error. error C2280: 'Singleton2::Singleton2(const Singleton2 &)': attempting to reference a deleted function
	Singleton2::GetInstance().Function();

	// 3.3 instance inside the Get() function
	Singleton3& instance4 = Singleton3::GetInstance();
	Singleton3::GetInstance().Function();

	// 4.examples of random number generator
	// 4.1 the normal way
	float number1 = Random1::GetInstance().Float();
	std::cout << number1 << std::endl;
	float number2 = Random2::Float();
	std::cout << number2 << std::endl;

	// 5. namespace vs. singleton
	float number3 = RandomClass::Float();  // we can make it but we can't use the features of "class"
	std::cout << number3 << std::endl;
}
