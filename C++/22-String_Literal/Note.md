## 22. String Literal

**Knowledge Points**: `srting literal`, `memory of string literal: const section`, `other types of character`, `string appending: s and R`

1. **what is string literal**: 

    `string literal` is basically a series of characters between two double quotes

    ```c++
    "xiaoli";
    ```

2. **const section**: 

    ```c++
    int main()
    {
        char* name = (char*)"xiaoli";
        name[0] = 'a';
        std::cout << name << std::endl;  // this will throw an exception, because if you check the binary code file, you will see the string "xiaoli" is in the const section (which is read-only memory), which can't be modified
    }
    ```

    if you want to modify for some reason, just define it as an `array`, not a `pointer`: 

    ```c++
    int main()
    {
        char name[] = "xiaoli";
        name[0] = 'a';
        std::cout << name << std::endl;  // "aiaoli"
    }
    ```

    remember to use `const` when you use `string literal` like this:

    ```c++
    int main()
    {
        const char* name = "xiaoli";
    }
    ```

3. **other types of character**: 

    ```c++
    const char8_t* name = u8"xiaoli";  // 1 byte for one character
    const wchar_t* name = L"xiaoli";   // 2 or 4 bytes
    const char16_t* name = u"xiaoli";  // 2 bytes
    const char32_t* name = U"xiaoli";  // 4 bytes
    ```

4. **string appending**: 

    1. **namespace std::string_literals**: 

        ```c++
        int main()
        {
          using namespace std::string_literal;
          
          std::string name1 = "xiao"s + "Hello";  // here "s" is essentially a function
          std::wstring name2 = L"xiaoli"s + L"Hello";
          std::u32string name3 = U"xiaoli"s + U"Hello";
        }
        ```

    2. **prefix R**: 

        ```c++
        int main()
        {
            const char* txt1 = R"(Line1
        Line2
        Line3)";  // here "R" helps us ignore the escape characters
            std::cout << txt1 << std::endl;
          	// output: 
            // Line1
            // Line2
            // Line3
          
          	const char* txt2 = "Line1\n"
                "Line2\n"
                "Line3\n";
          	std::cout << txt2 << std::endl;
          	// output: 
            // Line1
            // Line2
            // Line3
          
          	const char* txt3 = "Line1"
                "Line2"
                "Line3";
          std::cout << txt3 << std::endl;
          // Line1Line2Line3
        }
        ```

5. **memory of string literals**: 

    `string literals` are always stored in `read-only` memory

    ```c++
    int main()
    {
        char name[] = "xiaoli";
        name[0] = 'q';
        std::cout << name << std::endl;
      
        // if you check the assembly code, you will see the "xiaoli" is still in the cosnt segment and the compiler just copys "xiaoli" to "name"
        // if there is no such the "copy" code, we are going to write to the const data, which is illegal
    }
    ```

    

    