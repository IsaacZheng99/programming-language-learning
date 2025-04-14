## 86. NULL

**Knowledge Points**: `the memory address 0`, `read access violation`, `nullptr`, `NULL`, `offsetof`

### 1. null in other languages

for `C#` or `Java`, they are hold your hands, meaning they will throw exception once they encounter the `null reference` or `null pointer` problem to force the developers to handle the problem, but for `C++`, it will continue to execute and may lead to `UB`  

```c#
Entity entity = null;
entity.GetName();  // NullReferenceException
```

```java
Entity entity = null;
entity.GetName();  // NullPointerException
```

### 2. what is the value of NULL

#### 1. the key word nullptr

note that there is no key word `null` in `C++`

```c++
int main()
{
    void* value = nullptr;
    std::cout << value << std::endl;  // 0000000000000000
}
```

```c++
int main()
{
	int* value = nullptr;
    std::cout << value << std::endl;  // 0000000000000000
    std::cout << *value << std::endl;  // Wrong! this will throw an exception: read access violation
}
```

#### 2. the marco NULL

`NULL` is mostly used in `C` and it's totally acceptable to be used in `C++` as well, just might not be stylistically appropriate

```c++
int main()
{
    void* value1 = NULL;
    std::cout << value1 << std::endl;  // 0000000000000000
    int value2 = NULL;
    std::cout << value2 << std::endl;  // 0
}
```

the source code of `NULL`, it is just a `0` in `C++`

```c++
#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void*)0)
	#endif
#endif
```

### 3. what is the problem with NULL

1. now that `NULL` is just `0`, so what is the problem when we use `NULL`? the answer is `pointer`

2. a `pointer` is an address, but `0` is not a valid address, you will get something called `access violation` when you are trying to **read** a `memory` that is not valid, and it's not really the memory specifically is not valid, it's just what memory address the operating system determines is not valid

    so you are trying to read a memory address that does not exist or does not contain memory that you are allowed to access, a good kind of real word analogy to this is you're typing an address into Google Maps, it just doesn't physically exits, you can't go there

### 4. how does NULL work with objects

we have an `Entity class`

```c++
class Entity
{
public:
    Entity() = default;
    
    const std::string& GetName() const { return m_Name; }
    
    void PrintType()
    {
        std::cout << "Entity\n";
    }
private:
    Entity* m_Parent;
    std::string m_Name;
};
```

#### 1. GetName()

```c++
int main()
{
    Entity* entity = nullptr;
    std::cout << entity->GetName() << std::endl;  // Wrong! this will throw an exception: read access violation and you will see "this was 0x8"
    // if we run the Debugger in the "Release" mode, the infomation is a little different: "Access violation reading location 0x0000000000000020", this is because of optimization
}
```

#### 2. PrintType()

```c++
int main()
{
    Entity* entity = nullptr;
    entity->PrintType();  // Entity
}
```

it seems that there is no point to call a `function` on top of a `nullptr`, to solve this, let's go back to `C` first

#### 3. go back to C

there is not `class` in `C`, but there is `struct`, however, the `struct` in `C` can't contain `member functions`, so we have to move them outside

```c++
struct EntityData
{
    Entity* m_Parent;
    std::string m_Name;
};

const std::string& Entity_GetName(const EntityData* self)  // we can't use "this" because we are writing code in "C++"
{
    //return m_Name;  // we can't directly return m_Name, which is relative to an instance of "EntityData", so we need a parameter of the instance, and this is what exactly happens in "C++" when we actually compile the class: the methods inside the class get converted into just the regular free floating functions that actualy take the instance of the class as the first parameter: "EntityData* this"
    // for "static" case, if the member function is static, there is no "EntityData* this" and we can't access the non-static member like "m_Parent" in this function
    
    // self == nullptr
    return self->m_Name;
}
    
void Entity_PrintType(EntityData* self)
{
    // self == nullptr
    std::cout << "Entity\n";
}
```

as we can see, the `self == nullptr` can just influence the `GetName() function` and we should know that `Entity* entity = nullptr;` doesn't mean the `member functions` inside the class are not valid because the `compiler` will turn them into `normal functions` with `this pointer`, but for the `member variables` they can only be accessed by the instance if they are `non-static` (and for my personal view, this is also why we talk about the size of the `class` and `struct`, we can only focus on the `member variables`)

#### 4. the marco offsetof

the marco `offsetof` will give you the offset of a particular `member` of a `class` or `struct`

```c++
int main()
{
    uint64_t offset = offsetof(EntityData, m_Name);
    std::cout << offset << std::endl;
}
```

the source code of `offsetof`

```c++
#if define _MSC_VER && !defined _CRT_USE_BUILTIN_OFFSETOF
	#ifdef __cplusplus
		#define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&((((s*)0)->m)))
	#else
		#define offsetof(s,m) ((size_t)&(((s*)0)->m))
	#endif
#else
	#define offsetof(s,m) __builtin__offsetof(s,m)
#endif
```

based on `((size_t)&(((s*)0)->m))`, we can write our own implementation

```c++
int main()
{
    uint64_t offset = (uint64_t)&(((EntityData*)0)->m_Name);  // note that here we are not reading the memory, which will cause "read access violation", we are just getting the memory address
    std::cout << offset << std::endl;
}
```

now let's call back `4.1`, the exception information is `this was 0x8`, because the `GetName() function` returns `m_Name`, and the offset is `8`

