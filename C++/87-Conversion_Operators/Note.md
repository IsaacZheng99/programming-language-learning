## 87. Conversion Operators

**Knowledge Points**: ` conversion operators`, `when a function can handle both types`, `cleaner and less clear`

### 1. what does conversion operator do

it can convert one type to another type

### 2. some examples

#### 1. simple usage

now we have a simple custom `Orange class`

```c++
struct Orange
{
    operator float() { return 5.5f };
};
```

##### 1. directly assign

```c++



int main()
{
    Orange orange;
    float f = orange;
    std::cout << f << std::endl;  // 5.5
}
```

##### 2. cast

```c++
int main()
{
    Orange orange;
    std::cout << (float)orange << std::endl;  // 5.5
}
```

##### 3. parameter of function

```c++
void PrintFloat(float value)
{
    std::cout << value << std::endl;
}


int main()
{
    Orange orange;
    PrintFloat(orange);  // 5.5
}
```

#### 2. scoped pointer

now we have a custom `ScopedPtr class `and `Entity struct`

```c++
template <typename T>
class ScopedPtr
{
public:
    ScopedPtr() = default;
    
    ScopedPtr(T* ptr)
        : m_Ptr(ptr) {}
    
    ~ScopedPtr()
    {
        delete m_Ptr;
    }
    
    T* Get() { return m_Ptr; }
    
    const T* Get() const { return m_Ptr; }
private:
    T* m_Ptr;
};

struct Entity
{
    float X = 0.0f, Y = 0.0f;
};
```

##### 1. conditional expression

for `Entity*`, we can directly judge it like below, we can simply explain this that `pointer` is indeed an integer

```c++
void ProcessEntity(Entity* e)
{
    if (e)
    {
        
    }
}


int main()
{
    Entity* entity = new Entity();
    if (entity)
    {
        
    }
    if (entity != nullptr)
    {
        
    }
    if (!entity)
    {
        
    }
    bool b = (bool)entity;
}
```

but for `ScopedPtr`, we can't

```c++
void ProcessEntity(cosnt ScopedPtr<Entity>& e)
{
    if (e)  // Wrong! Compiling error.
    {
        
    }
}

int main()
{
    ScopedPtr<Entity> e = new Entity();
    if (e)  // Wrong! Compiling error.
    {
        
    }
}
```

##### 2. directly add a function to judge

```c++
template <typename T>
class ScopedPtr
{
public:
    ScopedPtr() = default;
    
    ScopedPtr(T* ptr)
        : m_Ptr(ptr) {}
    
    ~ScopedPtr()
    {
        delete m_Ptr;
    }
    
    bool IsValid() { return m_Ptr != nullptr; }  // add a function
    
    T* Get() { return m_Ptr; }
    
    const T* Get() const { return m_Ptr; }
private:
    T* m_Ptr;
};

void ProcessEntity(const ScopedPtr<Entity>& e)
{
    if (e.IsValid())
    {
        
    }
}
```

##### 2. conversion operator

we can use `conversion operator` to keep the same code

```c++
template <typename T>
class ScopedPtr
{
public:
    ScopedPtr() = default;
    
    ScopedPtr(T* ptr)
        : m_Ptr(ptr) {}
    
    ~ScopedPtr()
    {
        delete m_Ptr;
    }
    
    bool IsValid() { return m_Ptr != nullptr; }
    
    operator bool() const { return IsValid() ; }  // conversion operator
    
    T* Get() { return m_Ptr; }
    
    const T* Get() const { return m_Ptr; }
private:
    T* m_Ptr;
};

void ProcessEntity(const ScopedPtr<Entity>& e)
{
    if (e)
    {
        
    }
}
```

##### 4. std::unique_ptr

the `std::unique_ptr` also implements the `operator bool()`

```c++
void ProcessEntity(const std::unique_ptr<Entity>& e)
{
    if (e)
    {
        
    }
}
```

#### 3. timer

now we have a custom `Timer struct`

```c++
struct Timer
{
	using Clock = std::chronologically::high_resolution_clock;
    using TimePoint = std::chronologically::time_point<Clock>;
    
    void Start() const { m_Start = Clock::now(); }
    void Stop() const { m_Stop = Clock::now(); }
    
    double GetSeconds() const
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f * 0.001f;
    }
    
    double GetMilliSeconds() const
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f;
    }
private:
    TimePoint m_Start, m_Stop;
};
```

##### 1. directly use timer

```c++
int main()
{
    Timer timer;
    timer.Start();
    // do something...
    timer.Stop();
    double time = timer.GetSeconds();
}
```

##### 2. conversion operator

```c++
struct Timer
{
	using Clock = std::chronologically::high_resolution_clock;
    using TimePoint = std::chronologically::time_point<Clock>;
    
    void Start() const { m_Start = Clock::now(); }
    void Stop() const { m_Stop = Clock::now(); }
    
    double GetSeconds() const
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f * 0.001f;
    }
    
    double GetMilliSeconds() const
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(m_Stop - m_Start).count() * 0.001f;
    }
    
    operator double() const { return GetSeconds(); }  // conversion operator
private:
    TimePoint m_Start, m_Stop;
};


int main()
{
    Timer timer;
    timer.Start();
    // do something...
    timer.Stop();
    double time = timer;
}
```

we can even do math on the `timer`

```c++
int main()
{
    Timer timer1;
    timer1.Start();
    // do something...
    timer1.Stop();
    
 	Timer timer2;
    timer2.Start();
    // do something...
    timer2.Stop();
    
    double totalTime = timer1 + timer2;
}
```

but it definitely lower the readablitity because we don't know whether `operator double()` really represents seconds or milliseconds

#### 4. a real world bug

now we have a custom `PerframeData struct`, it initially just a `float` to record the time and for some reason, it converts to a `struct` to contain another vatiable `Samples`, so there has an `operator float()` to help simpify the code, however, it leads to a bug

```c++
struct PerframeData
{
    float Time = 0.0f;
    uint32_t Samples = 0;
    
    PerframeData() = default;
    
    PerframeData(float time)
        : Time(time) {}
    
    operator float() const { return Time; }
    
    inline PerframeData& operator+=(float time)
    {
        Time += time;
        
        return *this;
    }
};
```

then we use it in our service code (here I have simplified the code), as we can see, if we directly use `HandlePerframeData(data);`, it won't be converted to `float` because the `HandlePerframeData() fucntion` can accept both `float` and `PerFrameData`, meaning if we pass a `PerFrameData object` to it, it will directly accept it but not convert it to `float`

```c++
void HandlePerframeData(std::variant<float, PerFrameData> data)
{
    int index = data.index();
    
    if (index == 0)
    	std::cout << "float: " << std::get<float>(data) << std::endl;
    else if (index == 1)
    	std::cout << "PerframeData: " << std::get<PerframeData>(data) << std::endl;
}


int main()
{
    PerFrameData data(1);
    HandlePerframeData(data);  // PerframeData: 1
    HandlePerframeData((float)data);  // float: 1
}
```

the best approach is to pass `data.Time` to explicit show that we want to handle the  `member variable Time`

```c++
int main()
{
    PerFrameData data(1);
    HandlePerframeData(data.Time);  // float: 1
}
```

### 3. summary

`conversion operators` can make code cleaner but may make code less clear, so on the fence

