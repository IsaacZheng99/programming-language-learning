## 14. Constructor

**Knowledge Points**: `constructor`, `non-parameter constructor`, `constructor with parameter`, `default constructor`, `if you don't want people create instances`

1. **what is constructor**: 

    a `constructor` is basically a special type of `method`, which runs every time we instantiate an object

2. **instantiate a class to get an object**: 

    when we instantiated `class Entity` and allocated memory for it, we **didn't** actually initialize that memory, meaning we got **whatever was left over** in that memory space (note that in `Debug` mode, the memory will be set as `0xcccccccc`)

    ```c++
    class Entity
    {
    public:
        float x, y;
      
        void Print()
        {
            std::cout << x << ", " << y << std::endl;
        }
    };
    
    int main()
    {
        Entity e;
        e.Print();  // -1.07374e+08, -1.07374e+08
    }
    ```

    in general, it's not safe to use memory that has not been `initialized` (note that the case below depends on the compiler and I've tried `gcc 13.2.0` and it won't have error here): 

    ```c++
    int main()
    {
        Entity e;
        std::cout << e.x << e.y << std::endl;  // error C4700: uninitialized local variable 'e' used
        // here we are trying to use memory that has not been initialized
    }
    ```

    if you call a `method` of `Entity` first, and then access `e.x`, it will work well with `MSVC`: 

    ```c++
    class Entity
    {
    public:
        float x, y;
      
        void Hello() {}
    };
    
    int main()
    {
        Entity e;
        e.Hello();
        std::cout << e.x << e.y << std::endl;  // -1.07374e+08, -1.07374e+08
    }
    ```

3. **how about calling a Init() function**: 

    maybe we can also create a function called `void Init()` to handle some initializing issues and call it manually **every time** we instantiate an object, but this will make the code not clean

    ```c++
    class EntityWithInit
    {
    public:
        float x, y;
      
        void Init()
        {
            x = 0.0f;
            y = 0.0f;
        }
    };
    
    int main()
    {
        EntityWithInit e;
        e.Init();
        std::cout << e.x << e.y << std::endl;  // 0, 0
    }
    ```

4. **constructor**: 

    1. **non-parameter constructor and constructor with parameters**: 

        ```c++
        class Entity
        {
        public:
            float x, y;
          
            // a constructor without parameters
            Entity()  // no return type and same name with the class
            {
                x = 0.0f;
                y = 0.0f;
            }
          
            // a constructor with parameters
            // overload: different versions of the "same" methods ("same" means the methods' names are the same) with different parameters
            Entity(float x1, float y1)
            {
                x = x1;
                y = y1;
            }
          
            void Print()
            {
                std::cout << x << ", " << y << std::endl;
            }
        };
        
        int main()
        {
            Entity e(10.0f, 5.0f);
            e.Print();  // 10, 5
        }
        ```

    2. **default constructor**: 

        if we don't specify a `constructor`, we still have a `constructor` which is called `default constructor` and it does nothing, just like `Entity() {}`

    3. **when does a constructor run**: 

        `constructor` will not run if we do not instantiate an object, so if we just use a static method from a class, it won't run

    4. **if you don't want people create instances**: 

        1. **make the constructor private**: 

            ```c++
            class Log
            {
            private:
              Log() {}
            public:
              static void Write() {}
            };
            
            int main()
            {
              Log::Write();
            }
            ```

        2. **delete the constructor**: 

            ```c++
            class Log
            {
            public:
              Log() = delete;
              
              static void Write() {}
            };
            
            int main()
            {
              Log::Write();
            }
            ```

