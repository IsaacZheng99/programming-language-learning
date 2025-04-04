#include <iostream>


// 1.2 r-value
int GetValue1()
{
	return 10;
}

// 2. l-value reference
// 2.1 function returning l-value reference
int& GetValue2()
{
	int value = 10;
	return value;
}

// 2.2 function with l-value parameter
void SetValue1(int value)  // "int value" is "l-value"
{
}

// 2.3 function with l-value reference parameter
void SetValue2(int& value)
{
}

// 2.4 function with l-value reference parameter: std::string&
void PrintName1(std::string& name)
{
	std::cout << name << std::endl;
}

// 2.5 function with const l-value reference parameter
void PrintName2(const std::string& name)
{
	std::cout << name << std::endl;
}

// 3. r-value reference
// 3.1 function with r-value reference parameter
void PrintName3(std::string&& name)
{
	std::cout << name << std::endl;
}

// 3.2 override functions with r-value reference parameter and l-value reference parameter
void PrintName4(std::string&& name)
{
	std::cout << "[rvalue]" << name << std::endl;
}

void PrintName4(std::string& name)
{
	std::cout << "[lvalue]" << name << std::endl;
}

// 3.3 override functions with r-value reference parameter and const l-value reference parameter
void PrintName5(std::string&& name)
{
	std::cout << "[rvalue]" << name << std::endl;
}

void PrintName5(const std::string& name)
{
	std::cout << "[lvalue]" << name << std::endl;
}

// 3.4 function with const r-value reference parameter
void PrintName6(const std::string&& name)
{
	std::cout << name << std::endl;
}


int main()
{
	// 1. what is l-value and r-value
	// 1.1 l-value
	int i1 = 10;
	// we have a variable called "i1", which is of course an actual variable with a location in memory
	// we have simply a value "10", just a numerical literal, it has no storage, no location until it is assigned to an l-value, which is what "i" is

	int i2 = i1;
	// here we are setting an l-value equal to something that is also an l-value

	// 1.2 r-value
	int i3 = GetValue1();
	// "GetValue()" returns an r-value, which is a temporary value
	//GetValue1() = 5;  // Wrong! Compiling error. error C2106: '=': left operand must be l-value

	// 2. l-value reference
	// 2.1 function returning l-value reference
	GetValue2() = 1;

	// 2.2 function with l-value parameter
	int i4 = 10;
	SetValue1(i4);  // l-value used to create l-value
	SetValue1(10);  // r-value used to create l-value

	// 2.3 function with l-value reference parameter
	int i5 = 10;
	SetValue2(i5);
	//SetValue2(10);  // Wrong! Compiling error.

	// 2.4 function with l-value reference parameter: std::string&
	std::string firstName1 = "xiao";
	std::string lastName1 = "li";
	std::string fullName1 = firstName1 + lastName1;
	// l-values: firstName1, lastName1, fullName1
	// r-values: "xiao", "li", firstName1 + lastName1
	// a temporary string gets constructed from "firstName1" and "lastName1" and then it gets assigned into an l-value: "fullName1"
	PrintName1(fullName1);
	//PrintName1(firstName1 + lastName1);  // Wrong! Compiling error.

	// 2.5 function with const l-value reference parameter
	std::string firstName2 = "xiao";
	std::string lastName2 = "li";
	std::string fullName2 = firstName2 + lastName2;
	PrintName2(fullName2);
	PrintName2(firstName2 + lastName2);

	// 3. r-value reference
	// 3.1 function with r-value reference parameter
	std::string firstName3 = "xiao";
	std::string lastName3 = "li";
	std::string fullName3 = firstName3 + lastName3;
	//PrintName3(fullName3);  // Wrong! Compiling error.
	PrintName3(firstName3 + lastName3);

	// 3.2 override functions with r-value reference parameter and l-value reference parameter
	std::string firstName4 = "xiao";
	std::string lastName4 = "li";
	std::string fullName4 = firstName4 + lastName4;
	PrintName4(fullName4);
	PrintName4(firstName4 + lastName4);

	// 3.3 override functions with r-value reference parameter and const l-value reference parameter
	std::string firstName5 = "xiao";
	std::string lastName5 = "li";
	std::string fullName5 = firstName5 + lastName5;
	PrintName5(fullName5);
	PrintName5(firstName5 + lastName5);

	// 3.4 function with const r-value reference parameter
	std::string firstName6 = "xiao";
	std::string lastName6 = "li";
	std::string fullName6 = firstName6 + lastName6;
	//PrintName6(fullName6);  // Wrong! Compiling error.
	PrintName6(firstName6 + lastName6);
}
