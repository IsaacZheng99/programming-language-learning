## 21. String

**Knowledge Points**: `raw string`, `size of string`, `\0 in the middle`, `string appending`, `find`, `string as parameter`

1. **what is string**: 

    a `string` is an `array` of `characters`

2. **raw string**: 

    **null termination character**: 

    ```c++
    int main()
    {
        const char* name = "xiaoli";
        // if we check the memory, we will see there is a "0x00" behind the "Li" ascii code: 78 69 61 6f 6c 69, this is called the "null termination character" and that is how we know that is where the string ends, note that we don't know what the size of "xiaoli" is
    
        char name2[6] = {'x', 'i', 'a', 'o', 'l', 'i'}
        std::cout << name2 << std::endl;  // xiaoli烫烫烫烫烫H渏 if we check the memory of name2, there are some "array guards" behind "xiaoli", which tell us it comes outside of our memory
    
        char name3[7] = {'x', 'i', 'a', 'o', 'l', 'i', '\0'}
        char name4[7] = {'x', 'i', 'a', 'o', 'l', 'i', 0}
        std::cout << name3 << std::endl;  // xiaoli
        std::cout << name4 << std::endl;  // xiaoli
    }
    ```

3. **std::string**: 

    1. **size of string**: 

        1. **std::string::size()** and **strlen()**

            ```c++
            int main()
            {
                std::string name = "xiaoli";
                std::cout << name.size() << std::endl;  // 6
                char* name2 = (char*)"xiaoli";
                std::cout << strlen(name2) << std::endl;  // 6
            }
            ```

        2. **when the string literal contains '\0' in the middle:** 

            ```c++
            int main()
            {
                std::string name = "xiao\0li";
                std::cout << name << std::endl;  // xiao
                std::cout << name.size() << std::endl;  // 4
                
                const char* name2 = "xiao\0li";
                std::cout << name2 << std::endl;  // xiao
                std::cout << strlen(name2) << std::endl;  // 4
                std::cout << sizeof(name2) << std::endl;  // 4 (note that "4" is the size of the "char*")
            }
            ```

            `std::string` has another `constructor`: 

            ```c++
            int main()
            {
                char name[] = "xiao\0li";
                std::cout << name << std::endl;  // xiao
                std::cout << strlen(name) << std::endl;  // 4
                std::cout << sizeof(name) << std::endl;  // 8
                
                std::string name2(name, sizeof(name) - 1);
                std::cout << name2 << std::endl;  // xiaoli
                std::cout << name2.size() << std::endl;  // 7
                for (int i = 0; i < name2.size(); i++)
                    std::cout << name2 << ", ";  // x, i, a, o, , l, i,
            }
            ```

    2. **string appending**: 

        1. **add two pointers**: 

            ```c++
            int main()
            {
                std::string name = "xiaoli" + "Hello";  // Wrong! Here we are just trying to add two "const char*", but we can't add two pointers.
            }
            ```

        2. **std::string plus pointer**: 

            ```c++
            int main()
            {
                std::string name = "xiaoli";
                name += "Hello";  // we are adding a pointer to a string and "+=" is overloaded in the "std::string" class
            }
            ```

            we can also `explicitly cast` first: 

            ```c++
            int main()
            {
                std::string name = (std::string)"xiaoli" + "Hello";
            }
            ```

    3. **find**: 

        ```c++
        int main()
        {
            std::string name = "xiaoli";
            if (name.find("li") != std::string:npos)
                std::cout << "In!" << std::endl;
        }
        ```

4. **string as parameter**: 

    1. **copy**: 

        ```c++
        void PrintString(std::string string)
        {
            // in this case, we will copy the character data string on the heap, which costs much and if you want to modify the "string" variable, the original "string" won't be modified
          	string += "Hello";
            std::cout << string << std::endl;
        }
        
        int main()
        {
            std::string name = "xiaoli";
            PrintString(name);  // xiaoliHello
            std::cout << name << std::endl;  // xiaoli
        }
        ```

    2. if this is a `read-only` `function`, we can use the `const` key word, and we use `&` to avoid copying

        ```c++
        void PrintString(const std::string& string)
        {
            std::cout << string << std::endl;
        }
        ```

