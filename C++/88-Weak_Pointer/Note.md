## 88. Weak Pointer

**Knowledge Points**: `shared pointer`, `war pointer`, `weak pointer`, `cyclical dependency`

### 1. how does std::weak_ptr work

`std::weak_ptr` usually works with `shared_ptr`

#### 1. std::shared_ptr

`std::shared_ptr` is a wrap of a `raw pointer` and it can help manage the lifetime automatically, `std::unique_ptr` can also do this, but `std::shared_ptr` can **share**, meaning we can have multiple places inside our program that contain these references to that object and when all of them are gone, the underlying instance gets deleted

```c++
struct Object
{
};


int main()
{
    std::shared_ptr<Object> obj1 = std::make_shared<Object>();
    Object* obj2 = new Object();
    delete obj2;
}
```

share the object

```c++
struct Manager
{
	std::shared_ptr<Object> Obj;  
};


int main()
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();

    Manager manager;
    manager.Obj = obj;  // share
}
```

#### 2. strong reference

`strong reference` can keep things **alive**, when **all** the `strong references` die, the object dies

#### 3. raw pointer

in this case, the `Manager` just keep an address, which is just a number, it can't prevent the `Object` from dying

```c++
struct Manager
{
	Object* Obj;  
};


int main()
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();

    Manager manager;
    manager.Obj = obj.Get();
}
```

however, how can we know we can access the address? maybe the memory has been deleted, but we can still acces the `pointer` and if we read from it, there will be crash

```c++
struct Object
{
    ~Object() { std::cout << "Deleted Object\n"; }
};

struct Manager
{
	Object* Obj;  
};


int main()
{
	Manager manager;
    {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
	    manager.Obj = obj.Get();
    }
    std::cout << manager.Obj << std::endl;
}
```

#### 4. std::weak_ptr

to solve the above problem, here comes the `std::weak_ptr` which can **share** but **not own**, meaning there is no `strong reference`, there has `weak reference` and now we can do safety check, meaning if it is alive, we can do something, if it's not, it's also fine

```c++
struct Manager
{
	std::weak_ptr<Object> Obj;
    
    void Func1()
    {
        if (std::shared_ptr<Object> obj = Obj.lock())
        {
            // obj->
        }
    }
    
    void Func2()
    {
        if (Obj.expired())
        {
            
        }
    }
    
    void Func3()
    {
        std::cout << Obj.use_count() << std::endl;
        
        if (Obj.use_count())
        {
            
        }
    }
};


int main()
{
	Manager manager;
    {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
	    manager.Obj = obj.Get();
        manager.Func3();
    }
    manager.Func3();
}
// outputs:
// 1
// Deleted Object
// 0
```

it's not necessary that you replace all the `raw pointers` with `weak pointers`, which bring negligible overhead, use them based on the specific situation, but maybe `weak pointers` are better in many cases

### 2. cyclical dependency

#### 1. std::shared_ptr

the code below outputs nothing, meaning no objects have been destroyed

```c++
struct B;

struct A
{
	std::shared_ptr<B> ptrB;
    
    ~A() { std::cout << "A destroyed\n"; }
};

struct B
{
	std::shared_ptr<A> ptrA;
    
    ~B() { std::cout << "B destroyed\n"; }
};


int main()
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->ptrB = b;
    b->ptrA = a;
}
```

#### 2. std::weak_ptr

if we change one of them into `std::weak_ptr`

```c++
struct B;

struct A
{
	std::shared_ptr<B> ptrB;
    
    ~A() { std::cout << "A destroyed\n"; }
};

struct B
{
	std::weak_ptr<A> ptrA;
    
    ~B() { std::cout << "B destroyed\n"; }
};


int main()
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->ptrB = b;
    b->ptrA = a;
}
// outputs:
// A destroyed
// B destroyed
```

therefore, for cyclical dependency, we **should** use `weak pointers`

