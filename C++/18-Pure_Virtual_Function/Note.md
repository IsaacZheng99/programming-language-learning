## 18. Pure Virtual Function

1. **what is pure virtual function**: 

    1. a `pure virtual function` in `C++` is essentially the same as an `abstract method` or an `interface` in other languages such as `Java` or `C#`
    2. it allows us to define a function in a base class that **does not** have an implementation and then **forces** subclasses to actually implement that function
    3. we **can't instantiate** a class which contains an unimplemented function, a `pure virtual function` in this case

    ```c++
    class Printable  // we can call this class "interface"
    {
    public:
        virtual std::string GetClassName() = 0;  // pure virtual function
    };
    
    class Entity : public Printable
    {
    public:
        virtual std::string GetName() {return "Entity";}
        std::string GetClassName() override {return "Entity";}
    };
    
    class Player : public Entity
    {
    private:
        const std::string m_Name;
    public:
        Player(const std::string& name)
            : m_Name(name) {}
      
        std::string GetName() override {return m_Name;}
        std::string GetClassName() override {return "Player";}
    };
    
    void PrintClassName(Printable* obj)  // just set the type of the parameter as Printable, i.e., the "interface" type
    {
        std::cout << obj->GetClassName() << std::endl;
    }
    
    int main()
    {
        Entity* e = new Entity()
        PrintClassName(e);  // Entity
    
        Player* p = new Player("li")
        PrintClassName(p);  // Player
    }
    ```

