## 39. Multiple Return Values

**Knowledge Points**: `different ways to handle multiple return values with same type or different types`

### 1. use input parameters

there is a `function` which "returns" two `std::string` objects

1. **use reference**: 

    ```c++
    // use reference and not return anything
    void ReturnTwoStrings(std::string& outFirstString, std::string& outSecondString)
    {
        // do something and get two strings
        std::string fs = "fs";
        std::string ss = "ss";
    
        // this is kind of good and you just need to copy here
        outFirstString = fs;
        outSecondString = ss;
    }
    
    int main()
    {
        std::string fs, ss;
        ReturnTwoStrings(fs, ss);
        std::cout << fs << std::endl;  // fs
        std::cout << ss << std::endl;  // ss
    }
    ```

2. **use pointer**: 

    ```c++
    // use pointer and not return anything
    void ReturnTwoStrings(std::string* outFirstString, std::string* outSecondString)
    {
        // do something and get two strings
        std::string fs = "fs";
        std::string ss = "ss";
    
        if (outFirstString)
        	*outFirstString = fs;
        if (outSecondString)
    		*outSecondString = ss;
    }
    
    int main()
    {
        std::string fs, ss;
        ReturnTwoStrings(&fs, &ss);
        std::cout << fs << std::endl;  // fs
        std::cout << ss << std::endl;  // ss
        // ReturnTwoStrings(nullptr, &ss);  // you can also set the first parameter as "nullptr", meaning you just focus on the second std::string
    }
    ```

### 2. return an array

`array` can only handle `values with the same type`

1. **return a raw array**: 

    ```c++
    std::string* ReturnTwoStrings()
    {
        // do something and get two strings
        std::string fs = "fs";
        std::string ss = "ss";
    
        return new std::string[2]{fs, ss};  // this is a little annoying because we create the array on the heap and this function simply returns a pointer, which means we can't know how big the array is at the returning place
    }
    
    int main()
    {
        std::string* twoStrings = ReturnTwoStrings();
        std::cout << twoStrings[0] << std::endl;  // fs
        std::cout << twoStrings[1] << std::endl;  // ss
    }
    ```

2. **return a std::array<>**: 

    ```c++
    std::array<std::string, 2> ReturnTwoStrings()
    {
        // do something and get two strings
        std::string fs = "fs";
        std::string ss = "ss";
    
        return std::array<std::string, 2>{fs, ss};
    }
    
    int main()
    {
        std::arrat<std::string, 2> twoStrings = ReturnTwoStrings();
        std::cout << twoStrings[0] << std::endl;  // fs
        std::cout << twoStrings[1] << std::endl;  // ss
    }
    ```

3. **return a std::vector<>**: 

    ```c++
    // "std::array" is going to be created on the stack while "std::vector" is on the heap, so technically returning a "std::array" would actually be faster
    std::array ReturnTwoStrings()
    {
      // do something and get two strings
      std::string fs = "fs";
      std::string ss = "ss";
      
      return std::array<std::string, 2>{fs, ss};
    }
    
    int main()
    {
      std::array<std::string, 2> twoStrings = ReturnTwoStrings();
      std::cout << twoStrings[0] << std::endl;  // fs
      std::cout << twoStrings[1] << std::endl;  // ss
    }
    ```

### 3. return a std::tuple<>

`std::tuple<>`: contains `x` amount of `variables` and **doesn't** care about the `types`, meaning the `variables` can have arbitrary types and we use template to control

```c++
std::tuple<std::string, std::string> ReturnTwoStrings()
{
    // do something and get two strings
    std::string fs = "fs";
    std::string ss = "ss";

    return std::make_pair(fs, ss);
}

int main()
{
    std::tuple<std::string, std::string> twoStrings = ReturnTwoStrings();
    // using "0" and "1" is hard to read
    std::cout << std::get<0>(twoStrings) << std::endl;  // fs
    std::cout << std::get<1>(twoStrings) << std::endl;  // ss
}
```

### 4. return a std::pair<>

`std::pair<>`: contains `2` `variables` and **doesn't** care about the `types`

```c++
std::pair<std::string, std::string> ReturnTwoStrings()
{
    // do something and get two strings
    std::string fs = "fs";
    std::string ss = "ss";

    return std::make_pair(fs, ss);
}

int main()
{
    std::pair<std::string, std::string> twoStrings = ReturnTwoStrings();
    // besides using "std::get<>"", we can also use "first" and "second" for "std::pair<>", but this is also hard to read
    std::cout << std::get<0>(twoStrings) << std::endl;  // fs
    std::cout << std::get<1>(twoStrings) << std::endl;  // ss
    std::cout << twoStrings.first << std::endl;  // fs
    std::cout << twoStrings.second << std::endl;  // ss
}
```

### 5. return a struct (best in general)

create a custom `struct` to store the values

```c++
struct TwoStrings
{
    std::string FirstString;
    std::string SecondString;
};

TwoStrings ReturnTwoStrings()
{
    // do something and get two strings
    std::string fs = "fs";
    std::string ss = "ss";

    return { fs, ss };
}

int main()
{
    TwoStrings twoStrings = ReturnTwoStrings();
    std::cout << twoStrings.FirstString << std::endl;  // fs
    std::cout << twoStrings.SecondString << std::endl;  // ss
}
```

