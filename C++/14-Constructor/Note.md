## 14. Constructor

**Knowledge Points**:

1. `constructor`
2. `non-parameter constructor`
3. `constructor with parameter`
4. `default constructor`
5. `if we don't want people to create instances`

#### 1. What is constructor

A `constructor` is basically a special type of `method`, which runs every time when we `instantiate` an object.

#### 2. Instantiate a class to get an object

1. When we instantiated `class Entity` and allocated `memory` for it, we **didn't** actually initialize that `memory`, meaning we got **whatever was left over** in that `memory` space. (Note that in `Debug` mode, the memory will be set as `0xcccccccc`.)

    ```c++
    class Entity
    {
    public:
        float x, y;
      
        void Print()
        {
            std::cout << x << ", " << y << std::endl;
        }
    };
    
    int main()
    {
        Entity e;
        e.Print();  // -1.07374e+08, -1.07374e+08
    }
    ```

2. In general, it's **not safe** to use `memory` that has not been `initialized`:

    (Note that the case below depends on the `compiler` and I've tried `gcc 13.2.0` and it has warning but not error.)

    ```c++
    int main()
    {
        Entity e;
        std::cout << e.x << e.y << std::endl;  // error C4700: uninitialized local variable 'e' used
        // here we are trying to use memory that has not been initialized
    }
    ```

3. If you call a `method` of `Entity` first, and then access `e.x` and `e.y`, it will work well with `MSVC`: 

    ```c++
    class Entity
    {
    public:
        float x, y;
      
        void Hello() {}
    };
    
    int main()
    {
        Entity e;
        e.Hello();
        std::cout << e.x << e.y << std::endl;  // -1.07374e+08, -1.07374e+08
    }

#### 3. How about calling a Init() function

Maybe we can also create a `function` called `void Init()` to handle some initializing issues and call it manually **every time** we instantiate an object, but this will make the code not clean.

```c++
class EntityWithInit
{
public:
    float x, y;
  
    void Init()
    {
        x = 0.0f;
        y = 0.0f;
    }
};

int main()
{
    EntityWithInit e;
    e.Init();
    std::cout << e.x << e.y << std::endl;  // 0, 0
}
```

#### 4. constructor

##### 1. non-parameter constructor and constuctor with parameters

```c++
class Entity
{
public:
    float x, y;
  
    // a constructor without parameters
    Entity()  // no return type and same name with the class
    {
        x = 0.0f;
        y = 0.0f;
    }
  
    // a constructor with parameters
    // overload: different versions of the "same" methods ("same" means the methods' names are the same) with different parameters
    Entity(float x1, float y1)
    {
        x = x1;
        y = y1;
    }
  
    void Print()
    {
        std::cout << x << ", " << y << std::endl;
    }
};

int main()
{
    Entity e(10.0f, 5.0f);
    e.Print();  // 10, 5
}
```

##### 2. default constructor

If we don't specify a `constructor`, we still have a `constructor` which is called `default constructor` and it does nothing, just like `Entity() {}`.

##### 3. When does a constructor run

`constructor` will not run if we do not instantiate an object, so if we just use a `static method` from a `class`, it won't run.

##### 4. If we don't want people to create instances

1. **make the constructor private**: 

    ```c++
    class Log
    {
    private:
      Log() {}
    public:
      static void Write() {}
    };
    
    int main()
    {
      Log::Write();
    }
    ```

2. **delete the constructor**: 

    ```c++
    class Log
    {
    public:
      Log() = delete;
      
      static void Write() {}
    };
    
    int main()
    {
      Log::Write();
    }
    ```

