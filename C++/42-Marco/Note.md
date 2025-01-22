## 42. Marco

**Knowledge Points**: `examples of marco: replace a whole statement, send parameters, delete codes, make a whole function`

### 1. pre-process

`pre-process` stage is basically a **text-editing** stage

### 2. examples of marco

1. **replace a whole statement**

    ```c++
    #define WAIT std::cin.get()  // here we don't add ";" at the end, which makes it more readable when we use the marco in the code
    // but don't do this in a production environment because if this "marco" is defined in another file, it can't be readable
    
    int main()
    {
        WAIT;
    }
    ```

    ```c++
    #define WAIT std::cin.get()
    
    #define OPEN_CURLY {
    
    int main()
    OPEN_CURLY
        WAIT;
    }
    ```

2. **send parameters**: 

    1. first set `Prepeocessor Definitions`: add `MY_DEBUG`

    2. `#ifdef MY_DEBUG` and set some `marcos`

        ```c++
        #ifdef MY_DEBUG
        #define LOG(x) std::cout << x << std::endl  // send parameter "x"
        #else
        #define LOG(x)
        #endif
        
        int main()
        {
            LOG("Hello!");  // Hello!
            std::cin.get();
        }
        ```

    3. better to use `#if MY_DEBUG == 1` and in this case we can set `Prepeocessor Definitions`: add `MY_DEBUG=1`

        ```c++
        #if MY_DEBUG == 1  // this is better because we can change the value of "MY_DEBUG" rather than comment out it and this is more readable
        #define LOG(x) std::cout << x << std::endl
        #else
        #define LOG(x)
        #endif
        
        int main()
        {
            LOG("Hello!");  // Hello!
            std::cin.get();
        }
        ```

        we can also manually set the value: 

        ```c++
        #define MY_DEBUG 0
        
        #if MY_DEBUG == 1  // this is better because we can change the value of "MY_DEBUG" rather than comment out it
        #define LOG(x) std::cout << x << std::endl
        #else
        #define LOG(x)
        #endif
        
        int main()
        {
            LOG("Hello!");  // there will be no printing
            std::cin.get();
        }
        ```

    4. better to add another `marco` which is used in the `Release` mode:

        set `Prepeocessor Definitions`: add `MY_RELEASE`

        ```c++
        #if MY_DEBUG == 1
        #define LOG(x) std::cout << x << std::endl
        ##elif defined(MY_RELEASE)
        #define LOG(x)
        #endif
        
        int main()
        {
            LOG("Hello!");
            std::cin.get();
        }
        ```

3. **delete codes**: 

    ```c++
    #if 0
    
    #if MY_DEBUG == 1
    #define LOG(x) std::cout << x << std::endl
    #elif defined(MY_RELEASE)
    #define LOG(x)
    #endif
    
    #endif
    
    int main()
    {
      LOG("Hello!");  // Wrong! identifier not found
      std::cin.get();
    }
    ```

4. **make a whole function**: 

    ```c++
    // use "\", which is the "new line character" to make a whole function as a "marco"
    #define MAIN int main()\
    {\
    	std::cout << "Hello!" << std::endl;\
    	std::cin.get();\
    }
    
    MAIN
    ```

