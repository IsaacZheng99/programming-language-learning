## 20. Array

**Knowledge Points**: `raw array`,  `array and pointer`, `how array stores data`, `create an array by new`, `memory indirection`, `size of array`, `std::array<>`

1. **raw array**: 

    in this chapter, we mainly talk about `raw array` in `C++`, not `std::array<>` or `std::vector<>`

2. **array and pointer**: 

    1. `pointer` is the basement of how `array` works in `C++`
    2. an `array` is really just a `pointer`

3. **how array stores data**: 

    `array` stores data continuously

    ```c++
    int main()
    {
        int example[5];
        int* ptr = example;
    
        example[2] = 1;  // set the third element to 1
        *(ptr + 2) = 2;  // set the third element to 2
        *(int*)((char*)ptr + 8) = 10000;  // set the third element to 10000
        // *((char*)ptr + 8) = 10000; although the output of "example[2]" is also "10000", but in fact there has truncation in this case
    }
    ```

4. **why need new**: 

    if you create an `array` inside a `function` and you want to return it, you need to use `new` to create it on the `heap` unless you pass an address of an `array` by parameter and return this address

    ```c++
    int main()
    {
      int example1[5];  // created on stack and exists until the end braket
      
      int* example2 = new int[5];  // created on heap and we need to delete it
      delete[] example2;
    }
    ```

    ```c++
    int* Function()
    {
        int array[5];
        int* ptr = array;
        return ptr;
    }
    
    int* FunctionWithNew()
    {
        int* ptr = new int[5];
        return ptr;
    }
    
    int main()
    {
        int* ptr = Function();  // Warning!
        int* ptrToNew = FunctionWithNew();
    }
    ```

5. **memory indirection**: 

    `memory indirection`can cause `memory fragmentation`, `cache miss`, ... so if possible, it would be better to create `array` on the `stack`, because jumping among memory definitely affects performance

    ```c++
    class Entity
    {
    public:
        int example[5];
      
        Entity()
        {
            example[2] = 2;
        }
    };
    
    int main()
    {
        Entity e;  // if we check the memory by using the address of "e", we will see the data of "example" directly
    }
    ```

    ```c++
    class Entity
    {
    public:
        int* example = new int[5];
      
        Entity()
        {
            example[2] = 2;
        }
    };
    
    int main()
    {
        Entity e;  // if we check the memory by using the address of "e", we will see there is an address, which is the "example" pointer (i.e., the address of the array): f8 81 ca 00, and then if we check the memory 0x00ca81f8, we will see the data of the "example" array
    }
    ```

6. **size of array**: 

    **stack-based array**: 

    ```c++
    class Entity
    {
    public:
        int example[5];
    
        int GetCount()
        {
            return sizeof(example) / sizeof(int);  // we can get both the size and count of the array if it's created on the stack
        }
    };
    ```

    **heap-based array**: 

    ```c++
    class Entity
    {
    public:
        int* example = new int[5];
    
        int GetCount()
        {
            return sizeof(example) / sizeof(int);  // we will get sizeof(example) = 4 and count = 1 as the array is created on the heap
        }
    };
    ```

    **add an extra variable for recording**: 

    ```c++
    class Entity
    {
    public:
    	static const int exampleElementCount = 5;  // we need a variable to record the count
    	int* example = new int[exampleElementCount];
    
    	int GetCount()
        {
            return exampleElementCount;
        }
    };
    ```

7. **std::array<>**: 

    `std::array<>` brings more overhead: bounds checking, maintain the size integer, but more safer (details about `std::array<>` will be introduced in the later chapter)

    ```c++
    class Entity
    {
    public:
        std::array<int, 5> example;
    
        int GetCount()
        {
            return example.size();
        }
    };
    ```

