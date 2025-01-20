## 29. Implicit

**Knowledge Points**:`implicit conversion`,  `one implicit conversion`, `implicit construction`, `arithmetic conversion: float priority, larger-ranged number priority, bool conversion`, `assignment conversion`, `type conversion operator`

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
                char c1 = 10;
            	int i1 = 20;
            	int result1 = c1 + i1;
            	std::cout << c1 + i1 << std::endl;  // 30
            	std::cout << typeid(c1 + i1).name() << std::endl;  // int
            	std::cout << result1 << std::endl;  // 30
            	std::cout << typeid(result1).name() << std::endl;  // int
            }
            ```

        2. **usual arithmetic conversion**: 

            1. **float priority**: 

                ```c++
                int main()
                {
                    int i2 = 12;
                	float f1 = 1.1f;
                	std::cout << i2 + f1 << std::endl;  // 13.1
                	std::cout << typeid(i2 + f1).name() << std::endl;  // float
                	std::cout << i2 / f1 << std::endl;  // 10.9091
                	std::cout << typeid(i2 / f1).name() << std::endl;  // float
                	std::cout << i2 / i1 << std::endl;  // 0
                	std::cout << typeid(i2 / i1).name() << std::endl;  // int
                	std::cout << i1 / i2 << std::endl;  // 1
                	std::cout << typeid(i1 / i2).name() << std::endl;  // int
                	int i3 = 120;
                	std::cout << i3 / i2 << std::endl;  // 10
                	std::cout << typeid(i3 / i2).name() << std::endl;  // int
                	double d1 = 2.2;
                	std::cout << i2 + d1 << std::endl;  // 14.2
                	std::cout << typeid(i2 + d1).name() << std::endl;  // double
                	std::cout << f1 + d1 << std::endl;  // 3.3
                	std::cout << typeid(f1 + d1).name() << std::endl;  // double
                }
                ```

            2. **larger-ranged number priority**: 

                ```c++
                int main()
                {
                    int i4 = 1;
                	long l1 = 10;
                	std::cout << i4 + l1 << std::endl;  // 11
                	std::cout << typeid(i4 + l1).name() << std::endl;  // long
                	unsigned int ui1 = 100;
                	std::cout << i4 + ui1 << std::endl;  // 101
                	std::cout << typeid(i4 + ui1).name() << std::endl;  // unsigned int
                }
                ```

            3. **bool conversion**: 

                ```c++
                int main()
                {
                    bool b1 = true;
                	bool b2 = false;
                	int i5 = 99;
                	std::cout << i5 + b1 << std::endl;  // 100
                	std::cout << typeid(i5 + b1).name() << std::endl;  // int
                	std::cout << i5 + b2 << std::endl;  // 99
                	std::cout << typeid(i5 + b2).name() << std::endl;  // int
                }
                ```

        3. **floating-point promotion**: 

            ```c++
            int main()
            {
                float f2 = 3.3f;
            	double d2 = 4.4;
            	std::cout << f2 + d2 << std::endl;  // 7.7
            	std::cout << typeid(f2 + d2).name() << std::endl;
            }
            ```

    3. **assignment conversion**: 

        ```c++
        int main()
        {
            float f3 = 1.1f;
        	double d3 = f3;
        	char c2 = 1;
        	int i6 = c2;
        	char c3 = i6;
        }
        ```

    4. **type conversion operator**: 

        ```c++
        class MyClass
        {
        private:
        	int m_Value;
        public:
        	MyClass()
        		: m_Value(1) {
        	}
        
        	operator int() const
        	{
        		return m_Value;
        	}
        };
        
        int main()
        {
            MyClass obj;
        	int a = obj;
        	std::cout << a << std::endl;  // 1
        }
        ```

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


