## 6. Conditional

**Knowedge Points**: `overhead of conditionals`, `else if`

1. **overhead**: 

    `if` statements and `branching` statements generally do carry a little bit **overhead** because we have to check condition and then **jump** to a different portion of the memory and start executing instructions

2. **check the assembly code when debugging**: 

    `Go To Disassembly` helps us check the assembly code in the `Debug` mode during debugging

3. **else if**: 

    ```c++
    if (a == 1)
    {
      // ...
    }
    else if (a == 2)
    {
      // ...
    }
    ```

    `else if` is not a key word , it's just a combination

    ```c++
    if (a == 1)
    {
      // ...
    }
    else
    {
      if (a == 2)
      {
         // ...
      }
    }
    
    ```

    