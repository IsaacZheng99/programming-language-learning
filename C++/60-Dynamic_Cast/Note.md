## 60. Dynamic Cast

**Knowledge Points**: `type system`, `dynamic_cast<>`, `RTTI`

### 1. type system

`type system` in `C++` provides a way for us to protect the code, but it's **not** something that we have necessarily to stick to because we can **freely** `cast` between types if we want

### 2. dynamic_cast<>

1. `dynamic_cast<>` provides some kind of safety for us when we want to do specify `type casting`, it does **extra work** to make sure the way we actually `cast` is valid
2. `dynamic_cast<>` is more like a `function` and it's not like a `cast` which is done at `compiling time`, it's evaluated at `runtime` and it does have an associated **runtime cost**
3. `dynamic_cast<>` is specificaly used for `classes` along the inheritance hierarchy and it can check whether an object belongs to the given type or not
4. `dynamic_cast<>` can do this because it stores the `runtime type information (RTTI)` and it needs some time to check, which does add overhead

### 3. some examples

we have three classes: 

```c++
class Entity {};

class Player : public Entity {};

class Enemy : public Entity {};
```

#### 1. implicit cast

```c++
int main()
{
    Player* player = new Player();
    Entity* e = player;  // implicit cast
    Player* p = e;  // Wrong! Compiling error
}
```

#### 2. dynamic_cast<> without virtual function

```c++
int main()
{
    Player* player = new Player();
    Entity* e = player;
    Player* p = dynamic_cast<Player*>(e);  // Wrong! Compiling error. We need to add a "virtual function" in the "Entity" class to indicate it is a polumorphic type.
}
```

#### 3. dynamic_cast<> with virtual function

```c++
class Entity
{
public:
    virtual void Print() {}
};

class Player : public Entity {};

class Enemy : public Entity {};


int main()
{
    Player* player = new Player();
    Entity* actualPlayer = player;
    Entity* actualEnemy = new Enemy();
    
    Player* p1 = dynamic_cast<Player*>(actualPlayer);
    if (p1)
        std::cout << "p1 is Player" << std::endl;
    Player* p2 = dynamic_cast<Player*>(actualEnemy);
    if (p2 == nullptr)
        std::cout << "p2 is not Player" << std::endl;
}
// outputs:
// p1 is Player
// p2 is not Player
```

