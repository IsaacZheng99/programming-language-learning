## 76. Move Semantics

**Knowledge Points**: `copy`, `move`, `move constructor`

### 1. what can move semantics do

1. `move semantics` essentially allow us to move `objects` around, which is impossible before `C++11` because `C++11` introduces `r-value`, which is necessary for `move semantics`
2. the basic idea is when we write `C++` code, there are a lot of cases in which we don't really need to or want to necessarily **copy** an `object` from one place to another, but that's really the only place that we can get it from one place to another, e.g., pass an `object` to a `function` or return an `object` from a `function` (for the returning case, now we have `RVO`)
3. compared to `reference`, which needs the existence of the `original object` and allows to share the resources, `move semantics` is like to "steal" the resources of the `original object`

### 2. an example

here we use an informal customized `String class` to illustrate

#### 1. copy

the heap allocation happened twice because we need to create the `String object` in the scope of `main()` function and pass it to the `Entity constructor` and  `copy` it to `m_Name`, why can't we juse create it in the `main` function and move it into this space or just create it here?

```c++
class String
{
public:
    String() = default;
    
    String(const char* string)
    {
        printf("Created\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];  // note that there is no null termination character
        memcpy(m_Data, string, m_Size);
    }
    
    String(const String& other)
    {
        printf("Copied\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];  // allocate memory on the heap
        memcpy(m_Data, other.m_Data, m_Size);
    }
    
    ~String()
    {
        printf("Destroyed\n");
        delete m_Data;
    }
    
    void Print()
    {
  		for (uint32_t i = 0; i < m_Size; i++)
            printf("%c", m_Data[i]);
        
        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity
{
public:
    Entity(const String& name)
        : m_Name(name)  // "copy": String m_Name = name, here "String m_Name" is the class member not a local variable
    {
    }
    
    void PrintName()
    {
        m_Name.Print();
    }
private:
  	String m_Name;  // Why can't we just create in the "main" function and move it into this space or just create it here?
};

int main()
{
    Entity entity("xiaoli");  // create in the "main" function
    entity.PrintName();
}
// outputs: 
// Created
// Copied
// Destroyed
// xiaoli
// Destroyed
```

#### 2. move

first we add the `move constructor` of the `String class`, which takes an `r-value reference` and do the `move` action, then we need to add the `Entity(String&& name) function` in the `Entity class`, because the `Entity entity("xiaoli");` code will create a **temporary** `String object` (note that `Entity(cosnt String& name)` can also take the temporary as a parameter but we want to distinguish) and do `std::move` or `String&& cast` to call the `move constructor` of the `String class`

as the outputs show, the allocation only happened once

```c++
class String
{
public:
    String() = default;
    
    String(const char* string)
    {
        printf("Created\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }
    
    String(const String& other)
    {
        printf("Copied\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }
    
    String(String&& other) noexcept
    {
        printf("Moved\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;  // point to the same block of memory
        
        other.m_Size = 0;
        other.m_Data = nullptr;  // take over the old data, when the "other" is destroyed, the memory won't be freed because it will just delete a "nullptr", if you don't do so, it will delete "m_Data", meaning the block of memory will be freed and thus you will lose the data
        // note that instead of doing "deap copy" like "copy constructor", we've essentially done a "shallow copy"
    }
    
    ~String()
    {
        printf("Destroyed\n");
        delete m_Data;
    }
    
    void Print()
    {
  		for (uint32_t i = 0; i < m_Size; i++)
            printf("%c", m_Data[i]);
        
        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity
{
public:
    Entity(const String& name)
        : m_Name(name)
    {
    }
    
    Entity(String&& name)  // a constructor with an "r-value reference" parameter
        //: m_Name((String&&)name)  // explicitly cast "name" to a temporary
        : m_Name(std::move(name))  // more often to use "std::move"
    // if we still write "m_Name(name)", it will call the "String(const String& other)" function because a "r-value reference" is essentially a "l-value", meaning "name" is essentially an "l-value" and if you check the source code of "std::move", you will see it calls the "static_cast" to cast "name" to "String&&"
    {
    }
    
    void PrintName()
    {
        m_Name.Print();
    }
private:
  	String m_Name;
};

int main()
{
    Entity entity("xiaoli");
    entity.PrintName();
}
// outputs: 
// Created
// Copied
// Destroyed
// xiaoli
// Destroyed
```

