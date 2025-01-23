## 44. Static Array

**Knowledge Points**: `std::array<>`, `advantages of std::array<>`

### 1. std::array<>

1. **template parameter**: 

    two template parameters in `std::array<>`: `data type` and `size`, and we can simply specify `data type` (`std::array<typename _Ty, 0Ui64>`, but I have tried to just use one template parameter, it doesn't work)

2. **compare with C-style raw array**: 

    almost the **same**

    ```c++
    int main()
    {
        int array1[5];
        array1[0] = 1;
        
        std::array<int, 5> array2;
        array2[0] = 1;
    }
    ```

### 2. advantages of std::array<>

We can't use new things just because they are new, they have to actually do better, such as convenience, better performance. If they make the program slower, why should we use them?

1. **keep track of the size**: 

    here we want to iterate an array:

    1. for the `C-style raw array`, we need another parameter to get the `size`: 

        ```c++
        void PrintArray(int* array, unsigned int size)
        {
            for (int i = 0; i < size; i++)
            {
                
            }
        }
        ```

    2. for `std::array<>`, we can directly specify the `size` in the `template` of `std::array<>`: 

        ```c++
        void PrintArray(const std::array<int, 5>& data)  // specify the size parameter
        {
            for (int i = 0; i < 5; i++)
            {
                
            }
        }
        ```

        we can also call the `size()` `method`: 

        ```c++
        void PrintArray(const std::array<int, 5>& data)  // specify the size parameter
        {
            for (int i = 0; i < data.size(); i++)
            {
                
            }
        }
        ```

    3. use `template function`: 

        ```c++
        template<int N>
        void PrintArray(const std::array<int, N>& data);
        ```

        ```c++
        template<typename T, int N>
        void PrintArray(const std::array<T, N>& data);
        ```

        ```c++
        template<typename T>
        void PrintArray(const T& data);
        ```

2. support `iterator`: 

    `std::array<>::begin()`, `std::array<>::end()`

    ```c++
    int main()
    {
        std::array<int, 5> array({ 1, 2, 3, 4, 5 });
        for (auto it = array.begin() + 1; it != array.end() - 1; it++)
            std::cout << *it << std::endl;
    }
    // output:
    // 2
    // 3
    // 4
    ```

3. support `STL algorithms`: 

    because `std::array<>` support `iterator`, so it can use many `STL algorithms`: e.g., `std::sort()`

    ```c++
    int main()
    {
        std::array<int, 5> array({ 5, 2, 3, 4, 1 });
        std::sort(array.begin(), array.end());
        for (int value : array)
            std::cout << value << std::endl;
    }
    // output:
    // 1
    // 2
    // 3
    // 4
    // 5
    ```

4. support `bounds checking`: 

    in the `Debug` mode, there is a `marco` called `_CONTAINER_DEBUG_LEVEL` and `#if _CONTAINER_DEBUG_LEVEL > 0` is used in the `operator[]`

    ```C++
    int main()
    {
        int array1[5];
        array1[0] = 1;
        array1[5] = 1;  // Wrong! this will cause compiling error in the "Debug" mode and run successfully in the "Release" mode
        
        std::array<int, 5> array2;
        array2[0] = 1;
        array2[5] = 1;  // Wrong! this will cause crash in the runtime in the "Debug" mode and run successfully in the "Release" mode
        
        array2.at(5);  // Wrong! this will cause crash in the runtime in the "Debug" mode and throw an exception in the "Release" mode
    }
    ```

5. performance: 

    1. `std::array<>` is very fast and with maximum optimiztion of max speed level and just same as the normal array

    2. how much memory does `std::array<>` occupy because it "stores" the `size`: 

        **no**, `std::array<>` actually doesn't store the `size`

        `std::array<>.size()`: if you check the source code of `std::array<>`, you'll find that there is **no** extra `variable` to store the `size`, the `size()` `function` literally returns the `template parameter` `_Size` directly, which is just `5` in the case of `std::array<int, 5>`, not a `variable` 

    3. it actually brings **no** extra performance cost

### 3. wher is std::array<> stored

`std::array<>` and normal array (e.g., `int array[5]`) are created on the `stack` while `std::vector<>` is created on the `heap`

