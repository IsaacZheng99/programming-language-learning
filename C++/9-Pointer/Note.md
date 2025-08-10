## 9. Pointer

**Knowledge Points**:

1. `pointer: address, type of pointer`
2. `null pointer: 0, NULL, nullptr; type of nullptr: std::nullptr_t`
3. `void pointer`
4. `dereference: deference a void* pointer; deference a null pointer`
5. `create data: stack, heap, static storage area`
6. `double pointer, triple pointer`

### 1. Pointer

1. A `pointer` is just an **address**, it is an **integer** which holds a `memory` address.
2. Just foget the type, `int*` or `Entity*`, here the `type` **doesn't matter** and we are just saying the data at that address is **pre-assumed** to be the `type` and the `type` helps when we need to **manipulate the memory**, like **read** or **write**.

### 2. Null pointer

#### 1. How to get null pointer

##### 1. Set the value of a pointer as 0

`0` is an **invalid** address, but being invalid is acceptable for a `pointer`, which is `null pointer`.

```c++
void* nptr = 0;
```

##### 2. Marco NULL

`NULL` is a `marco` in `C++`,   we can check the header file `vcruntime.h` and see `#define NULL 0`.

```c++
void* nptr = NULL;
```

##### 3. Key word nullptr

`nullptr` is a key word for `null pointer`.

```c++
void* nptr = nullptr;
```

#### 2. Assign nullprt to a non-void pointer

It's also fine if we assign `nullptr` to a `non-void pointer`.

```c++
int* nptr4 = nullptr;
double* nptr5 = nullptr;
```

#### 3. Type of nullptr

The `type` of `nullptr` is `std::nullptr_t`.

```c++
std::cout << typeid(nullptr).name() << std::endl;  // std::nullptr_t
```

### 3. Dereference

1. We can `deference` a `pointer` to access the data.

    ```c++
    int var = 8;
    int* ptr = &var;
    std::cout << *ptr << std::endl;  // 8
    ```

2. It will cause `compiling error` if we want to `read` or `write` data by a `void*` because the `compiler` doesn't know **how much memory** should be read or allocated as the type of the `pointer` is `void`.

    ```c++
    int var = 1;
    void* ptr = &var;
    std::cout << *ptr << std::endl;  // Wrong! error C2100: you cannot dereference an operand of type 'void'
    *ptr = 9;  // Wrong! error C2100: you cannot dereference an operand of type 'void'
    ```

3. If we `dereference` a `nullptr`, it will cause `runtime error`, which is `null pointer access`.

    ```c++
    int* nptr1 = 0;
    std::cout << *nptr1 << std::endl;  // Wrong! Read data by a "void*"
    
    int* nptr2 = nullptr;
    std::cout << *nptr2 << std::endl;  // Wrong!
    *nptr2 = 1;  // Wrong!
    
    // This will cause run time error or throw an exception when debugging because of "access violation".
    ```

### 4. Create an object on the stack or the heap

1. We can directly create an `object` on the `stack`:

    ```c++
    void Function()
    {
        int a = 1;
    }
    ```

    Note that for a `global variable` `int a = 1`, it will be created on the `static storage area`, not on the `stack`.

2. We can use `new` to create an `object` on the `heap`:

    ```c++
    char* buffer = new char[8];  // ask for 8-byte memory
    memset(buffer, 0, 8);  // set "value = 0" for 8-byte data
    delete[] buffer;
    ```

    Note that for a `global pointer variable` `int* a = new int`, the `pointer` `a` is on the `static storage area` while the pointed data is on the `heap`.

### 5. Double pointer, Triple pointer 

`Pointer` is also a `variable` and it's stored in the `memory`, so we can get `double pointer`, `triple pointer` ...

