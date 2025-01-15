## 13. Enum

**Knowledge Points**: `enum`, `enum class`, `value of enum`, `type of enum`,  `difference between enum and enum classs`

1. **what is enum**: 

    `enum` is just a way to give a name to a set of values, so we don't have to keep dealing with integers

2. **value of enum**: 

    begin with `0` in default: 

    ```c++
    enum Example2
    {
        A1 = 1, B1, C1  // 1, 2, 3
    };
    ```

    explicitly set the first value: 

    ```c++
    enum Example2
    {
        A2 = 1, B2, C2  // 1, 2, 3
    };
    ```

    explicitly set all the values: 

    ```c++
    enum Example3
    {
        A3 = 2, B3 = 5, C3 = 8  // 2, 5, 8
    };
    ```

    the value of an `enum-type` data is limited: 

    ```c++
    int main()
    {
        Example1 value1 = Example1::B1;
        Example1 value2 = 1;  // Wrong! Compiling error.
        Example1 value3 = C1;
    }
    ```

3. **type of enum**: 

    must be `integer` types, `int`, `char`, `unsigned char`... we can save memory by using `char` instead of `int` if it's fine

    ```c++
    enum Example4  // by default, int
    {
        A4, B4, C4
    };
    
    enum Example5: char
    {
        A5, B5, C5
    };
    
    enum Example6:
    {
        A6 = 0.1, B6, C6  // Wrong! Compiling error.
    };
    
    int main()
    {
        std::cout << sizeof(Example4) << std::endl;  // 4
        std::cout << sizeof(Example5) << std::endl;  // 1
    }
    ```

4. **enum class**: 

    ```c++
    enum class Example7:
    {
        A7, B7, C7
    };
    
    int main()
    {
        Example7 value7 = Example7::A7;
        Example7 value8 = B1;  // Wrong! Compiling error.
        Example7 value9 = 2;  // Wrong! Compiling error.
        int b = Example7::A7;  // Wrong! Compiling error.
    }
    ```

5. **enum vs. enum class**

    1. **scope**: 

        `enum` has weak scope, we can directly use `Example1 value1 = A1;` and the names of the `variables` **shouldn't** be the same across different `enums`

        `enum class` has strong scope, we have to use `Example7 value7 = Example7::A7` and the names of the `variables` across `enum class` can be the same

    2. **type safety**: 

        `enum` is not type safety, we can assign an `enum` to an integer: `int a = Example1::A1;`

        `enum class` is type safety, we need to explicitly cast

    3. **comparison**: 

        we can directly compare value of two `enums`, but we can't do that for `enum class`

6. **improve class Log with enum** (check the `Code` part)