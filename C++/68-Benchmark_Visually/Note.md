## 68. Benchmark Visually

**Knwoledge Points**: 

### 1. Chrome Tracing

`url`: `chrome://tracing`

### 2. some examples

#### 1. directly benchmark two functions

we can start with benchmarking two `functions` which run one after another

##### 1. session

first we need to get the profile for each `function` and store the information of these profiles in a file used for `Chrome Tracing` to analyze and here we use a `session` to record the information

```c++
struct ProfileResult  // profile class
{
    std::string Name;
    long long Start, End;
};

struct InstrumentationSession  // session class
{
    std::string Name;
};

class Instrumentor  // handle session, profile, file writing
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
public:
    Instrumentor()
    	: m_CurrentSession(nullptr), m_ProfileCount(0)
	{
	}
    
    void BeginSession(const std::string& name, const std::string& filePath)
    {
        m_OutputStream.open(filePath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession({ name });
    }
    
    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }
    
    void WriteProfile(const ProfileResult& result)
    {
        if (m_ProfileCount++ > 0)  // for each function, we have a profile
            m_OutputStream << ",";
        
        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');  // for "json" format
        
        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":0,";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";
        
        m_OutputStream.flush();
    }
    
    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        
        m_OutputStream.flush();
    }
    
    void WriteFooter()
    {
        m_OutputStream << "]}";
        
        m_OutputStream.flush();
    }
    
    static Instrumentor& Get()
    {
        static Instrumentor* instance = new Instrumentor();
        return *instance;
    }
}
```

##### 2. timer

we need a `timer` to do benchmarking, and as we only record the start and end time of the function and the `timer` is a `scoped timer`, so we can just put `WriteProfile()` in the `timer`

```c++
class InstrumentationTimer
{
private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    bool m_Stopped;
public:
    InstrumentationTimer(const char* name)
        : m_Name(name), m_Stopped(false)
    {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }
    
    ~InstrumentationTimer()
    {
        if (!m_Stopped)
			Stop();
    }
    
    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        
        std::cout << m_Name << ": " << end - start << "us\n";
        
        Instrumentor::Get().WriteProfile({ m_Name, start, end });
        
        m_Stopped = true;
    }
};
```

##### 3. benchmarking

now we are trying to benchmark two `function` and we can get a `.json` for `Chrome Tracing` to analyze

```c++
void Function1()
{
    InstrumentationTimer timer("Function1");
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << i << std::endl;
}

void Function2()
{
    InstrumentationTimer timer("Function2");
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << sqrt(i) << std::endl;
}


int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    Function1();
    Function2();
    Instrumentor::Get().EndSession();
}
```

#### 2. two functions stack-printing-like run

we can write another `function` to call `Function1()` and `Function2()` and in this way we can see a stack-printing-like visual result

```c++
void RunBenchmarks()
{
    InstrumentationTimer timer("RunBenchmarks");
    
    std::cout << "Running Benchmarks...\n";
    
    Function1();
    Function2();
}


int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    RunBenchmarks();
    Instrumentor::Get().EndSession();
}
```

#### 3. use macro to open or close the timer

control the `timer` by `macro` because the `timer` is just for benchmarking and it's not something that we want to run all the time as it will add overhead

```c++
#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)  // "timer##__LINE__" can give different names to these "timers"
#else
#define PROFILE_SCOPE(name)
void Function1()
{
    PROFILE_SCOPE("Function1");
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << i << std::endl;
}

void Function2()
{
    PROFILE_SCOPE("Function2");
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks()
{
    PROFILE_SCOPE("RunBenchmarks");
    
    std::cout << "Running Benchmarks...\n";
    
    Function1();
    Function2();
}


int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    RunBenchmarks();
    Instrumentor::Get().EndSession();
}
```

#### 4. use macro to write the function names automatically

we don't really want to write the `function` name every time we want to use the `timer`, so we can leverage `macro` to do this

```c++
#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
void Function1()
{
    PROFILE_FUNCTION();
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << i << std::endl;
}

void Function2()
{
    PROFILE_FUNCTION();
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks()
{
    PROFILE_FUNCTION();
    
    std::cout << "Running Benchmarks...\n";
    
    Function1();
    Function2();
}


int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    RunBenchmarks();
    Instrumentor::Get().EndSession();
}
```

#### 5. use \_\_FUNCSIG\_\_ to avoid same names of functions

sometimes we may override `functions` and thus we can use `__FUNCSIG__` to distinguish them

```c++
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
void Function1()
{
    PROFILE_FUNCTION();
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << i << std::endl;
}

void Function2()
{
    PROFILE_FUNCTION();
    
    for (int i = 0; i < 1000; i++)
        std::cout << "Hello World #" << sqrt(i) << std::endl;
}

void RunBenchmarks()
{
    PROFILE_FUNCTION();
    
    std::cout << "Running Benchmarks...\n";
    
    Function1();
    Function2();
}


int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    RunBenchmarks();
    Instrumentor::Get().EndSession();
}
// void __cdecl RunBenchmarks(void);
// void __cdecl PrintFunction(int);
// void __cdecl PrintFunction(void);
// "__cdecl" is called "calling convention"
```

#### 6. add a namespace to specify the scope

in a real production enviroment, we need to use `namespace` to include the `functions` sometimes

```c++
#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()

namespace Benchmark {
    
    void RunBenchmarks()
    {
        PROFILE_FUNCTION();

        std::cout << "Running Benchmarks...\n";

        PrintFunction(2);
        PrintFunction();
    }

    void PrintFunction(int value)
    {
        PROFILE_FUNCTION();

        for (int i = 0; i < 1000; i++)
            std::cout << "Hello World #" << (i + value) << std::endl;
    }

    void PrintFunction()
    {
        PROFILE_FUNCTION();

        for (int i = 0; i < 1000; i++)
            std::cout << "Hello World #" << sqrt(i) << std::endl;
    }
}

int main()
{
    Instrumentor::Get().BeginSession("Profile", "src/json/results.json");
    Benchmark::RunBenchmarks();
    Instrumentor::Get().EndSession();
}
// void __cdecl Benchmark::RunBenchmarks(void);
// void __cdecl Benchmark::PrintFunction(int);
// void __cdecl Benchmark::PrintFunction(void);
```





