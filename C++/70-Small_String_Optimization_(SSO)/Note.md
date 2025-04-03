## 70. Small String Optimization (SSO)

**Knowledge Points**: `SSO`, `_Mypair._Myval12__Myres`

### 1. the storage stragety

1. people like to use `const char* name = "xiaoli"` to avoid `heap allocation` brought by `std::string` but in fact `std::string name = "xiaoli"` is fine because of `SSO`
2. there is a `static storage` on the `stack` for strings that are below a certain length (it's `15-character` length in `vs2022`)

2. check the source code of `std::string` and see the `basic_string& assign()` function, there is a `variable` called `_Mypair._Myval12__Myres`

### 2. some examples

#### 1. a small string

run the program in the `Release` mode, there is no allocation

```c++
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

int main()
{
    std::string name = "xiaoli";
    
    std::cin.get();
}
```

#### 2. a 15-character-long string

```c++
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

int main()
{
    std::string name = "xiaoli666666666";  // 15 characters, still no allocation
    
    std::cin.get();
}
```

#### 3. a big string

```c++
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

int main()
{
    std::string name = "xiaoli6666666666";  // 16 characters
    
    std::cin.get();
}
// outputs:
// Allocating 32 bytes
```

