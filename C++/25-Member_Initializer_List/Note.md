## 25. Member Initializer List

**Knowledge Points**: `initialization order when using member initializer list`,  `benefits of member initializer list`

1. **initialization order**: 

    no matter how you write your `member initializer list`, it will be initialized in the **order** that the actual class members are defined, if you break the order, there maybe some dependency problems so just make sure that you always initialize your `variables` in the same order that they're declared when you declare them as `members`

    ```c++
    class Entity1
    {
    public:
        int x, y;
        
        Entity1()
            : y(1), x(y) {}
    };
    
    class Entity2
    {
    public:
        int x, y;
        
        Entity2()
            : x(1), y(x) {}
    };
    
    int main()
    {
        Entity1 e1;
        std::cout << e1.x << ", " << e1.y << std::endl;  // -858993460, 1
        Entity2 e2;
        std::cout << e2.x << ", " << e2.y << std::endl;  // 1, 1
    }
    ```

2. **why need member initializer list:**

    1. **more readable and cleaner** 

    2. **better performance**:

        here we have an custom `class Example`: 

        ```c++
        class Example
        {
        public:
            Example()
            {
            	std::cout << "Created Example" << std::endl;
            }
        
            Example(int x)
            {
            	std::cout << "Created Example with " << x << std::endl;
            }
        };
        ```

        1. a `constructor` with no parameter: 

            ```c++
            class Entity
            {
            private:
                std::string m_Name;
                Example m_Example;
            public:
                Entity()
                {
            
                }
            };
            
            int main()
            {
                Entity e;
            }
            // output:
            // Created Example
            ```

        2. assign the `member variable` in the `constructor`: 

            ```c++
            class Entity
            {
            private:
                std::string m_Name;
                Example m_Example;  // when the "Entity e" is created, the "Example m_Example" is also created
            public:
                Entity()
                {
                	m_Example = Example(1);  // the second "Example" object is created
                    // in this case, it will also call the "move assignment operator"
                }
            }
            int main()
            {
                Entity e;
            }
            // output:
            // Created Example
            // Created Example with 1
            ```

        3. use `member initializer list`: 

            ```c++
            class Entity
            {
            private:
                std::string m_Name;
                Example m_Example;
            public:
                Entity()
                	: m_Example(Example(1))
                {
                }
            }
            
            int main()
            {
            	Entity e;
            }
            // output:
            // Created Example with 1
            ```

        4. just pass the parameter: 

            ```c++
            class Entity
            {
            private:
                std::string m_Name;
                Example m_Example;
            public:
                Entity()
                	: m_Example(1)
                {
                }
            }
            int main()
            {
            	Entity e;
            }
            // output:
            // Created Example with 1
            ```

        5. note that this applies to `non-primitive types` (e.g., `class Example`, `std::string` ...), for `primitive types` like `int`, it won't be initialized unless you initialize it by assigning it, but always use `member initializer list` whether the variable is of primitive type or not