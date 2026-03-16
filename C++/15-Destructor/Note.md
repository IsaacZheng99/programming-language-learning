## 15. Destructor

**Knowledge Points**:

1. `destructor`
2. `when calling a destructor`
3. `why we need destructor`

#### 1. When calling a destructor

1. **destroy an object**: 

    A `destructor` runs when we destroy an `object` and it is where we **uninitialize** anything that we might have to or clean any memory that we've used.

2. **apply to both stack and heap allocated objects**: 

    If you allocate memory to an `object` by using `new`, when you call `delete`, the `destructor` will get called; if you just have a `stack` based `object` and when the `scope` ends, the object will get deleted and thus the `destructor` will get called.
    
    ```c++
    class Entity
    {
    public:
        float x, y;
      
        Entity()
        {
            x = 0.0f;
            y = 0.0f;
            std::cout << "Created Entity" << std::endl;
        }
      
        ~Entity()  // add a tilde
        {
            std::cout << "Destroyed Entity" << std::endl;
        }
      
        void Print()
        {
            std::cout << x << ", " << y << std::endl;
        }
    };
    
    void Function()
    {
        Entity e;
        e.Print();
    }
    
    int main()
    {
        Function();
    }
    // outputs: 
    // Created Entity
    // 0, 0
    // Destroyed Entity
    ```

#### 2. Why we need destructor

If there is a certain initialization code in the `constructor`, you will likely want to uninitialize or destroy all of that stuff in the `destructor`, because if you don't, you may get `memory leak`.

e.g., if you've allocated any kind of `memory` on the `heap`  manually then you need to manually clean it up.

e.g., if it was allocated throughout the `Entity` or in the `Entity` `constructor`, you're likely going to get rid of it in the `destructor` because when the `destructor` gets called, that `Entity` is gone and the allocation should also be gone.

