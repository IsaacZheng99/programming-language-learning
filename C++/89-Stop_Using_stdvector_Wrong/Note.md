## 89. Stop Using std::vector<> Wrong

**Knowledge Points**: `std::vector<> vs. std::array<>`, `push_back() vs. emplace_back()`, `allocation`,  `copy`, `move`

### 1. the metric to evaluate

1. how to determine whether we are using `std::vector<>` correctly? the answer is **performance**
2. without a doubt that the `simple array` in programming is the **most** used data structure, here we are talking about a sequence if elements of any defined or variable size that are stored **contiguously in memory** and the importance is how the data are structured in the memory
3. superficially, the biggest difference between `std::array<>` and `std::vector<>` is resizability, but internally the most critical difference is that `std::array<>` is stored on the `stack`, while `std::vector<>` is stored on the `heap` and `heap` is slower than `stack`, therefore even if you could use `std::vector<>` anywhere where you could use `std::array<>`, you should always prioririze to use `std::array<>`, which is faster to both allocate and use

### 2. some examples

#### 1. fixed count of elements

```c++
struct Color
{
    int x, y, z;
};

const Color RED = {1, 2, 3};
const Color YELLOW = {1, 2, 4};
const Color BLUE = {1, 2, 5};

std::vector<Color> GetAllColors1()
{
    return {RED, YELLOW, BLUE};
}

std::array<Color, 3> GetAllColors2()
{
    return {RED, YELLOW, BLUE};
}
```

#### 2. allocation for std::vector<>

we have a simple example and we can check the allocation time (note that we can set a `checkpoint` inside the `operator new()` and see exactly which line of the code leads to the allocation)

```c++
static int s_AllocationCount = 0;

void *operator new(size_t size)
{
    std::cout << "Allocated " << size << " bytes\n";
    s_AllocationCount++;
    return malloc(size;)
}

struct Data
{
    int Value = 0;
    
    Data() = default;
    
    Data(int value)
        : Value(value) {}
};

static void PrintVector(std::vector<Data> vector)
{
    std::cout << "Size: " << vector.size() << std:endl;
    
    if (vector.empty())
        return;
    
    std::cout << "Elements: { ";
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i].Value;
        if (i < vector.size() - 1)
            std::cout << ", ";
    }
    std::cout << " }\n";
}


int main()
{
    std::vector<Data> vector;
    
    for (int i = 0; i < 5; i++)
        vector.push_back(Data(i));
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
}
// outputs:
// ALlocated 16 bytes
// ALlocated 4 bytes
// ALlocated 8 bytes
// ALlocated 12 bytes
// ALlocated 16 bytes
// ALlocated 24 bytes
// ALlocated 16 bytes
// ALlocated 20 bytes
// Size: 5
// Elements: { 0, 1, 2, 3, 4 }
// 8 allocations
```

if we run this code in the `Release` mode, there still has `6` allocations, but in fact if we still use `std::vector<>` in this case, we can just use `1` allocation in the `Realeas` mode and `2` allocations in the `Debug` mode

##### 1. don't copy std::vector<> unless we need to

now there are `6` allocations in the `Debug` mode and `5` allocations in the `Release` mode

```c++
static void PrintVector(const std::vector<Data>& vector)
{
    std::cout << "Size: " << vector.size() << std:endl;
    
    if (vector.empty())
        return;
    
    std::cout << "Elements: { ";
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i].Value;
        if (i < vector.size() - 1)
            std::cout << ", ";
    }
    std::cout << " }\n";
}
```

##### 2. estimate the maximum size if we can

now there are `2` allocations in the `Debug` mode and `1` allocation in the `Release` mode

```c++
int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i = 0; i < 5; i++)
        vector.push_back(Data(i));
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
}
```

we can also use `resize` or `std::vector<Data> vector(5);`, but in these two cases there will call the `default constructor` of `Data` many times, therefore `reserve()` is preferred

```c++
int main()
{
    std::vector<Data> vector;
    vector.resize(5);
    
    for (int i = 0; i < 5; i++)
        vector[i] = Data(i);
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
}
```

```c++
int main()
{
    std::vector<Data> vector(5);
    
    for (int i = 0; i < 5; i++)
        vector[i] = Data(i);
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
}
```

##### 3. the copy problem

now we have `5` copies and if we go back to the initial code, there will have `20` copies

```c++
static int s_CopyCount = 0;

struct Data
{
    int Value = 0;
    
    Data() = default;
    
    Data(int value)
        : Value(value) {}
    
    Data(const Data& other)
        : Value(other.Value)
    {
    	std::cout << "Copied Data\n";
        s_CopyCount++;
    }
};


int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i = 0; i < 5; i++)
        vector.push_back(Data(i));
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
    std::cout << s_CopyCount << " copies\n";
}
// outputs:
// ALlocated 16 bytes
// ALlocated 20 bytes
// Copied Data
// Copied Data
// Copied Data
// Copied Data
// Copied Data
// Size: 5
// Elements: { 0, 1, 2, 3, 4 }
// 2 allocations
// 5 copies
```

we can use `emplace_back()` to solve this

```c++
int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i = 0; i < 5; i++)
        vector.emplace_back(i);  // just pass the arguments for construction
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
    std::cout << s_CopyCount << " copies\n";
}
// outputs:
// ALlocated 16 bytes
// ALlocated 20 bytes
// Size: 5
// Elements: { 0, 1, 2, 3, 4 }
// 2 allocations
// 0 copies
```

##### 4. the move problem

```c++
static int s_MoveCount = 0;

struct Data
{
    int Value = 0;
    
    Data() = default;
    
    Data(int value)
        : Value(value) {}
    
    Data(const Data& other)
        : Value(other.Value)
    {
    	std::cout << "Copied Data\n";
        s_CopyCount++;
    }
    
    Data(Data&& other)
        : Value(other.Value)
    {
    	std::cout << "Moved Data\n";
        s_MoveCount++;
    }
};


int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i = 0; i < 5; i++)
        vector.push_back(Data(i));
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
    std::cout << s_CopyCount << " copies\n";
    std::cout << s_MoveCount << " moves\n";
}
// outputs:
// ALlocated 16 bytes
// ALlocated 20 bytes
// Moved Data
// Moved Data
// Moved Data
// Moved Data
// Moved Data
// Size: 5
// Elements: { 0, 1, 2, 3, 4 }
// 2 allocations
// 0 copies
// 5 moves
```

use `emplace_back()`

```c++
int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i = 0; i < 5; i++)
        vector.emplace_back(i);
    
    PrintVector(vector);
    
    std::cout << s_AllocationCount << " allocatoins\n";
    std::cout << s_CopyCount << " copies\n";
    std::cout << s_MoveCount << " moves\n";
}
// outputs:
// ALlocated 16 bytes
// ALlocated 20 bytes
// Size: 5
// Elements: { 0, 1, 2, 3, 4 }
// 2 allocations
// 0 copies
// 0 moves
```

### 3. summaray

1. **don't** use `std::vector<>` if we can use `std::array<>` (for the second case above, we can also directly use `std::array<Data, 5>` and there has `move`, but it doesn't matter)
2. **allocate up-front** if we know the estimated maximum size, or at first the size is `1000` and latter is `3000`, in this case we can **manually** resize it
3. use `emplace_back()` to avoid `copy` and `move` (note that if you use `vector.emplace_back(Data(i))`, it will work in the same way as `vector.push_back(Data(i))`, so use it in the right way: `vector.emplace_back(i)`)

