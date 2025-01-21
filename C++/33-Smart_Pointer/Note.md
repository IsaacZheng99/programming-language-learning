## 33. Smart Pointer

**Knowledge Points**: `what can smart pointer do`, `when to use smart pointer`, `std::unique_ptr<>`, `std::shared_ptr<>`, `std::weak_ptr<>`

1. **what can smart pointer do**: 

    when we create objects on the `heap` by `new`, we need to manually call `delete` to free the `memory`, `smart pointer` is an **automatic** way to the process

2. **when to use smart pointer**: 

    if you don't want to **explicitly** manage the memory, you should use `smart pointer` and use `unique pointer` whenever you can because it has less overhead, but if you want to "share", use `shared pointer`

3. **std::unique_ptr<>**: 

    1. **scoped pointer**: 

        `std::unique_ptr<>` is a `scoped pointer`, meaning when that pointer goes out of the scope, it will get detroyed and call the `delete`

        ```c++
        class Entity
        {
        private:
            int x, y;
        public:
            Entity()
            {
           		std::cout << "Created Entity!" << std::endl;
            }
            
            Entity(int x, int y)
                : x(x), y(y)
            {
           		std::cout << "Created Entity!" << std::endl;
            }
        
            ~Entity()
            {
            	std::cout << "Destroyed Entity!" << std::endl;
            }
        
            void Print()
            {
                std::cout << x << ", " << y << std::endl;
            }
        }
        
        int main()
        {
            {
                std::unique_ptr<Entity> e1(new Entity(1, 2));
                e1->Print();
                std::unique_ptr<Entity> e2(new Entity());
                e2->Print();
        
                std::unique_ptr<Entity> e3 = std::make_unique<Entity>(1, 2);
                e3->Print();
                std::unique_ptr<Entity> e4 = std::make_unique<Entity>();
                e4->Print();
                // safer (exception safety) and preferred because if the constructor happeds to throw an exception, we won't end up having a dangling pointer with no reference which leads to memory leak
            }
        }

    2. **can't copy**: 

        you can't copy a `unique pointer`, if you copy it, you will get two `unique pointers` pointing to the same block memory and when one of them dies, it will free that memory, meaning that the other `pointer` is pointing to memory that has beed freed

        ```c++
        int main()
        {
            {
                std::unique_ptr<Entity> entity = std::make_unique<Entity>();
                std::unique_ptr<Entity> e = entity;  // Wrong! check the source code of "unique_pointer" and you will find that the "copy constructor" and the "assignment operator" are both "= delete"
            }
        }
        ```

4. **std::shared_ptr<>**: 

    1. if you want to "share" the `pointer`, then use `std::shared_ptr<>`

    2. **reference counting**: 

        the implementation of `shared pointer` actually depends on the compliers and the standard library you're using with your compiler, but most of them use `reference counting`

    3. **control block**: 

        ```c++
        int main()
        {
            {
                std::shared_ptr<Entity> entity1(new Entity());
                
                std::shared_ptr<Entity> entity2 = std::make_shared<Entity>();  // preferred, because "shared_pointer" needs to allocate another block memory called "control block", where it stores the reference count, if you first create a Entity by "new" and then pass it to the "shared_pointer" constructor, it has to allocate twice, in the second case you can combine it together and it will be more efficient
            }
        }
        ```

    4. **use std::shared_ptr<> inside the scope**: 

        ```c++
        int main()
        {
            {
                std::shared_ptr<Entity> entity = std::make_shared<Entity>();
                std::shared_ptr<Entity> e = entity;  // now you can copy
            }
            std::cout << "Destroyed has been printed!" << std::endl;
        }
        ```

    5. **use std::shared_ptr<> outside the scope**: 

        ```c++
        int main()
        {
            {
            	std::shared_ptr<Entity> e0;
                {
                    std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
                    e0 = sharedEntity;
                    sharedEntity->Print();  // check the source code of "std::shared_ptr<>" and you will find the overloaded "operator->", which returns the pointer,
                }
            	std::cout << "Destroyed hasn't been printed!" << std::endl;
            }
        }
        ```

5. **std::weak_ptr<>**: 

    1. it is similar to `std::shared_ptr<>`, but it **won't** increase the `reference count`

    2. **when to use it**: 

        you will use it when you just want a `reference` to do something like sorting

        ```c++
        int main()
        {
            {
            	std::weak_ptr<Entity> e0;
                {
                    std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
                    e0 = sharedEntity;
                    e0->Print();  // Wrong! check the source code of "std::weak_ptr<>" and you will find that there is no overloaded "operator->"
                }
            }
        }
        ```

