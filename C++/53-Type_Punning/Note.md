## 53. Type Punning

**Knowledge Points**: `type punning: cast to a different pointer`, `initialize another variable or manipulate the same memory`

### 1. what is type punning

`type punning` is a fancy term and it's a way to get around the type system in `C++`, we can treat this `memory` as a different type than it actually is, all we really need to do is just get that type as a `pointer` and then **cast** it to a different `pointer` and we can dereference it if we need to

### 2. some examples

1. **implicit conversion**: 

    check the memory addresses of `a` and `b`

    ```c++
    int main()
    {
        int a = 1;
        double b = a;
        std::cout << b << std::endl;  // 1
    }
    ```

2. **cast int to double**: 

    check the memory addresses of `a` and `b`

    ```c++
    int main()
    {
        int a = 1;
        double b = (double)a;
        std::cout << b << std::endl;  // 1
    }
    ```

3. **cast int* to double***: 

    ```c++
    int main()
    {
        int a = 1;
        double b = *(double*)&a;
        std::cout << b << std::endl;  // -9.25596e+61
    }
    ```

    if we want to `write`: 

    ```c++
    int main()
    {
        int a = 1;
        
        double b1 = *(double*)&a;
        b1 = 0.0;
        std::cout << b1 << std::endl;  // 0
        
        double& b2 = *(double*)&a;  // now we are manupulating the "same" memory
        b2 = 0.0;  // Wrong! runtime error
    }
    ```

4. **cast Entity* to other pointers**: 

    we have a custom `struct Entity`, which only has two `integers`: 

    ```c++
    struct Entity
    {
    	int x, y;
    }
    ```

    1. **cast Entity* to int***: 

        ```c++
        int main()
        {
            Entity e = { 5, 8 };
            int* position = (int*)&e;
            std::cout << position[0] << ", " << position[1] << std::endl;  // 5, 8
        }
        ```

    2. **cast Entity* to char*, float\***: 

        ```c++
        int main()
        {
            Entity e = { 5, 8 };
            int y1 = *(int*)((char*)&e + 4);
            std::cout << y1 << std::endl;  // 8
            int y2  = *(int*)((float*)&e + 1);
            std::cout << y2 << std::endl;  // 8
        }
        ```

    3. **a method returns the address of x**: 

        ```c++
        struct Entity
        {
            int x, y;
        
            int* GetPosition()
            {
            	return &x;
            }
        }
        
        int main()
        {
            Entity e = { 5, 8 };
        
            int* position = e.GetPosition();
            std::cout << position[0] << ", " << position[1] << std::endl;  // 5, 8
            position[0] = 123;
            std::cout << position[0] << ", " << position[1] << std::endl;  // 123, 8
            std::cout << e.x << ", " << e.y << std::endl;  // 123, 8
        }
        ```

