## 28. New

**Knowledge Points**: `new`, `delete`, `new[]`, `delete[]`, `placement new`

1. **what does new do**: 

    `new` allocates memory and calls the `constructor`

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
    
    int main()
    {
    	Entity* e1 = new Entity();
    	// Entity* e2 = (Entity*)(malloc(sizeof(Entity)));  // in "C", we use "malloc" to allocate memory, but don't do this in "C++" except that you have to because in this case it only allocates memory but not calls the constructor
    	delete e1;  // don't forget "delete", it calls the "C" function "free()" and the "destructor" of Entity class
    	// there are a lot of "C++" strategies like scope-based pointer, reference counting to automate the "delete" operation
    }
    ```

2. **what are new and delete**: 

    `new` and `delete` are both `operators`, we can overload them

3. **what are new[] and delete[]**: 

    `new[]` and `delete[]` are also `operators`

    ```c++
    int main()
    {
        int* a = new int;
        delete a;
    
        int* array = new int[10];
        delete[] array;
    
        Entity* entities = new Entity[10];
        delete[] entities;
    }
    ```

4. **placement new**: 

    ```c++
    int main()
    {
        int* a = new int[1000];
        Entity* e = new(array) Entity();  // note the size of "Entity e" object (40 bytes) and the size of the array (4 * 1000 bytes)
        delete[] a;
    }
    ```

