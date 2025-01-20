## 29. Implicit

1. **one implicit conversion**: 

    what `C++` is allowed to d o what the `compiler` is allowed to do is perform **one** `implicit conversion` on your code

    1. **implicit construction**: 

        ```c++
        // version 1:
        class Entity
        {
        private:
            std::string m_Name;
            int m_Age;
        public:
            Entity(const std::string& name)
            	: m_Name(name), m_Age(-1) {}
            Entity(int age)
            	: m_Name("Unknown"), m_Age(age) {}
        };
        
        int main()
        {
            Entity e1 = (std::string)"xiaoli";
            Entity e2 = Entity("xiaoli");
            Entity e3 = Entity(25);
            Entity e4 = 25；  // implicit conversion from "int" to "Entity"
        }
        ```

        ```c++
        class Entity
        {
        private:
            std::string m_Name;
            int m_Age;
        public:
            Entity(const std::string& name)
            	: m_Name(name), m_Age(-1) {}
           
            Entity(int age)
            	: m_Name("Unknown"), m_Age(age) {}
        };
        
        void Function(const Entity& e)
        {
          
        }
        
        int main()
        {
            Function((std::string)"xiaoli");
            Function(25);
        }
        ```

    2. **arithmetic conversion**

        ensure that the compatibility of types of operands of `arithmetic operators (+, -, *, /)`

        1. **integral promotion**: 

            ```c++
            int main()
            {
                char c = 10;
                int i = 20;
               	int result = c + i;
                std::cout << result << std::endl;  // 30
                std::cout << typeid(result).name << std::endl;  // int
                std::cout << c + i << std::endl;  // 30
                std::cout << typeid(c + i).name << std::endl;  // int
            }
            ```

    3. **assignment conversion**: 

    4. **type conversion operator**: 

        ```c++
        class MyClass
        {
        private:
            int m_Value;
        public:
            MyClass()
                : m_Value(1) {}
            
            operator int() const
            {
                return m_Value;
            }
        };
        
        int main()
        {
            MyClass obj;
            int a = obj;
            std::cout << a << std::endl;
        }
        ```

    5. Arithmic

2. **explicit**: 

    if you write `explicit` in front of a `constructor`, it means that no `implicit conversions` for it and this `constructor` must be explicitly called

    ```c++
    class Entity
    {
    private:
        std::string m_Name;
        int m_Age;
    public:
        Entity(const std::string& name)
        	: m_Name(name), m_Age(-1) {}
        
        explicit Entity(int age)
        	: m_Name("Unknown"), m_Age(age) {}
    };
    
    int main()
    {
      Entity e1 = 25;  // Wrong!
      Entity e2 = (Entity)25;  // explicitly cast "int" to "Entity"
      Entity e3 = Entity(25);
      Entity e4(25);
    }
    ```

    