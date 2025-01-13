## 1. WorkFlow

**Knowledge Points**: `pre process`, `compile`, `link`

1. `pre-process` happens before `compile`

2. anything after `#` is `pre-process` statement

3. `Debug` mode is **slower** than `Release` mode because many **optimizations** are shut off but `Debug` mode can help us debug code (we can also change the configuration to do optimizations in the `Ddebug` mode)

4. `compile`: `.cpp` files become `.obj` files

    1. in the `pre-process` stage, the complier simply "**replace**" (copy, delete, etc.) code

        ```c++
        #include <iostream>  // take all the contents of the "iostream" file and copy them, then paste them to the current file
        ```

        ```c++
        #include
        #define
        #if  #endif
        #ifdef
        #pragma
        ```

    2. after `pre-process`, the compiler will generate an `abstract syntax tree (AST)` to represent the code, then it will generate the machine code

    3. `.i` file: in `visual studio`, set the `Preprocess to a File` as `Yes` and we can get the `.i` file, which is the pre-processed `c++` code

    4. `.asm` file: in visual studio, set the `Assemble Output` as `Assemble-Only Listing` and we can get the `.asm` file, which is the readable assembly code

    5. `translation unit`: somtimes, one `.cpp` file may contain other `.cpp` files and become **one** big `.cpp` file and in this case you complie this big `.cpp` file, you get one translation unit and one `.obj` file, so one `.cpp` file doesn't need to be one translation unit

    6. `.obj` file: it's a `binary` file and contains the machine code

5. `link`: link `.obj` files and get `.exe` file

    1. if we check the `.asm` file, we will see some random characters to represent functions and they are indeed the **signatures** of these functions, which is used to find functions in the `linking` process
    2. three ways to solve the **repeated definition** problem
        1. `static` key word: in different files, there are different functions, which only have the same code but are not the same functions
        2. `inline` key word: `inline` will directly **replace** the call of function with the function body
        3. move the definition of the function to other file and just use the definition once