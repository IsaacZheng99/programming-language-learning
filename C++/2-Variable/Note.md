## 2. Variable

**Knowledge Points**:

1. `store variables: stack, heap`
2. `only difference of variables in C++: size of variables`
3. `comparison between char and short`
4. `comparison between float and double`
5. `bool`
6. `sizeof()`
7. `*, &`

### 1. Store variables

`Variables` are stored in the `memory`, either in the `stack` or `heap`.

### 2. Difference of variables in C++

1. The **only** difference of `variables` in `C++` is **size**, i.e., how much the `memory` does the `variable` occupy, i.e., how much memory will be allocated when we create a `variable`.

2. The size of different primitive `integer` types:

    ```c++
    char       // 1 byte
    short      // 2 bytes
    int        // 4 bytes
    long       // 4 or 8 bytes, depending on the compiler and the platform
    long long  // 8 bytes
      
    unsigned int  // 4 bytes
    ...
    ```

### 3. char and short

We can get different outputs based on the `operator overloading` of `operator<<()`

```c++
char a0 = 'A'
char a1 = 65
std::cout << a0 << std::endl;  // A
std::cout << a1 << std::endl;  // A

short a2 = 'A'
short a3 = 65
std::cout << a2 << std::endl;  // 65
std::cout << a3 << std::endl;  // 65
```

### 4. float and double

When we use `float`, it's better to add `f` or `F` at the end because: 

1. more readable;
2. less overhead (`type conversion` costs);
3. safer (`type conversion` may bring problems like **accuracy loss**, in the below case there is no accuracy loss because `5.5` is in the scope of `float`);
4. avoid cross-platform problem (in different platforms, the way of `type conversion` may differ).

```c++
float f0 = 5.5f;
float f1 = 5.5F;
double d = 5.5;
```

### 5. bool

1. `0` means `false` and anything except `0` means `true`.
2. The `bool` `variable` does take `1` bit to represent, however when addressing memory, we can't address `1` bit, so we can't simply create a `1-bit` `variable`. (One advanced fun trick is to use `1 byte` to store 8 `bool` `variables`.)

```c++
bool var = true;
std::cout << var << std::endl;  // 1
bool a = 123;
std::cout << a << std::endl;  // 1
bool b = 0;
std::cout << b << std::endl;  // 0
bool c = -1;
std::cout << c << std::endl;  // 1
```

### 6. sizeof()

`sizeof()` is an `operator` in `C++`, and it will be replaced with constant result during `compile` and doesn't cause runtime overhead.

```c++
std::cout << sizeof(bool) << std::endl;  // 1
std::cout << sizeof bool << std::endl;  // 1, no brackets is also fine
std::cout << sizeof(int) << std::endl;  // 4
std::cout << sizeof(double) << std::endl;  // 8

int a = 1;
std::cout << sizeof(a) << std::endl;  // 4
```

### 7. *, &

```c++
int* a = 1;  // asterisk
int& b = 2;  // ampersand
```

