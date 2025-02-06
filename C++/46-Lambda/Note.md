## 46. Lambda

**Knowledge Points**: `copy capture`, `mutable`

### 1. what is lambda

`lambda` is essentially a way to define something called `anonymous function`

### 2. when to use lambda

whenever we want to set  a `function pointer` to a `function`, we can set it to a `lambda`

1. `copy capture (pass by value)`:  

    ```c++
    void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
    // here we can't use "void(*func)(int)"
    {
        for (int value : values)
        	func(value);
    }
    
    
    int main()
    {
        std::vector<int> values = {5, 4, 3  2, 1};
        int a = 10;
        auto lambda = [=](int value) { std::cout << a << std::endl; };  // "=" means copy capture (passing by value), if we don't use "=" or "&" we can't access "a" in the "lambda"
        ForEach(values, lambda);
    }
    // outputs:
    // 10
    // 10
    // 10
    // 10
    // 10
    ```

2. key word `mutable`: 

    even though we are passing by `value`, we can't modify `a` unless we use `mutable`

    ```c++
    void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
    {
        for (int value : values)
        	func(value);
    }
    
    int main()
    {
        std::vector<int> values = {5, 4, 3, 2, 1};
        int a = 10;
        //auto lambda = [=](int value) { a = 5; std::cout << a << std::endl; }}  // Wrong!
        auto lambda = [=](int value) mutable { a = 5; std::cout << a << std::endl; }}
        ForEach(values, lambda);
    }
    // outputs:
    // 5
    // 5
    // 5
    // 5
    // 5
    ```

3. used in `std api`: 

    ```c++
    int main()
    {
        std::vector<int> values = {1, 4, 3, 2, 5};
        auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
        std::cout << *it << std::endl;  // 4
    }
    ```

    

