## 1. WorkFlow

**Knowledge Points**:

1. `pre process`: `.i`

2. `compile`: `.asm files; .obj files`

3. `link`: `.exe files; repeated definition problem: static, inline, move the definition of the function`

### 1. Pre-process

1. `Pre-process` happens before `compile`.

2. Anything after `#` is `pre-process` statement.

    ```c++
    #include
    #define
    #if  #endif
    #ifdef
    #pragma
    ```

### 2. Debug mode and Release mode

Debug` mode` is **slower** than `Release` mode because many **optimizations** are **shut off** but `Debug` mode can help us debug code, but we can also change the configuration to do optimizations in the `Ddebug` mode.

### 3. Compile

Here, `compile` is a kind of **broadly speaking**, representing the process that the `.cpp` files become the `.obj` files.

1. Before `compile`, there is the `pre-process` stage, where the complier simply "**replace**" (copy, delete, etc.) code.
    1. For example, the `pre-process` statement `#include <iostream` is to take all the contents of the `iostream` file and **copy** them, then **paste** them to the current file.

    2. `.i` file: in `visual studio`, set the `Preprocess to a File` as `Yes` and we can get the `.i` file, which is the pre-processed `c++` code.

2. After `pre-process`, the compiler will generate an `abstract syntax tree (AST)` to represent the code, then it will generate the machine code. The whole process is `compile`.
    1. `.asm` file: in visual studio, set the `Assemble Output` as `Assemble-Only Listing` and we can get the `.asm` file, which is the readable assembly code. We can call this process as **narrowly speaking** `compile`.
    2. `Translation unit`: somtimes, one `.cpp` file may contain other `.cpp` files and become **one** big `.cpp` file and in this case we `complie` this big `.cpp` file, we get one translation unit and one `.obj` file, so one `.cpp` file doesn't need to be one `translation unit`.
    3. `.obj` file: in the `assembly` state, the `.asm` files will become `.obj` files, which are `binary` files and contain the machine code.

### 4. Link

In the `link` process, we `link` the `.obj` files and get `.exe` file.

1. If we check the `.asm` file, we will see some random characters to represent functions and they are indeed the **signatures** of these functions, which is used to find functions in the `link` process.

2. Typically, we may get into **repeated definition** problems like this:

    ```c++
    // Log.h
    #pragma
    void Log(const char* message)
    {
        std::cout << message << std::endl;
    }
    
    // Log.cpp
    #include <iostream>
    #include "Log.h"
    void InitLog()
    {
        Log("Initialized Log!");
    }
    
    // Main.cpp
    #include <iostream>
    #include "Log.h"
    static int Multiply(int a, int b)
    {
        Log("Multiply");
        return a * b;
    }
    
    int main()
    {
        std::cout << Multiply(5, 8) << std::endl;
    }
    
    // fatal error LNK1169: one or more multiply defined symbols found
    ```

    We have three ways to solve the **repeated definition** problem:

    1. The `static` key word:

        1. The `link` process of this function should only be internal.
        2. The scene will be that there are different functions in different files, which only have the same code but are not the same functions.

    2. The `inline` key word: `inline` will directly **replace** the call of function with the `function` body.

    3. Move the `definition` of the `function` to other file and just use the definition once. 

        1. The above problem is essentially because we put the `Log()` function in two `translation units`, we can simply remain the `declaration` and move the `definition` to the `Log.cpp` file.
        2. Therefore, we always seperate the `declaration` and the `definition`, e.g., we can put the `declaration` in the `.h` files and the `definition` in the `.cpp` files.

        ```c++
        // Log.h
        #pragma
        void Log(const char* message);
        
        // Log.cpp
        #include <iostream>
        #include "Log.h"
        void Log(const char* message)
        {
            std::cout << message << std::endl;
        }
        
        void InitLog()
        {
            Log("Initialized Log!");
        }
        
        // Main.cpp
        #include <iostream>
        #include "Log.h"
        static int Multiply(int a, int b)
        {
            Log("Multiply");
            return a * b;
        }
        
        int main()
        {
            std::cout << Multiply(5, 8) << std::endl;
        }
        ```

