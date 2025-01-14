## 10. Reference

**Knowledge Points**: `reference`, `pass by value, reference, pointer`, `when and how to use reference`

1. **reference**: 

    1. `reference` is just **syntax suger** on top of `pointer`
    2. `reference` is not a variable and it **doesn't** occupy any memory

    ```c++
    int a = 1;
    int& ref = a;  // just an alias
    ```

2. **pass by value, by reference, by pointer (address)**: 

    ```c++
    void Increment1(int value)
    {
      value++;
    }
    
    void Increment2(int& value)
    {
      value++;
    }
    
    void Increment3(int* value)
    {
      (*value)++;
    }
    ```

3. **when to use reference**: 

    whatever `reference` can do, `pointer` can also do and `pointer` is more powerful, but if you can use `reference` to solve the current problem, **just use it** because it can make the code simpler and cleaner

4. **when declare a reference, it should be initialized**

    ```c++
    int a = 1;
    int& ref = a;
    
    int& ref2; // Wrong! This will cause compiling error.
    ```

5. **you can't change what a reference references, meaning what the reference references is always what the reference initially references **

    ```c++
    int a = 1;
    int b = 10;
    int& ref = a;
    ref = b; // We will get "a = 10", "b = 10" because we simply assign "b" to "a".
    ```

    