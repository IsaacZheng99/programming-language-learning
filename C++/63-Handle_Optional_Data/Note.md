## 63. Handle Optional Data

**Knowledge Points**: `std::optional<>`, `how to access the actual data via std::optional<>`, `value_or()`

### 1. what is optional data

what happens when we have data that may or may not be there?

e.g., if the we want to read from a file but we can't because the file doesn't exist, we can't simply return a `null string` because maybe it does contain nothing

### 2. some examples

#### 1. simple use "if(data)"

```c++
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


int main()
{
    std::string data = ReadFileAsString("data.txt");
    if (data != "")  // Not correct! We also want to know whether the file is read successfully.
    {
        // do something
    }
}
```

#### 2. add a flag variable

```c++
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

int main()
{
    bool fileOpenSuccessfullly;
    std::string data = ReadFileAsString("data.txt", fileOpenSuccessfullly);
    if (fileOpenSuccessfullly)
    {
        // do something
    }
}
```

#### 3. std::optional<>

```c++
std::optional<std::string> ReadFileAsString(std::string& filePath)  // new class in "C++17"
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
    std::optional<std::string> data = ReadFileAsString("data.txt");
    if (data)
    // if (data.has_value())
    {
        // access "data", really like the "smart pointer"
        std::string& value = *data;  // we can also use "data3->..." and "data3.value()" to operate and access the actual data
        
        std::cout << "File read successfully!\n";
    }
    else
    {
        std::cout << "File could not be opened!\n";
    }
}
```

#### 4. set default value

```c++
std::optional<std::string> ReadFileAsString(std::string& filePath)
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
    std::optional<std::string> data = ReadFileAsString("data.txt");
    std::string value = data.value_or("------Not present------");  // set default value
    std::cout << value << std::endl;
    if (data)
    {
        std::cout << "File read successfully!\n";
    }
    else
    {
        std::cout << "File could not be opened!\n";
    }
}
```