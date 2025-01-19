## 23. Const

**Knowledge Points**: `const`, `pointer to const`, `const pointer`, `const in a method or a function`, `reference to const`

1. **what const can do**: 

    1. `const` **promises** something is not going to change and can simplify our code a lot

    2. maybe we can call `const` as **fake** key word, because it can't do much in the scope of changes to the generated code, it's like `visibility` for `class` and `struct` 

        ```c++
        int main()
        {
            const int MAX_AGE = 100;
        	std::cout << MAX_AGE << std::endl;  // 100
            
            int* a = new int;  // created on heap
            *a = 1;
            std::cout << *a << std::endl;  // 1
            
            // one way to break the promise of "const"
            a = (int*)&MAX_AGE;
            std::cout << *a << std::endl;  // 100
            *a = 10;
            std::cout << *a << std::endl;  // 10
            std::cout << MAX_AGE << std::endl;  // 100  here you should check the assembly code and you will see that the compiler simply outputs 100, not addresses the memory of "MAX_AGE"
            std::cout << a << std::endl;  // 0x00CFFB50
            std::cout << &MAX_AGE << std::endl;  // 0x00CFFB50
        }
        ```

2. **const and pointer**: 

    1. **指针常量 pointer to const**: `const int*` or `int const*` (the key here is the order of `const` and  `asterisk`, i.e., the `pointer` sign) 

        **const int***: 

        ```c++
        int main()
        {
            const int* a = new int;
            *a = 1;  // Wrong! you can't modify the contents of that pointer (i.e., something the pointer points)
            int b = 2;
            a = &b;  // you can change the pointer "a"
        }
        ```

        **int const***: 

        ```c++
        int main()
        {
            int const* a = new int;
            *a = 1;  // Wrong!
            int b = 2;
            a = &b;
        }
        ```

    2. **const pointer 常量指针**: 

        **int* const**: 

        ```c++
        int main()
        {
            int* const a = new int;
            *a = 1;
            int b = 2;
            a = &b;  // Wrong!
        }
        ```

    3. **const int* const** or **int const* const**: neither can be changed

3. **const in a method or a function**: 

    1. **const in both method and function**: 

        ```c++
        class Entity
        {
        private:
        	int m_X, m_Y;
        public:
        	int GetX() const  // // here "const" means this method won't modify any of the class
            {
            	return m_X;
            }
        }
        
        void PrintEntity(const Entity& e)
        {
        	e = Entity();  // Wrong! for const reference, you can't modify the reference
        	// Note that C++ programmers tend to abbreviate the phrase “reference to const” as “const reference”. This abbreviation makes sense—if you remember that it is an abbreviation.
        	// there is no so-called const reference, the reference is just the content, if it's const, you simply can't modify it because it's const
        	std::cout << e.GetX() << std::endl;
        }
        ```

    2. **remove the const in the method**: 

        ```c++
        class Entity
        {
        private:
        	int m_X, m_Y;
        public:
            int GetX()  // remove the const
            {
            	return m_X;
            }
        }
        
        void PrintEntity(const Entity& e)
        {
        	std::cout << e.GetX() << std::endl;  // Wrong! here we remove "const" from "GetX()" function and this function can't gurantee that it won't modify the Entity object but the paramter "const Entity& e" promise it's const
        }
        ```

    3. **overload by const**: 

        ```c++
        class Entity
        {
        private:
        	int m_X, m_Y;
        public:
            int GetX() const
            {
                std::cout << "GetX() with const" << std::endl;
            	return m_X;
            }
        
            int GetX()
            {
                std::cout << "GetX() without const" << std::endl;
            	return m_X;
            }
        }
        
        void PrintEntity(const Entity& e)
        {
        	std::cout << e.GetX() << std::endl;
        }
        
        void PrintEntity(Entity& e)
        {
        	std::cout << e.GetX() << std::endl;
        }
        
        int main()
        {
            Entity e1;
            PrintEntity(e1);
            const Entity e2 = e1;
            PrintEntity(e2);
        }
        // output:
        // GetX() without const
        // -858993460
        // GetX() with const
        // -858993460
        ```

