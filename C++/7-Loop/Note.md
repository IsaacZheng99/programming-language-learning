## 7. Loop

**Knowledge Points**: `for`, `while`, `do while`

1. **for**: 

    ```c++
    for (int i = 0; i < 10; i++)
    {
      // ...
    }
    // initialization expression: "int i = 0" is executed only once at the beginning of the loop
    // condition expression: "i < 10" is evaluated before the next iteration
    // iteration expression: "i++" is executed at the end of each iteration
    ```

2. **while**: 

    ```c++
    int i = 0;
    while (i < 10)
    {
      // ...
      i++;
    }
    ```

3. **do while**: 

    ```c++
    do
    {
      // ...
      i++; 
    } while (i < 10);
    ```

4. **other ways to write a for loop**: 

    ```c++
    int i = 0;
    bool condition = true;
    for (; condition; )
    {
      if (!(i < 10))
        condition = false
      // ...
      i++;
    }
    ```

