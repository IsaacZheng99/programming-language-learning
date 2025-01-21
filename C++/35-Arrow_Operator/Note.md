## 35. Arrow Operator

**Knowledge Points**: `operator->`, `operator-> used with pointer`, `overload operator->`, `use operator-> to get offset`

1. **operator-> used with pointer**: 

    ```c++
    class Entity
    {
    public:
    	void Print() const { std::cout << "Hello!" << std::endl; }
    };
    
    int main()
    {
        Entity e;
        e.Print();
      
        Entity* ptr = &e;
        (*ptr).Print();
        
        Entity& entity = *ptr;
        entity.Print();
      
    	ptr->Print();
    }
    ```

2. **overload operator->**: 

    1. **leverage the convenience of scoped pointer and operator-> at the same time**: 

        ```c++
        class Entity
        {
        public:
        	void Print() const { std::cout << "Hello!" << std::endl; }
        }
        
        class ScopedPtr
        {
        private:
        	Entity* m_Obj;
        public:
        	ScopedPtr(Entity* entity)
            	: m_Obj(entity)
            {
            }
          
            ~ScopedPtr()
            {
            	delete m_Obj;
            }
        
            Entity* GetObject()
            {
            	return m_Obj;
            }
        
            Entity* operator->()
            {
            	return m_Obj;
            }
        }
        
        int main()
        {
            ScopedPtr entity = new Entity();
            entity.GetObject()->Print();
            entity->Print();  // with the overloaded "operator->", we can simply write cleaner code like this
        }
        ```

    2. **const version of operator->**: 

        (try to comment the four `const` and check the results)

        ```c++
        class Entity
        {
        public:
        	void Print() const { std::cout << "Hello!" << std::endl; }
        }
        
        class ScopedPtr
        {
        private:
        	Entity* m_Obj;
        public:
        	ScopedPtr(Entity* entity)
            	: m_Obj(entity)
            {
            }
          
            ~ScopedPtr()
            {
            	delete m_Obj;
            }
        
            Entity* GetObject()
            {
            	return m_Obj;
            }
        
            Entity* operator->()
            {
            	return m_Obj;
            }
            
            const Entity* operator->() const
            {
            	return m_Obj;
            }
        }
        
        int main()
        {
            const ScopedPtr entity = new Entity();
            entity->Print();
        }
        ```

3. **use operator-> to get offset**: 

    use `operator->` to get offset of a certain `member variable` in memory: it's very useful when you are serializing data into a stream of bytes and you want to figure out offsets

    ```c++
    struct Vector3
    {
    	float x, y, z;
    }
    
    int main()
    {
        int offsetX = (int)&((Vector3*)nullptr)->x;
        // int offsetX = (int)&((Vector3*)0)->x;
        int offsetY = (int)&((Vector3*)nullptr)->y;
        int offsetZ = (int)&((Vector3*)nullptr)->y;
    
        std::cout << offsetX << std::endl;  // 0
        std::cout << offsetY << std::endl;  // 4
        std::cout << offsetZ << std::endl;  // 8
    }
    ```

    

    

    