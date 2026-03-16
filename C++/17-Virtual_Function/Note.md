## 17. Virtual Function

**Knowledge Points**:

1. `virtual function`
2. `hide`
3. `override`
4. `dynamic dispatch`
5. `v table`

#### 1. What can virtual function do

`virtual functions` allow us to `override` methods in `subclasses`.

#### 2. hide

1. When we simply write a `method` in the subclass, which has a **same name** with a `method` in the base class, here comes `hide`.
2. When we just declare our `method` normally inside our class, then when it comes to call a `method`, it's going to call whatever `method` belongs to the type.

```c++
class Entity
{
public:
    std::string GetName() {return "Entity";}
};

class Player : public Entity
{
private:
    const std::string m_Name;
public:
    Player(const std::string& name)
        : m_Name(name) {}
  
    std::string GetName() {return m_Name;}
};

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl;
    // "entity" is an "Entity*", so it will always call the "GetName()" function in the "class Entity" in this case
}

int main()
{
  Entity* e = new Entity();
  std::cout << e->GetName() << std::endl;  // Entity
  PrintName(e);  // Entity
  
  Player* p1 = new Player("p1");
  std::cout << p1->GetName() << std::endl;  // p1
  PrintName(p1);  // Entity
  
  Entity* p2 = p1;
  std::cout << p2->GetName() << std::endl;  // Entity
  PrintName(p2);  // Entity
}
```

#### 3. override

1. `virtual function` introduces something called `dynamic dispatch`, which compilers typically implement via a `v table`, which is basically a table which contains a **mapping** for all of the `virtual functions` inside our base `class`, so that we can actually map them to the correct `overriden functions` at runtime.

    ```c++
    class Entity
    {
    public:
        virtual std::string GetName() {return "Entity";}
        // key word "virtual"
    };
    
    class Player : public Entity
    {
    private:
        const std::string m_Name;
    public:
        Player(const std::string& name)
            : m_Name(name) {}
      
        std::string GetName() {return m_Name;}
    };
    
    void PrintName(Entity* entity)
    {
        std::cout << entity->GetName() << std::endl;
    }
    
    int main()
    {
      Entity* e = new Entity();
      std::cout << e->GetName() << std::endl;  // Entity
      PrintName(e);  // Entity
      
      Player* p1 = new Player("p1");
      std::cout << p1->GetName() << std::endl;  // p1
      PrintName(p1);  // p1
      
      Entity* p2 = p1;
      std::cout << p2->GetName() << std::endl;  // p1
      PrintName(p2);  // p1
    }
    ```

2. It's better to add the key word `override` to make it more readable, avoid spelling problem like `Getname()` and avoid forgetting the `virutal` key word in the base class.

    ```c++
    class Player : public Entity
    {
    private:
        const std::string m_Name;
    public:
        Player(const std::string& name)
            : m_Name(name) {}
      
        std::string GetName() override {return m_Name;}
    };
    ```

#### 4. Cost of virtual function

`virtual functions` aren't free, there are two runtime costs associated with `virtual functions`:

1. **memory cost**: 

    We have the additional memory that is required in order for us to store that `v-table` so that we can `dispatch` to the correct function, and `memory` that includes a `member pointer` in the `class` that points to the `v-table`.

2. **calling cost**: 

    Every time we call a `virtual function`, we have to access that `v-table` to determine which `function` to actually map.

`virtual functions` generally brings a little overhead but it helps a lot.

