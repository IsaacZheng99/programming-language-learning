## 19. Visibiity

**Knowledge Points**: `visibility`, `visibility of class members`, `visibility of inheritance`, `friend`

1. **what is vidibility**: 

    `vidibility` just means who can see, use or call and it has **no** effects on how your program acutually runs and **no** effects on program performance

2. **visibility of class members**: 

    1. **private**: 

        `private` means **only** the current class can actually access these variables (note hat in `C++` there is a key word `friend`, which makes a `class` or a `function` be able to access the private members)

        ```c++
        class Entity
        {
        private:
        	int x, y;
        };
        
        class Player : public Entity
        {
        public:
        	Player()
            {
                x = 0;  // Wrong!
            }
        };
        ```

    2. **protected**: 

        `protected` means the current `class` and all `subclasses` along the hierarchy can access

        ```c++
        class Entity
        {
        protected:
            int x, y;
        };
        
        class Player : public Entity
        {
        public:
            Player()
            {
                x = 0;
            }
        };
        ```

    3. **public**: 

        `public` means anyone can access

3. **visibility of inheritance**: 

    1. **private inheritance**: 

        the `public` and `protected` members in the `base class` will become `private` in the `subclass`, the `private` members are still inaccessible

        ```c++
        class Entity
        {
        public:
            int x, y;
        };
        
        class Player : private Entity
        {
        public:
            Player()
            {
                x = 0;
            }
        };
        
        class SubPlayer : public Player
        {
        public:
            SubPlayer()
            {
                x = 0;  // Wrong! Compiling error.
            }
        };
        
        int main()
        {
            Player p;
            std::cout << p.x << std::endl;  // Wrong! Compiling error.
        }
        ```

    2. **protected inheritance**: 

        the `public` and `protected` members in the `base class` will become `protected` in the `subclass`, the `private` members are still inaccessible

        ```c++
        class Entity
        {
        public:
            int x, y;
        };
        
        class Player : protected Entity
        {
        public:
            Player()
            {
                x = 0;
            }
        };
        
        class SubPlayer : public Player
        {
        public:
            SubPlayer()
            {
                x = 0;
            }
        };
        
        int main()
        {
            Player p;
            std::cout << p.x << std::endl;  // Wrong! Compiling error.
        }
        ```

    3. **public inheritance**: 

        the `public` and `protected` members in the `base class` will remain the same in the `subclass`, the `private` members are still inaccessible

4. **friend**: 

    1. **friend function**: 

        `friend function` can access all the member of the current `class`, but it's not a member of the current `class` and it can't access the `this` pointer

        ```c++
        class FriendFunctionEntity
        {
        private:
            int x, y;
            
            friend void PrintFriendFunctionEntity(FriendFunctionEntity* e);
        };
        
        void PrintFriendFunctionEntity(FriendFunctionEntity* e)
        {
            std::cout << e->x << ", " << e->y << std::endl;
        }
        
        int main()
        {
            FriendFunctionEntity* friendFunctionEntity = new FriendFunctionEntity();
            PrintFriendFunctionEntity(friendFunctionEntity);
        }
        ```

    2. **friend class**: 

        `friend class` can access all the member of the current `class`

        ```c++
        class FriendClassEntity
        {
        private:
            int x, y;
            
            friend void Friend;
        };
        
        class Friend
        {
        public:
            void PrintFriendClassEntity(FriendClassEntity* e)
            {
                std::cout << e->x << ", " << e->y << std::endl;
            }
        };
        int main()
        {
            FriendClassEntity* friendClassEntity = new FriendClassEntity();
            Friend friendClass;
            friendClass.PrintFriendClassEntity(friendClassEntity);
        }
        ```

    3. the `friend` relationship can't be inherited, meaning if a `function` or a `class` is `friend` with the current `class`, it's not `friend` with the `subclasses` of the current `class`

5. **why we need visibility**: 

    easy to read, maintain, extend the code

    e.g., you want to change the value of `X`, you can simply do `X = 5`, however most of the time we also need **other** operations, in this case, it's reasonable to set `X` as `private` and provide a `public` method called `SetX()`, which can set the value of `X` and do other things

    ```c++
    private:
    	int x;
    public:
        void SetX(int newX)
        {
            x = newX;
            // other operations
            Refresh();
            // ...
        }
    ```

