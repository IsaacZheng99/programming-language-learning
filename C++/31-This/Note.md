## 31. This

**Knowledge Points**: `this`, `usage of this`

1. **what is this**:

    `this` is a `const pointer` to the current `object instance` that the `method` belongs to

2. **how to access this**: 

    `this` is only accessible to us through a `member function`

3. **usage of this**:

    1. **assign the member variable**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
            	x = x;  // it's just assigning local variable "x" with its own value
            }
        };
        
        int main()
        {
            Entity e(1, 2);
            std::cout << e.x << std::endl;  // -858993460
        }
        ```

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
            	this->x = x;
            }
        };
        
        int main()
        {
            Entity e(1, 2);
            std::cout << e.x << std::endl;  // 1
        }
        ```

    2. **this is a const pointer**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
                Entity* e1 = this;
            	Entity* const e2 = this;  // "this" is an "Entity* const" pointer
            	this = nullptr;  // Wrong!
            }
        }
        ```

    3. **reference this**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
            	// Entity*& e1 = this;  // Wrong! the reference is not "const"
            	Entity* const& e2 = this; // we have to decalare the reference is "const" because "this" is "Entity* const"
                const Entity* const& e3 = this;
            }
        }
        // you can check the error message and you will learn about the overload of "Entity*", "Entity* const", "const Entity*"
        ```

    4. **access member by this**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
                this->x = x;
                // (*this).x = x;
        
                // Entity* e = this;
                // e->x = x;
            }
        }
        ```

    5. **add const in method**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
                this->x = x;
                this->y = y;
            }
        
            int GetX() const  // here we add "const" and the "this" will become "const Entity* const"
            {
                // Entity* e = this;  // Wrong!
                const Entity* e = this;
                return x;
            }
        }
        ```

    6. **this and *this**: 

        ```c++
        class Entity;
        void PrintEntity1(Entity* e);
        void PrintEntity2(const Entity& e);
        
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
                this->x = x;
                this->y = y;
        
                PrintEntity1(this);
                PrintEntity2(*this);
            }
        }
        
        void PrintEntity1(Entity* e)
        {
        	std::cout << "PrintEntity1" << std::endl;
        }
        
        void PrintEntity2(const Entity& e)
        {
        	std::cout << "PrintEntity2" << std::endl;
        }
        ```

    7. **delete this**: 

        ```c++
        class Entity
        {
        public:
            int x, y;
        
            Entity(int x, int y)
            {
                this->x = x;
                this->y = y;
        
            	delete this;  // Wrong! Runtime error.
                // avoid doing this unless in very specialized cases
            }
        }
        ```

