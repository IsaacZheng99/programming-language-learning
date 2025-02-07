## 50. Timing

**Knowledge Points**: `some std apis: using namespace std::literals::chrono_literals, std::chrono::high_resolution_clock::now(), std::chrono::duration<float>`, `custom timer`

### 1. some std apis

`using namespace std::literals::chrono_literals`

`std::chrono::high_resolution_clock::now()`

`std::chrono::duration<float>`

```c++
int main()
{
    using namespace std::literals::chrono_literals;

    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s" << std::endl;  // 1.0073s
}
```

### 2. an example

**Demand**: we want to time two `functions` to compare the speeds of `std::endl` and `\n` (try to change the `Solution Platforms` to check the results)

```c++
struct Timer
{
    std::chrono::steady_clock::time_point start, end;
    std::chrono:duration<float> duration;

    Timer()
    {
    	start = std::chrono::high_resolution_clock::now();  // similar with scoped pointer
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = start - end;

        float ms = duration.count() * 1000.0f;
        std::cout << ms << "ms" << std::endl;
    }
}

void Function1()
{
    Timer timer;

    for (int i = 0; i < 100; i++)
    {
    	std::cout << "Hello" << std::endl;
    }
}

void Function2()
{
    Timer timer;

    for (int i = 0; i < 100; i++)
    {
    	std::cout << "Hello\n";
    }
}

int main()
{
    Function1();
    Function2();

    std::cin.get();
}
```

