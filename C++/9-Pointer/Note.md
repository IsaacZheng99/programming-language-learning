## 9. Pointer

**Knowledge Points**: `pointer`, `null pointer`, `void pointer`, `dereference`, `stack`, `heap`, `double pointer`, `triple pointer`

1. **pointer**: 

    1. a `pointer` is just an **address**, it is an **integer** which holds a memory address
    2. just foget the type, `int*` or `Entity*`, here the `type` **doesn't matter** and we are just saying the data at that address is pre-assumed to be the type and the `type` helps when we need to **manipulate the memory**, like **read** or **write**

2. **null pointer**: 

    ```c++
    void* nptr1 = 0;  // 0 is an invalid address and being invalid is acceptable for a pointer
    void* nptr2 = NULL;  // #define NULL 0 (check the head file "vcruntime.h")
    void* nptr3 = nullptr;  // "nullptr" is a key word
    ```

    it's also fine if you assign `nullptr` to a `non-void pointer`

    ```c++
    int* nptr4 = nullptr;
    double* nptr5 = nullptr;
    ```

3. **dereference**: 

    ```c++
    int var = 8;
    int* ptr = &var;
    std::cout << *ptr << std::endl;  // Dereference a pointer to access the data
    ```

    it will cause `compiling error` if you want to `read` or `write` data by a `void*`: 

    ```c++
    void* p = &var;
    std::cout << *p << std::endl;  // Wrong!
    *p = 9;  // Wrong!
    
    // This will cause "compiling error" because the compiler doesn't know how much memory should be read or allocated as the type of the pointer is "void".
    ```

    `dereference` a `nullptr`: 

    ```c++
    void* nptr1 = 0;
    std::cout << *nptr1 << std::endl;  // Wrong! Read data by a "void*"
    ```

    ```c++
    int* nptr4 = nullptr;
    std::cout << *nptr4 << std::endl;  // Wrong!
    *nptr4 = 1;  // Wrong!
    
    // This will cause run time error or throw an exception when debugging because of "access violation"
    ```

4. **create data on the stack or the heap**: 

    ```c++
    // on the stack
    int a = 1;
    
    // on the heap
    char* buffer = new char[8];  // ask for 8-byte memory
    memset(buffer, 0, 8);  // set "value = 0" for 8-byte data
    delete[] buffer;
    ```

5. **double pointer, triple pointer ...** : 

    `pointer` is also a `variable` and it's stored in the memory, so we can get `double pointer`, `triple pointer` ...