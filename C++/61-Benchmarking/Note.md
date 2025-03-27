## 61. Benchmarking

**Knowledge Points**:`no extra overhead of benchmarking itself`, `benchmark the right thing`, `benchmark in the right mode`

### 1. attention

1. be careful that the way you measure the performance itself **won't** add overhead

2. make sure that you are `benchmarking` the codes that gets compiled

    if you use a `Timer` to time the time in different modes (`Debug` mode and `Release` mode), you will see that the `assembly codes` are different, the `assembly code` in `Debug` mode is really doing the `add` operation, but in the `Release` mode it's just writing the `2000000`, which doesn't do the `add` operation

    ```c++
    int value = 0;
    for (int i = 0; i < 1000000; i++)
        value += 2;
    ```

### 2. an example

```c++
class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
public:
    Timer()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock:now();
    }
    
    ~Timer()
    {
        Stop();
    }
    
    void Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock:now();
        
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
        
        auto duration = end - start;
        
        double ms = duration * 0.001;
        
        std::cout << duration << "us (" << ms << "ms)\n";
    }
};


int main()
{
    struct Vector2
    {
    	float x, y;  
    };
    
    std::cout << "Make Shared!\n";
    {
        std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); i++)
            sharedPtrs[i] = std::make_shared<Vector2>();
    }
    
    std::cout << "New Shared!\n";
    {
        std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); i++)
            sharedPtrs[i] = std::shared_ptr<Vector2>(new Vector2());
    }
    
    std::cout << "Make Unique!\n";
    {
        std::array<std::unique_ptr<Vector2>, 1000> uniquePtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); i++)
            uniquePtrs[i] = std::make_unique<Vector2>();
    }
}
// "Debug" mode is not good for measuring performance because it does a lot of safety stuffs, which take time and you are not shipping your code in "Debug" mode, so choose the right mode
// in "Release" mode, these three are all much faster than in the "Debug" mode and "make_shared" is faster than "new shared"
```

