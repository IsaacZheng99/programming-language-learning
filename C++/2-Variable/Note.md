## 2. Variable

**Knowledge Points**: `size` of `variables`, `sizeof()`

1. `variables` are stored in memory, which is called `stack` or `heap`

2. the only difference of `variables` of `C++` is **size**, i.e., how much the memory does the variable occupy, i.e., how much memory will be allocated when you create a `variable`

3. different primitive integer types

    ```c++
    char       // 1 byte
    short      // 2 bytes
    int        // 4 bytes
    long       // 4 or 8 bytes, depending on the compiler and the platform
    long long  // 8 bytes
      
    unsigned int
    ...
    ```

4. `char` and `short`

    ```c++
    // different output based on operator overloading of "operator<<()"
    char a0 = 'A'
    char a1 = 65
    std::cout << a0 << std::endl;  // A
    std::cout << a1 << std::endl;  // A
    
    short a2 = 'A'
    short a3 = 65
    std::cout << a2 << std::endl;  // 65
    std::cout << a3 << std::endl;  // 65
    ```

5. `float` and `double`

    ```c++
    // add "f" or "F" at the end to make your code: 
    // 1. more readable
    // 2. save memory (in this case no memory save)
    // 3. have less overhead (type conversion costs)
    // 4. safer (type conversion may bring problems like accuracy loss, in this case there is no accuracy loss because 5.5 is in the scope of float)
    // 5. avoid cross-platform problem (in different platforms, the way of type conversion may differ)
    float f0 = 5.5f;
    float f1 = 5.5F;
    double d = 5.5;
    ```

6. `bool`

    ```c++
    bool var = true;
    std::cout << var << std::endl;  // 1
    bool a = 123;
    std::cout << a << std::endl;  // 1
    bool b = 0;
    std::cout << b << std::endl;  // 0
    bool c = -1;
    std::cout << c << std::endl;  // 1
    // 0 means "false" and anything except 0 means "true"
    // "bool" variable does take 1 bit to represent, however when addressing memory, we can't address 1 bit, so we can't create a 1-bit variable
    // one advanced fun trick is to use 1 byte to store 8 "bool" variables
    ```

7. `sizeof()`

    ```c++
    std::cout << sizeof(bool) << std::endl;  // 1
    std::cout << sizeof bool << std::endl;  // 1, no brackets is also fine
    std::cout << sizeof(int) << std::endl;  // 4
    std::cout << sizeof(double) << std::endl;  // 8
    
    int a = 1;
    std::cout << sizeof(a) << std::endl;  // 4
    ```

8. ```c++
    int* a = 1;  // asterisk
    int& b = 2;  // ampersand
    ```

