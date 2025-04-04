## 71. Track Allocation and Deallocation of Memory

**Knowledge Points**: `overreide operator new and operator delete`, `add breakpoint in operator new and operator delete`

### 1. memory management

1. for the case of game engine, we can set a `breakpoint` in the `operator new()` function and trace exactly where those allocations are coming from while your game loop is running
2. you can write a `memory arena` (a big memory block which is allocated once and assigns small pieces of itself o manually manage the memory) to manually allocate

### 2. an example

put a `breakpoint` in the `operator new()` and `operator delete()` `functions` and you will see exactly where it gets called

```c++
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    
    return malloc(size);
}

void operator delete(void* memory, size_t size)  // add the "size" parameter to override for more information
{
    std::cout << "Freeing " << size << " bytes\n";
    
    free(memory);
}

struct Object
{
    int x, y, z;
}

int main()
{
    {
    	std::unique_ptr<Object> obj = std::make_unique<Object>();
    }
    
	std::string name = "xiaoli";
}
// outputs:
// Allocating 12 bytes
// Freeing 12 bytes
// Allocating 16 bytes
// Freeing 16 bytes
```

### 3. a custom allocation tracker

there are also some tools that can do this

```c++
struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;
    
    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
}

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;
    
    free(memory);
}

struct Obj
{
	int x, y, z;  
};

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

int main()
{
    PrintMemoryUsage();
    
    std::string string = "xiaoli";
    
    PrintMemoryUsage();
    
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
    	PrintMemoryUsage();
    }
    
    PrintMemoryUsage();
}
// outputs: 
// Memory Usage: 0 bytes
// Memory Usage: 16 bytes
// Memory Usage: 28 bytes
// Memory Usage: 16 bytes
```



