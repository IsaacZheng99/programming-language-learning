## 16. Inheritance

**Knowledge Points**: `inheritance`, `polymorphism`, `subclass and parent class`, `function with parent-class-typed parameter`

1. **polymorphism**: 

    basically `polymorphism` is the idea of having multiple types for a single type

2. **inheritance**: 

    1. **the subclass will have all the non-private members of its parent class**

        ```c++
        class Entity
        {
        private:
            bool m_Flag;
        public:
            float x, y;
            
            void Move(float xa, float ya)
            {
                x += xa;
                y += ya;
            }
        };
        
        class Player : public Entity
        {
        public:
            void Print()
            {
                std::cout << x << ", " << y << std::endl;
            }
        };
        
        int main()
        {
            Player p;
            p.Move(1.0f, 1.0f);
            p.Print();
        }
        ```

    2. **a function with Entity-typed parameter can also accept Player-typed value**: 

        ```c++
        void Print(const Entity& entity)
        {
            std::cout << entity.x << ", " << entity.y << std::endl;
        }
        
        int main()
        {
            Player p;
            p.Move(1.0f, 1.0f);
            p.Print();
            Print(p);
        }
        ```

