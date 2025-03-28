## 66. Improve Performance by Multi-threading

**Knowledge Points**: `what to focus on`, `std::async`, `std::lock_guard`, `std::mutex`,`std::ref`

### 1. what to focus on

1. one of the hardest parts of making something run in parallel is trying to figure out **dependency** and think through **what** you can actually put into different threads
2. game engine is a good example
3. `C#` has a built-in library providing `parallel for loop`

### 2. an example

now we want to read some `.txt` files

#### 1. the normal way

```c++
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


int main()
{
    std::string path = "src/txt/paths.txt";
    std::vector<std::string> allContents = LoadData(path);
    for (std::string content : allContents)
        std::cout << content << std::endl;
    
    std::cin.get()
}
// outputs:
// This is the 1st file. Hello!
// This is the 2nd file. Hello!!
// This is the 3rd file. Hello!!!
// This is the 4th file. Hello!!!!
// This is the 5th file. Hello!!!!!
```

#### 2. multi-threading: std::async

```c++
static std::mutex s_TxtMutex;

std::string LoadTxtFile(const std::string& txtPath)
{
    std::ifstream stream(txtPath);
    std::string contetn = "";
    std::string line;
    while (std::getline(stream, line))
        content += line + " ";
    return content;
}

void LoadContent(std::vector<std::string>& allContents, std::string txtPath)
{
    if (txtPath == "src/txt/1.txt")
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // add latency manually
    auto content = LoadTxtFile(txtPath);
    std::lock_guard<std::mutex> lock(s_TxtMutex);  // work similarly with "Timer" (RAII), the destructor of the lock_guard will unlock that lock
    allContents.push_back(content);
}

std::vector<std::string> LoadData(const std::string& filePath)
{
    std::ifstream stream(filePath);
    std::string line;
    std::vector<std::string> txtPaths;
    std::vector<std::string> allContents;
    
    while (std::getline(stream, line))
        txtPaths.push_back(line);
    
#define ASYNC 1
#if ASYNC
    for (const auto& file : txtPaths)
    {
        allContents.push_back(std::async(std::launch::async, LoadContent, std::ref(allContents), file));
    }
#else
    for (const auto& file : txtPaths)
    	allContents.push_back(LoadTxtFile(file));
#endif
    return allContents
}

int main()
{
    std::string path = "src/txt/paths.txt";
    std::vector<std::string> allContents = LoadData(path);
    for (std::string content : allContents)
        std::cout << content << std::endl;
}
// outputs:
// This is the 2nd file. Hello!!
// This is the 3rd file. Hello!!!
// This is the 4th file. Hello!!!!
// This is the 5th file. Hello!!!!!
// This is the 1st file. Hello!
```

