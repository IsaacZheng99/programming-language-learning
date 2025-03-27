## 64. Multiple Types of Data in a Single Variable

**Knowledge Points**: `std::variant<>`, `index()`, `std::get_if<>()`, `std::variant<> vs. std::optional<>`, `std::variant<> vs. union`

### 1. when to use

when we don't want to worry about the **exact types** of the data and just use **one single variable**, we can make it by `union` but `std:variant<>` has its own benefits

### 2. some examples

#### 1. std::variant<>

```c++
int main()
{
    // a new class in "C++17"
    std::variant<std::string, int> data;  // list all the possible types in the template
    data = "xiaoli";
    std::cout << std::get<std:string>(data) << std::endl;;  // xiaoli
    data = 1;
    //std::cout << std::get<std::string>(data);  // Wrong! running error
    std::cout << std::get<int>(data) << std::endl;  // 1
}
```

#### 2. std::variant<>::index()

```c++
int main()
{
    std::variant<std::string, int> data;
    data = 1;
    std::cout << std::get<int>(data) << std::endl;  // 1
    std::cout << data.index() << std::endl;  // 1, tell which index the current data being stored in
}
```

#### 3. std::get_if<>()

```c++
int main()
{
    std::variant<std::string, int> data;
    data = 1;
    if (auto ptr = std::get_if<std::string>(&data))
    {
        std::string& value = *ptr;
        std::cour << value << std::endl;
    }
    else if (auto ptr = std::get_if<int>(&data))
    {
        int* value = ptr;
        std::cout << *value << std::endl;
    }
}
```

#### 4. std::variant<> vs. std::optional<>

1. `std::optional<>`: 

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
    ```

2. `std::variant<>`: 

    ```c++
    // instead of returning the "null string", we can return an "error code", which will give us more information
    enum class ErrorCode
    {
    	None = 0, NotFound, NotAccess  
    };
    
    std::variant<std::string, ErrorCode> ReadFileAsString(std::string& filePath)
    {
        std::variant<std::string, ErrorCode> result;
        
        std::ifstream stream(filePath);
        if (stream)
        {
            std::string data;
            // read file
            stream.close();
            result = data;
            return result;
        }
        
        result = ErrorCode::None;
        
        return result;
    }
    
    int main()
    {
        std::variant<std::string, ErrorCode> result = ReadFileAsString("data.txt");
        if (auto ptr = std::get_if<std::string>(&result))
        {
            std::string data = *ptr;
            std::cout << data << std::endl;
        }
        else if (auto ptr = std::get_if<ErrorCode>(&result))
        {
            Errorcode error = *ptr;
            std::cout << static_cast<int>(error) << std::endl;
        }
    }
    ```

### 3. difference between std::variant<> and union

1. technically, `union` is more efficient, however `std::variant<>` is much more `type safe` and won't have `undefined behavior`
2. you **should** use `std::variant<>` unless you are really kind of doing low-level optimization

```c++
int main()
{
    union Data
    {
    	std::string s;
        int v;
    };
    
    std::variant<std::string, int> data;
    
    std::cout << sizeof(Data) << std::endl;         // 40
    std::cout << sizeof(data) << std::endl;         // 48  basically what it has done is just kind of create a struct or class for you, it just stores those two data types as separate variables as separate members in a class or struct
    std::cout << sizeof(int) << std::endl;          // 4
    std::cout << sizeof(std::string) << std::endl;  // 40
}
```

