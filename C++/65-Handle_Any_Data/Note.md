## 65. Handle Any Data

**Knowledge Points**: `std::any`, `std::any_cast<>()`, `std::any vs. std::variant<>`,`reference in std::any_cast<>() and std::get<>()`, `dynamic allocation for std::any`

### 1. how to store any kind of data in a single variable

we can do this via a `void pointer`

### 2. std::any vs. std::variant<>

1. for `std::any`, you don't need to write the possible types, but it's **less** type safe
2. when `std::any` is used with **big-size** data, it will **dynamically** allocates the memory, therefore when dealing with large data and you are avoiding dynamic allocation, `std::variant<>` will become faster (check the source code to see more)
3. in general, it's **not** good to use `std::any`, if you really need to use any types, maybe you need to redesign your code first and not to mention we have `void*`

### 3. some examples

#### 1. std::any

```c++
int main()
{
    std::any data;  // a new class in "C++17"
    data = 1;
    data = "xiaoli";
    data = std::string("xiaoli");
    //std::cout << data << std::endl;  // Wrong! Compiling error
}
```

#### 2. std::any_cast<>()

```c++
int main()
{
    std::any data;
    data = 1;
    data = std::string("xiaoli");
    // if you want to retrive your data from "data", you have to do more work
    std::string value = std::any_cast<std::string>(data);
    std::cout << value << std::endl;  // xiaoli
    // int value = std::any_cast<int>(data);  // Wrong! Runtime error
}
```

#### 3. std::any vs. std::variant<>

```c++
int main()
{
    std::any data1;
    data1 = 1;
    data1 = "xiaoli";
    //std::string value1 = std::any_cast<std::string>(data1);  // Wrong! Runtime error
    
    std::variant<int, std::string> data2;
    data2 = 1;
    data2 = "xiaoli";
    std::string value2 = std::get<std::string>(data2);  // implicit conversion
}
```

#### 4. reference in std::any_cast<>() and std::get<>()

```c++
int main()
{
    std::any data1;
    data1 = std::string("xiaoli");
    std::string& value1 = std::any_cast<std::string&>(data1);  // compared with "std::string value1 = std::any_cast<std::string>(data1);", which will copy, but in the "reference" case, there won't have copy
    // std::string& value1 = std::any_cast<std::string>(data1);  // Wrong! Compiling error
    
    std::variant<int, std::string> data2;
    data2 = "xiaoli";
    std::string& value2 = std::get(std::string)(data2);
    // std::string& value2 = std::get(std::string&)(data2);  // Wrong! Compiling error
}
```

#### 5. dynamic allocation 

when it comes to the large data, you will see the **dynamic allocation** in the `Debug` mode

```c++
void* operator new(size_t size)
{
    return malloc(size);  // breakpoint here
}

class Custom
{
    std::string s;
    float f;
    char c;
}

int main()
{
    std::any data;
    data = Custom();  // large data
}
```

