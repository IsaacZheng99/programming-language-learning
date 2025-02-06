#include <iostream>
#include <vector>


// 2. how to use function pointer
void HelloWorld()
{
	std::cout << "Hello World!" << std::endl;
}

// 2.2 use void(*function)()
void Function(const std::string& name, int age)
{
	std::cout << "Name: " << name << "; Age: " << age << std::endl;
}

// 3. why we need function pointer
void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int))
{
	for (int value : values)
		func(value);
}


int main()
{
	// 2.1 use auto
	//auto function1 = HelloWorld();  // Wrong! error C3313: 'function1': variable cannot have the type 'void'
	auto function2 = HelloWorld;  // implict conversion
	function2();
	auto function3 = &HelloWorld;
	function3();

	// 2.2 use void(*function)()
	void (*function4)();
	function4 = HelloWorld;
	function4();
	void (*function5)() = HelloWorld;
	function5();

	void (*function6)(const std::string&, int) = Function;
	function6("xiaoli", 1);

	// 2.3 use typedef
	typedef void (*HelloWorldFunction)();
	HelloWorldFunction function7 = HelloWorld;
	function7();

	typedef void (*FunctionPtr)(const std::string&, int);
	FunctionPtr function8 = Function;
	function8("xiaoli", 1);

	// 2.4 use using
	using HelloWorldPtr = void (*)();
	HelloWorldPtr function9 = HelloWorld;
	function9();

	using FunctionPtr2 = void (*)(const std::string&, int);
	FunctionPtr2 function10 = Function;
	function10("xiaoli", 1);

	// 3. why we need function pointer
	std::vector<int> values = { 5, 4 ,3 ,2 ,1 };
	ForEach(values, PrintValue);

	ForEach(values, [](int value) { std::cout << "Value: " << value << std::endl; });
}
