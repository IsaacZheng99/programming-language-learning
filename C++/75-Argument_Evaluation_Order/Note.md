## 75. Argument Evaluation Order

**Knowledge Points**: `argument evaluation order`, `rule for postfix-expression`

### 1. an example

```c++
void PrintSum(int a, int b)
{
    std::cout << a << " + " << b << " = " << (a + b) << std::endl;
}

int main()
{
    int value = 0;
    PrintSum(value++, value++);
}
// outputs: 
// 1 + 0 = 1

// run in "vs2022" with "C++20", this is actually an "undefined behaviour" and the result depends on the compiler and you are not supposed to do this

// before "C++17", you may see "0 + 0 = 0" because the compiler is actually allowed to work out what these are in parallel

// since "C++17", the "postfix-expression" is sequenced before each expression in the expression-list and any default argument, so we can get "1 + 0 = 1" or "0 + 1 = 1" because the order of these two is still not deterministic
```

