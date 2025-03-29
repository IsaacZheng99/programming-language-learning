## 67. Make String Faster

**Knowledge Points**: `how std::string allocates`, `std::string_view`

### 1. why std::string slow

`std::string` and a lot of its methods like to **allocate**, which severely affects the performance

### 2. how std::string allocates

first we overload `operator new` to track the allocation: 

```c++
static uint32_t s_AllocCount = 0;

void* operator new(size_t size)  // overloading "operator new" is a good way to track the allocation
{
    s_AllocCount++;
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}
```

a `function` to print a string: 

```c++
void PrintName(const std::string& name)
{
    std::cout << name << std::endl;
}
```

#### 1. print a std::string

```c++
int main()
{
    std::string name = "xiaoli";
    PrintName(name);
    
    std::cout << s_AllocCount << " allocations\n";  // 1
}
// outputs
// Allocating 16 bytes
// xiaoli
// 1 allocations
```

#### 2. directly pass a const char*

```c++
int main()
{
    PrintName("xiaoli");
    
    std::cout << s_AllocCount << " allocations\n";  // 1, even if we use "const std::string& name" in the "PrintName()" function, there is still an allocation because of implicit construction
    
    std::cin.get();
}
// Allocating 16 bytes
// xiaoli
// 1 allocations
```

#### 3. a more complicated example

```c++
int main()
{
    std::string name = "xiaoli";
    std::string firstName = name.substr(0,4);
    std::string lastName = name.substr(4,6);
    
    PrintName(firstName);
    
    PrintName(name.substr(0,4))
    
    std::cout << s_AllocCount << " allocations\n";
}
// outputs:
// Allocating 16 bytes
// Allocating 16 bytes
// Allocating 16 bytes
// xiao
// Allocating 16 bytes
// xiao
// 4 allocations
```

### 3. std::string_view

1. the code `PrintName(name.substr(0,4))` in `2.3` also does the allocation because it creates a whole new string, but what we really want is just a "view" into the original string and we don't want any new strings, so here comes the `std::string_view`

2. a new `class` in `C++17` and it is essentially a `pointer` to the existing memory, i.e., a `const char*` pointing to any existing strings, plus a `size`

```c++
void PrintName(std::string_view name)
{
    std::cout << name << std::endl;
}

int main()
{
    std::string name = "xiaoli";  // create a std::string at first
    
    std::string_view firstName(name.c_str(), 4);
    std::string_view lastName(name.c_str() + 4, 2);
    
    PrintName(firstName);
    
    std::cout << s_AllocCount << " allocations\n";
}
// outputs:
// Allocating 16 bytes
// xiao
// 1 allocations
```

```c++
void PrintName(std::string_view name)
{
    std::cout << name << std::endl;
}

int main()
{
    const char* name = "xiaoli";  // directly use a const char*
    
    std::string_view firstName(name, 4);
    std::string_view lastName(name + 4, 2);
    
    PrintName(firstName);
    PrintName("xiaoli");
    
    std::cout << s_AllocCount << " allocations\n";
}
// outputs:
// xiao
// xiaoli
// 0 allocations
```

