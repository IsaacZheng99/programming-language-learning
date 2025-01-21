## 32. Lifetime of Stack-based Object

**Knowledge Points**: `scope: empty scope, function scope, etc`, `how to leverage the property of stack-based object: scoped pointer, timer, mutex lock`

1. **what is scope**: 

    `function scope`, `if statement scope`, `loop scope`, `empty scope`, `class scope`

2. **create class object on the stack or heap**: 

    ```c++
    // create class object on the stack or heap
    class Entity
    {
    public:
        Entity()
        {
        	std::cout << "Created Entity!" << std::endl;
        }
    
        ~Entity()
        {
        	std::cout << "Destroyed Entity!" << std::endl;
        }
    };
    
    int main()
    {
        {
            Entity e1;
            Entity* e2 = new Entity();
            delete e2;
        }
    }
    ```

3. **function scope**: 

    1. **pointer to a local variable**: 

        ```c++
        int* CreateArray()
        {
            int array[50];
            return array;  // Warning!
        }
        
        int main()
        {
        	int* a = CreateArray();  // Warning! create a "stack-based variable" and try to return a pointer to it, but once the function ends, the variable goes done
        }
        ```

    2. **create on the heap**: 

        ```c++
        int* CreateArray()
        {
            int array = new int[50];
        	return array;
        }
        
        int main()
        {
        	int* a = CreateArray();
        }
        ```

    3. **define the variable outside the function scope**

        ```c++
        void CreateArray(int* array)
        {
        	// fill the array
        }
        
        int main()
        {
            int array[50];
            CreateArray(array);
        }
        ```

4. **how to leverage the property of stack-based object**: 

    1. **scoped pointer**: 

        ```c++
        class Entity
        {
        public:
            Entity()
            {
            	std::cout << "Created Entity!" << std::endl;
            }
        
            ~Entity()
            {
            	std::cout << "Destroyed Entity!" << std::endl;
            }
        };
        
        class ScopedPtr
        {
        private:
        	Entity* m_Ptr;
        public:
            ScopedPtr(Entity* ptr)
            	: m_Ptr(ptr) {}
        
            ~ScopedPtr()
            {
            	delete m_Ptr;
            }
        }
        
        int main()
        {
            {
                // in this case, the "e" object is created on the stack and once it gets out of the scope, it will call the destructor and delete the "Entity*" pointer
                ScopedPtr e = new Entity();  // implicit conversion
                // Entity* e = new Entity();  // almost the same format and we don't need to call the "delete" manually
            }
        }
        ```

    2. `timer` object created on `stack` for automatic timing

    3. `mutex lock` created on `stack` in a function