#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>


// 2.1 simple use: "if(data)"
std::string ReadFileAsString(std::string& filePath)
{
	std::ifstream stream(filePath);
	if (stream)
	{
		std::stringstream buffer;
		buffer << stream.rdbuf();
		std::string result = buffer.str();
		stream.close();

		return result;
	}

	return std::string();
}

// 2.2 add a flag variable
std::string ReadFileAsString(std::string& filePath, bool& outSuccess)
{
	std::ifstream stream(filePath);
	if (stream)
	{
		std::stringstream buffer;
		buffer << stream.rdbuf();
		std::string result = buffer.str();
		stream.close();
		outSuccess = true;

		return result;
	}

	outSuccess = false;
	return std::string();
}

// 2.3 std::optional<>
std::optional<std::string> ReadFileAsStringByOptional(std::string& filePath)
{
	std::ifstream stream(filePath);
	if (stream)
	{
		std::stringstream buffer;
		buffer << stream.rdbuf();
		std::string result = buffer.str();
		stream.close();

		return result;
	}

	return std::string();
}

int main()
{
	// 2.1 simple use: "if(data)"
	std::string filePath1 = "data.txt";
	std::string data1 = ReadFileAsString(filePath1);
	if (data1 != "")
	{
		// do something
	}

	// 2.2 add a flag variable
	std::string filePath2 = "data.txt";
	bool fileOpenSuccessfully;
	std::string data2 = ReadFileAsString(filePath2, fileOpenSuccessfully);
	if (fileOpenSuccessfully)
	{
		// do something
	}

	// 2.3 std::optional<>
	std::string filePath3 = "data.txt";
	std::optional<std::string> data3 = ReadFileAsStringByOptional(filePath3);
	if (data3)
		//if (data3.has_value())
	{
		// access the "data", really like the "smart pointer"
		std::string& value = *data3;  // we can also use "data3->..." and "data3.value()" to operate and access the actual data

		std::cout << "File read successfully!\n";
	}
	else
	{
		std::cout << "File could not be opened!\n";
	}

	// 2.4 set default value for std::optional<>
	std::string filePath4 = "data.txt";
	std::optional<std::string> data4 = ReadFileAsStringByOptional(filePath4);
	std::string value4 = data4.value_or("------Not Present------");
	std::cout << value4 << std::endl;
	if (data4)
	{
		std::cout << "File read successfully!\n";
	}
	else
	{
		std::cout << "File could not be opened!\n";
	}
}
