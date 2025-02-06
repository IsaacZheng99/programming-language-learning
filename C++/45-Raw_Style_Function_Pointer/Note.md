## 45. Raw-Style Function Pointer

**Knowledge Points**: `how to use function pointer: auto (implicit conversion), void(*ptrName)(), typedef,  using`, `function as a parameter`, `lambda`

#### 1. what is function pointer

1. `raw-style function pointer` comes from `C`
2. `function pointer` is just a way to assign a `function` to a `variable`

#### 2. how to use function pointer

here we have a `function`: 

```c++
void HelloWorld()
{
	std:cout << "Hello World!" << std::endl;
}
```

1. use `auto`:

    notice that don't assign the `return value`

    ```c++
    int main()
    {
    	auto function = HelloWorld();  // Wrong! here we are assigning the return value of the "HelloWorld" function to the "function" variable but the return type is "void" and we can't deduce "auto" type
    }
    ```

    ```c++
    int main()
    {
        auto function = HelloWorld;
        // this is same as "auto function = &HelloWorld" because there is an implicit conversion
        function();  // Hello World!
    }
    ```

    ```c++
    int main()
    {
        auto function = &HelloWorld;
        function();  // Hello World!
    }
    ```

2. use `void (*function)()`

    ```c++
    int main()
    {
        void (*function)();
        function = HelloWorld;
        function();  // Hello World!
    }
    ```

    ```c++
    int main()
    {
        void (*function)() = HelloWorld;
    	function();  // Hello World!
    }
    ```

    if the `function` has `parameters`: 

    ```c++
    void Function(const std::string& name, int age)
    {
        std::cout << "Name: " << name << "; Age: " << age << std::endl;
    }
    
    int main()
    {
        void(*function)(const std::string&, int) = Function;
        function("xiaoli", 1);  // Name: xiaoli; Age: 1
    }
    ```

3. use `typedef`: 

    ```c++
    int main()
    {
        typedef void (*HelloWorldFunction)();
        HelloWorldFunction function = HelloWorld;
        function();  // Hello World!
    }
    ```

    ```c++
    void Function(const std::string& name, int age)
    {
        std::cout << "Name: " << name << "; Age: " << age << std::endl;
    }
    
    int main()
    {
        typedef void(*FunctionPtr)(const std::string&, int);
        HelloWorldFunction function = Function;
        function("xiaoli", 1);  // Name: xiaoli; Age: 1
    }
    ```

4. use `using`: 

    ```c++
    int main()
    {
        using HelloWorldFunction = void (*)();
        HelloWorldFunction function = HelloWorld;
        function();  // Hello World!
    }
    ```

    ```c++
    void Function(const std::string& name, int age)
    {
        std::cout << "Name: " << name << "; Age: " << age << std::endl;
    }
    
    int main()
    {
        using FunctionPtr = void(*)(const std::string&, int)
        HelloWorldFunction function = Function;
        function("xiaoli", 1);  // Name: xiaoli; Age: 1
    }
    ```

#### 3. whye need function pointer

when we need a `function` parameter

```c++
void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int))
{
    for (int value : values)
    	func(value);
}

int main()
{
    std::vector<int> values = {5, 4, 3, 2, 1};
    ForEach(values, PrintValue);
}
// outputs:
// Value: 5
// Value: 4
// Value: 3
// Value: 2
// Value: 1
```

for a simple `function`, we can use `lambda` to implement it: 

```c++
void ForEach(const std::vector<int>& values, void(*func)(int))
{
  for (int value : values)
    func(value);
}

int main()
{
  std::vector<int> values = {5, 4, 3, 2, 1};
  // "[]" is called "captures", here we simply capture nothing
  ForEach(values, [](int value) { std::cout << "Value: " << value << std::endl; });
}
// outputs:
// Value: 5
// Value: 4
// Value: 3
// Value: 2
// Value: 1
```

