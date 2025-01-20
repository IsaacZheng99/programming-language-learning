## 27. Create Object

**Knowledge Points**: `memory cost of an object`, `lifespan of stack-based object`, `lifespan of heap-based object`

1. **how much memory an object costs**: 

    even if we instantiate a `class` without any members, it will cost at least `1-byte memory`

2. **when memory is freed**: 

    ```c++
    using String = std::string;
    
    class Entity
    {
    private:
    	String m_Name;
    public:
        Entity() : m_Name("Unknown") {}
        
        Entity(const String& name) : m_Name(name) {}
    
        const String& GetName() const { return m_Name; }
    };
    ```

    1. **stack-based object**: 

        `stack` objects have an automatic lifespan and their life time is actually controled by the scope that they are declared in, as soon as that `variable` goes out of the scope, the memory is free because when that scope ends, the `stack` pops and anything in that `stack frame` gets freed

        ```c++
        int main()
        {
            // create object on stack
            // this the fastest and most managed way in "c++" to instantiate objects, do this whenever you can do in this way
            Entity entity1;  // not like "c#" or "Java", there is no problem like null pointer problem, here the non-parameter constructor will be called
            std::cout << entity1.GetName() << std::endl;  // Unknown
            Entity entity2 = Entity();
            std::cout << entity2.GetName() << std::endl;  // Unknown
            Entity entity3("xiaoli");
            std::cout << entity3.GetName() << std::endl;  // xiaoli
            Entity entity4 = Entity("xiaoli");
            std::cout << entity4.GetName() << std::endl;  // xiaoli
        
            Entity* e1;
            {
                Entity entity5("xiaoli");
                e1 = &entity5;
            	std::cout << e1->GetName() << std::endl;  // We will see "m_Name=""".
            }  // once the program runs out of the scope, the "entity5" object will be destryed and the address which the pointer points will not have normal data
            std::cout << e1->GetName() << std::endl;  // We will see "m_Name=""".
        }
        ```

    2. **heap-based object**: 

        `heap` objects will exist until you free them

        ```c++
        int main
        {
        	// create object on heap
            
        	// if you actually want the object to live outsize of the life of the current scope, you need to create the object on heap
        	
            // if the size of the object is too large or we have too many objects, we might not have enough room on stack because the stack is usually quite small, usually 1M or 2M bytes depending on the platform and compiler
          
        	// this will cost more time than create on stack and you need to free the memory allocated to the object
        	Entity* e2;
        	{
        		Entity* entity6 = new Entity("xiaoli");  // note that the key word "new"
        		e2 = entity6;
        	}
        	delete e2;
        }
        ```

        