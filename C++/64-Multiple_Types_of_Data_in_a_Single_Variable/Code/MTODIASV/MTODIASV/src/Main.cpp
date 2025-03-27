#include <iostream>
#include <variant>
#include <optional>
#include <fstream>
#include <sstream>


// 2.4 std::variant<> vs. std::optional<>
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

enum class ErrorCode
{
	None = 0, NotFound, NotAccess
};

std::variant<std::string, ErrorCode> ReadFileStringByVariant(std::string& filePath)
{
	std::variant<std::string, ErrorCode> result;

	std::ifstream stream(filePath);
	if (stream)
	{
		std::stringstream buffer;
		buffer << stream.rdbuf();
		std::string data = buffer.str();
		stream.close();
		result = data;

		return result;
	}

	result = ErrorCode::None;

	return result;
}


int main()
{
	// 2. some examples
	// 2.1 std::variant<>
	std::variant<std::string, int> data1;
	data1 = "xiaoli";
	std::cout << std::get<std::string>(data1) << std::endl;
	data1 = 1;
	//std::cout << std::get<std::string>(data1);  // Wrong! runnning error
	std::cout << std::get<int>(data1) << std::endl;

	// 2.2 std::variant<>::index()
	std::variant<std::string, int> data2;
	data2 = 1;
	std::cout << std::get<int>(data2) << std::endl;
	std::cout << data2.index() << std::endl;

	// 2.3 std::get_if<>()
	std::variant<std::string, int> data3;
	data3 = 1;
	if (auto ptr = std::get_if<std::string>(&data3))
	{
		std::string& value = *ptr;
		std::cout << value << std::endl;
	}
	else if (auto ptr = std::get_if<int>(&data3))
	{
		int* value = ptr;
		std::cout << *value << std::endl;
	}

	// 2.4 std::variant<> vs. std::optional<>

	// 3. difference between std::variant<> and union
	union Data
	{
		std::string s;
		int v;
	};
	std::variant<std::string, int> data4;
	std::cout << sizeof(Data) << std::endl;
	std::cout << sizeof(data4) << std::endl;
	std::cout << sizeof(int) << std::endl;
	std::cout << sizeof(std::string) << std::endl;
}
