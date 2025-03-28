#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <future>


// 2. an example
// 2.1 the normal way
std::string LoadTxtFile(const std::string& txtPath)
{
	std::ifstream stream(txtPath);
	std::string content = "";
	std::string line;
	while (std::getline(stream, line))
		content += line + " ";
	return content;
}

std::vector<std::string> LoadData(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::vector<std::string> txtPaths;
	std::vector<std::string> allContents;

	while (std::getline(stream, line))
		txtPaths.push_back(line);

	for (const auto& file : txtPaths)
		allContents.push_back(LoadTxtFile(file));

	return allContents;
}

// 2.2 multi-threading: std::async
static std::mutex s_TxtMutex;

void LoadContent(std::vector<std::string>& allContents, std::string txtPath)
{
	if (txtPath == "src/txt/1.txt")
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	auto content = LoadTxtFile(txtPath);
	std::lock_guard<std::mutex> lock(s_TxtMutex);  // work similarly with "Timer" (RAII), the destructor of the lock_guard will unlock that lock
	allContents.push_back(content);
}

std::vector<std::string> LoadData2(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::vector<std::string> txtPaths;
	std::vector<std::string> allContents;
	std::vector<std::future<void>> futures;

	while (std::getline(stream, line))
		txtPaths.push_back(line);

#define ASYNC 1
#if ASYNC
	for (const auto& file : txtPaths)
	{
		futures.push_back(std::async(std::launch::async, LoadContent, std::ref(allContents), file));
	}
#else
	for (const auto& file : txtPaths)
		allContents.push_back(LoadTxtFile(file));
#endif

	return allContents;
}


int main()
{
	// 2. an example
	// 2.1 the normal way
	std::string path1 = "src/txt/paths.txt";
	std::vector<std::string> allContents1 = LoadData(path1);
	for (std::string content : allContents1)
		std::cout << content << std::endl;

	// 2.2 multi-threading: std::async
	std::string path2 = "src/txt/paths.txt";
	std::vector<std::string> allContents2 = LoadData2(path2);
	for (std::string content : allContents2)
		std::cout << content << std::endl;
}
