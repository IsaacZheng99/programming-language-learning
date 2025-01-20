## 24. Mutable

**Knowledge Points**: `mutable with const in methods`, `mutable with lambda`

1. **mutable works with const in methods**: 

    if we really want some `member variables` to change in a `const method` (e.g., when you are debugging and you want to check how many times a `method` has been called), we need to use `mutable`

    1. **non-const object**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
        public:
            Entity()
                : m_Name("Entity") {}
            
        	const std::string& m_Name()
        	{
            	return m_Name;
        	}
        };
        
        int main()
        {
        	Entity e;
        	std::cout << e.GetName() << std::endl;  // Entity
        }
        ```

    2. **const object with non-const method**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
        public:
            Entity()
                : m_Name("Entity") {}
            
        	const std::string& m_Name()
        	{
            	return m_Name;
        	}
        };
        
        int main()
        {
        	const Entity e;
        	std::cout << e.GetName() << std::endl;  // Wrong!
        }
        ```

    3. **const object with const method**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
        public:
            Entity()
                : m_Name("Entity") {}
            
        	const std::string& m_Name() const
        	{
            	return m_Name;
        	}
        };
        
        int main()
        {
        	const Entity e;
        	std::cout << e.GetName() << std::endl;  // Entity
        }
        ```

    4. **change a member variable in a const method**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
            int m_DebugCount;  // We want to check how many times a method has been called.
        public:
            Entity()
                : m_Name("Entity"), m_DebugCount(0) {}
            
        	const std::string& m_Name() const
        	{
                m_DebugCount++;  // Wrong!
            	return m_Name;
        	}
        };
        ```

    5. **add mutable to allow change**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
        	mutable int m_DebugCount;  // here "mutable" allows "m_DebugCount" to change in the const methods
        public:
            Entity()
                : m_Name("Entity"), m_DebugCount(0) {}
            
        	const std::string& m_Name() const
        	{
            	m_DebugCount++;
            	return m_Name;
        	}
        };
        
        int main()
        {
        	const Entity e;
        	e.GetName();
        }
        ```

    6. **const object must be initialized**: 

        ```c++
        class Entity
        {
        private:
        	const std::string& m_Name;
        	mutable int m_DebugCount;
        public:
            //Entity()  // remove the constructor
            //    : m_Name("Entity"), m_DebugCount(0) {}
            
        	const std::string& m_Name() const
        	{
            	m_DebugCount++;
            	return m_Name;
        	}
        };
        
        int main()
        {
        	const Entity e;  // Wrong!
        	e.GetName();
        }
        ```

2. **mutable works with lambda**: 

    ```c++
    int main()
    {
        int x = 0;
        auto f = [=]() mutable  // if there is no mutable, we can't modify "x" in this lambda
        {
            x++; // here it is equivalent to y = x and y++
            std::cout << x << std::endl;
        };
      	f();  // 1
        std::cout << x << endl;  // 0
    }
    ```

    

    