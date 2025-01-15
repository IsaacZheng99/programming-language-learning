## 12. Static

**Knowledge Points**: `visibility of static variables/functions outside of a class/struct`, `extern`, `static member variable`, `static member method`, `local static variable`, `different implementations of Singleton`

1. **static outside of a class or struct**: 

    1. **only invisible to the current translation unit**: 

        the linkage of that symbol that you declare to be `static` is going to be `internal`, meaning that it's only going to `be visible to that translation unit` that you've defined it in

    2. **only try to find linkage internally**: 

        a `static` varible or function means that when it comes time to `link` those actual functions or varibles to actually defined symbols, the linker is **not** going to look outside of the scope of this `translation unit` for that symbol definition

    3. **extern**: 

        ```c++
        //"extern" means it's going to look for the "s_Variable" in an external translation unit, which is called external lincage or external linking 
        // Mian.cpp
        extern int s_Variable;
        // Static.cpp
        int s_Variable = 5;
        ```

2. **static inside a class or struct**: 

    1. **static variable**: 

        if you use `static` with a `variable` inside a class, it means there is only going to be **one** instance of that `variable` across **all** instances of that class, meaning if one of the class instances **changes** the static variable, it's going to reflect that change across **all** class instances, so there is no point of referring to the `variable` through a class instance

    2. **static method**: 

        1. if you use `static` with a `method` inside a class, you don't have access to the class instance inside a static method since you don't have that class instance to refer to

        2. a `static` method **can't** access `non-static` variables

        3. in fact, every `non-static` method always gets an instance of the current class as a parameter

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
                std::cout << x << ", " << y << std::endl;
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

3. **static in a local scope**: 

    1. **local static variable**: 

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

    2. **singleton**: (note that the code here is just a simple example to illustrate the usage of `static local variable` but not a serious `Singleton` implementation)

        1. by using a `static member variable`: `private static Singleton*` or `private static Singleton`

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

        2. by using a `static local variable`

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

            

        

    