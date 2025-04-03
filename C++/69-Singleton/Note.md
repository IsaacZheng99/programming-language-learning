## 69. Singleton

**Knowledge Points**: `singleton class can leverage the features of class`, `delete the copy constructor`, `different implementations of singleton`

### 1. what is singleton

a `singleton` is basically a single instance of a `class`

### 2. why do we need a class which will be instantiated only once

1. we want to essentially have a functionality that applys to some kind of **global set of data** that we just want to potentially repeatedly reuse, e.g., a random number generator which we just need to initialize it once and give it a initial random seed and the repeatedly call the generate function to get the random numbers, another example is the renderer
2. ultimately speaking, `singleton` can just behave like `namespace`, we can say `singleton` in `C++` is just a way to organize a bunch of `global variables` and `static functions`, which may or may not act upon those `variables`

### 3. implementations of singleton

#### 1. not delete copy constructor

this is not a formal `singleton` because we can copy the `object`

```c++
class Singleton
{
public:
    static Singleton& GetInstance()
    {
        return s_Instance;
    }
    
    void Function() {}
private:
    Singleton() {}
    
    static Singleton s_Instance;
};

Singleton Singleton::s_Instance;

int main()
{
    Singleton::GetInstance().Function();
    
    Singleton anotherInstance = Singleton::GetInstance();  // will copy!
}
```

#### 2. delete copy constructor

for avoiding copy, we can `delete` the `copy constructor` and for better protection, we also `delete` the `copy assignment operator` (note that the `default constructor` has been put into the `private` part, meaning we can't use `Singleton2 instance2; instance2 = instance1`;)

```c++
class Singleton
{
public:
    Singleton(const Singleton&) = delete;  // delete the copy constructor
    Singleton& operator=(const Singleton&) = delete;  // we usually also delete the copy assignment operator
    
    static Singleton& GetInstance()
    {
        return s_Instance;
    }
    
    void Function() {}
private:
    Singleton() {}
    
    static Singleton s_Instance;
};

Singleton Singleton::s_Instance;

int main()
{
    Singleton& instance = Singleton::GetInstance();
    auto& instance = Singleton::GetInstance();
    // Singleton instance = Singleton::GetInstance();  // Wrong! Compiling error.
    Singleton::GetInstance().Function();
}
```

#### 3. instance inside the Get() function

we can put the `instance` inside the `GetInstance()` function

```c++
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton& GetInstance()
    {
        static Singleton instance;  // // "instance" will be instantiated when "GetInstance()" is called for the first time
        return instance;
    }
    
    void Function() {}
private:
    Singleton() {}
};

int main()
{
    Singleton& instance = Singleton::GetInstance();
    Singleton::GetInstance().Function();
}
```

### 4. examples of random number generator

#### 1. the normal way

```c++
class Random
{
public:
    Random(const Random&) = delete;
    
    static Random& GetInstance()
    {
        return s_Instance;
    }
    
    float Float()
    {
        return m_RandomGenerator;
    }

private:
    Random() {}
    
    float m_RandomGenerator = 1.1f;  // pretend this is random
    
    static Random s_Instance;
};

Random Random::s_Instance;

int main()
{
    float number = Random::GetInstance().Float();
}
```

#### 2. more simplified calling

maybe we don't want to get the random number by `Random::GetInstance().Float();` but by `Random::Float();`, we can add an extra `function`

```c++
class Random
{
public:
    Random(const Random&) = delete;
    
    static Random& GetInstance()
    {
        return s_Instance;
    }
    
    static float Float()
    {
        return GetInstance().IFLoat();
        // you can also write "return GetInstance().m_RandomGenerator", but the benefit of the function "float IFloat()" is that it's not a "static" method, which means you can access all the class members in it, so in a lot of cases, you will keep it
    }
    
private:
    float IFloat()  // some people like to call it "Float Internal (FloatInternal())", "Float Implementation (FloatImpl())", here the "I" means "Internal" and makes the function like an interface
    {
        return m_RandomGenerator;
    }
    
    Random() {}
    
    float m_RandomGenerator = 1.1f;
    
    static Random s_Instance;
};

Random Random::s_Instance;

int main()
{
    float number = Random::Float();  // make it by only one step
}
```

### 5. namespace vs. singleton

```c++
namespace RandomClass {
    
    static float s_RandomGenerator = 1.1f;
    static float Float() { return s_RandomGenerator; }
}

int main()
{
    float number = RandomClass::Float();  // we can make it but we can't use the features of "class"
}
```

