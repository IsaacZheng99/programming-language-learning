## 12. Static

**Knowledge Points**:

1. `static outside of a class or struct: static global variables/functions; link internally; extern`
3. `static member variable`
4.  `static member method`
5. `local static variable`
6. `different implementations of Singleton`

### 1. static outside of a class or struct

#### 1. Link internally

1. The `static global variables` are **only** visible to the current `translation unit` and the `linkage` of that symbol that we declare to be `static` is going to be `internal`, meaning that it's only going to `be visible to the translation unit` that we've defined it in.
2. The `linker` will only try to find `linkage` internally. A `static` `varible` or `function` means that when it comes to `link` those actual `varibles` or `functions`  to **actually defined symbols**, the `linker` is **not** going to look outside of the scope of the `translation unit` for that symbol definition.

#### 2. Key word extern

1. If we simply define two `global variables` with the same name, there will be a `link error`:

    ```c++
    // Mian.cpp
    int g_Variable = 1;
    
    // Static.cpp
    int g_Variable = 2;
    
    // Wrong! fatal error LNK1169: one or more multiply defined symbols found
    ```

2. If we use `static` to make the `variable` to be `linked` `internally`, it will be fine:

    ```c++
    // Mian.cpp
    int g_Variable = 1;
    
    // Static.cpp
    static int g_Variable = 2;
    ```

3. If we wan to `declare` the `global variable` in one file and `link` it externally, we need to use `extern`. The key word `extern` means it's going to look for the `g_Variable` in an **external** `translation unit`, which is called `external linkage` or `external linking`.

    ```c++
    // Mian.cpp
    extern int g_Variable;
    
    // Static.cpp
    int g_Variable = 2;
    ```

    But if we `initialize` the `extern variable`, there will be a `link error` because it's no longer a `declaration` but a `definition`:

    ```c++
    // Mian.cpp
    extern int g_Variable = 1;
    
    // Static.cpp
    int g_Variable = 2;
    
    // Wrong! fatal error LNK1169: one or more multiply defined symbols found
    ```

### 2. static inside a class or struct

#### 1. static member variable

If you use `static` with a `variable` inside a `class`, it means there is only going to be **one** instance of that `variable` across **all** instances of that `class`, meaning if one of the `class` instances **changes** the `static variable`, it's going to reflect that change across **all** `class` instances, so there is no point to refer to the `variable` through a `class` instance, even though we can access a `static variable` through a `class` instance.

#### 2. static member method

1. If you use `static` with a `method` inside a class, you don't have access to the `class` instance inside a `static` method since you don't have that `class` instance to refer to.

2. A `static` method **can't** access `non-static` `variables`.

3. In fact, every `non-static` method always gets an instance of the current `class` as a parameter.

    ```c++
    class Entity
    {
    public:
        int x, y;
    public:
        void Print()
        {
            std::cout << x << ", " << y << std::endl;
        }
    };
    
    void Print(Entity& e)  // The "Print()" method in "class Entity" is just like this, which has a "hidden parameter", which is the "this" pointer
    {
        std::cout << e.x << ", " << e.y << std::endl;
    }
    ```

4. you need to `define` `static variable` somewhere

    ```c++
    // version 1: there is a linking error: unresolved external symbol "public: static int Entity:: x", "public: static int Entity:: y"
    struct Entity
    {
        static int x, y;
    }
    
    int main()
    {
        Entity e;
        e.x = 1;  // Wrong! Linking error.
        e.y = 2;
    }
    
    // version 2: we have to define those static variables somewhere
    struct Entity
    {
        static int x, y;
    }
    
    int Entity::x;
    int Entity::y;
    
    int main()
    {
        Entity e;
        e.x = 1;
        e.y = 2;
    }
    
    // version 3: refer to the static varibales through class
    // it's like we've made two variables that are inside a namespace called "Entity"
    struct Entity
    {
        static int x, y;
    }
    
    int Entity::x;
    int Entity::y;
    
    int main()
    {
        Entity::x = 1;
        Entity::y = 2;
    }
    ```

### 3. static in a local scope

#### 1. local static variable

a `local static variable` allows us to declare a `variable` that has a **lifetime** of essentially our entire program, however, its **scope** is limitted inside that scope (e.g., a `function`)

```c++
void Function()
{
    static int i = 0;
    i++;
    std::cout << i << std::endl;
}

int main()
{
    Function();  // 1
    Function();  // 2
    Function();  // 3
    std::cout << i << std::endl;  // Wrong! Compiling error.
}
```

```c++
void Function()
{
    static int i = 0;
    i = 0;
    i++;
    std::cout << i << std::endl;
}

int main()
{
    Function();  // 1
    Function();  // 1
    Function();  // 1
}
```

it's like a `global variable`, but we can refer to `global variable` outside the `function`: 

```c++
int i = 0;

void Function()
{
  i++;
  std::cout << i << std::endl;
}

int main()
{
  Function();  // 1
  i = 10;
  Function();  // 11
  Function();  // 12
}
```

#### 2. singleton

 (Note that the code here is just a simple example to illustrate the usage of `static local variable` but not a serious `Singleton` implementation.)

1. Use a `static member variable`: `private static Singleton*` or `private static Singleton`:

    ```c++
    // version 1:
    class Singleton
    {
    private:
        static Singleton* s_Instance;
    private:
        Singleton() {}
    public:
        static Singleton& Get()
        {
            if (s_Instance == nullptr)
                s_Instance = new Singleton();
            return *s_Instance;
        }
        
        void Hello() {}
    }
    
    Singleton* Singleton::s_Instance = nullptr;
    
    int main()
    {
        Singleton::Get().Hello();
    }
    
    // version 2:
    class Singleton
    {
    private:
        static Singleton s_Instance;
    public:
        static Singleton& Get()
        {
            return s_Instance;
        }
        
        void Hello() {}
    }
    
    Singleton Singleton::s_Instance;
    
    int main()
    {
        Singleton::Get().Hello();
    }
    ```

2. Use a `static local variable`:

    ```c++
    class Singleton
    {
    public:
        static Singleton& Get()
        {
            static Singleton instance;
            return instance;
        }
      
      void Hello() {}
    }
    
    int main()
    {
        Singleton::Get().Hello();
    }
    ```

