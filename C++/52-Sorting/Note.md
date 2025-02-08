## 52. Sorting

**Knowledge Points**: `std::sort()`, `predicate`, `comparator`, `how to keep the original order`

### 1. std::sort()

`std::sort()` performs `sorting` for you of any kind of `iterator` by using `operator<` (by default) and the `complexity` is `nlog(n)`

### 2. some examples

1. **ascending order by default**: 

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end());
    
        for (int value : values)
        	std::cout << value << std::endl;  // 12345
    }
    ```

2. **descending order**: 

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end(), std::greater<int>());
    
        for (int value : values)
        	std::cout << value << std::endl;  // 54321
    }
    ```

3. **ascedning order by lambda**: 

    if the `predicate` returns **true**, then `a` will be ordered before `b`

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end(), [](int a, int b) { return a < b; });
    
        for (int value : values)
        	std::cout << value << std::endl;  // 12345
    }
    ```

4. **descending order by lambda**: 

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end(), [](int a, int b) { return a > b; });
    
        for (int value : values)
        	std::cout << value << std::endl;  // 54321
    }
    ```

5. **if we want to put 1 at the last place**

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end(), [](int a, int b) { return a > 1; });
    
        for (int value : values)
        	std::cout << value << std::endl;  // Wrong! runtime error
    }
    ```

    we can't simply use `return a > 1` because it's an `invalid comparator`

    ```c++
    int main()
    {
        std::vector<int> values = { 3, 5, 1, 4, 2 };
        std::sort(values.begin(), values.end(), [](int a, int b) 
        {
            if (a == 1)
    			return false;
            if (b == 1)
    			return true;
            return false;  // keep the original order 
        });
    
        for (int value : values)
        	std::cout << value << std::endl;  // 35421
    }
    ```

