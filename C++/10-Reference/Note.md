## 10. Reference

**Knowledge Points**:

1. `reference`
2. `pass by value, reference, pointer`
3. `when to use reference`
4. `how to use reference`

### 1. Reference

1. `Reference` is just **syntax suger** on top of `pointer`.
2. `Reference` is not a `variable` and it **doesn't** occupy any `memory`.

```c++
int a = 1;
int& ref = a;  // just an alias
```

### 2. Pass by value, reference, or pointer (address)

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

### 3. When to use reference

Whatever `reference` can do, `pointer` can also do and `pointer` is more powerful, but if you can use `reference` to solve the current problem, **just use it** because it can make the code simpler and cleaner.

### 4. How to use reference

1. When declare a reference, it should be **initialized**.

    ```c++
    int a = 1;
    int& ref = a;
    
    int& ref2; // Wrong! Compiling error: error C2530: 'ref2': references must be initialized
    ```

2. We **can't** change what a `reference` references, meaning what the `reference` references is always what the `reference` **initially** references.

    In the below code, we will get `a = 10` and  `b = 10` because we simply assign `b` to `a`.

    ```c++
    int a = 1;
    int b = 10;
    
    int& ref = a;
    ref = b;
    
    std::cout << a << std::endl;  // 10
    std::cout << b << std::endl;  // 10
    ```

