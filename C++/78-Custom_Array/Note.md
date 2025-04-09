## 78. Custom Array

**Knowledge Points**: `raw array`, `std::array<>`, `custom array: template, Size(), constexpr, operator[], return reference, return const reference, return pointer, return pointer to const`

### 1. raw array

```c++
int main()
{
    int array1[5];
    
    int size = 5;
    int array2[size];  // Wrong! Compiling error. "expression must have a constant value", the size has to be known by the compiler
    // if you want to allocate on the "stack" dynamically (with a runtime value), you can use "alloca()"
    int* array3 = (int*)alloca(size * sizeof(int));
    
    int* heapArray1 = new int[5];
    int* heapArray2 = new int[size];
    
    delete[] heapArray1;
    delete[] heapArray2;
}
```

### 2. std::array<>

```c++
int main()
{
    std::array<int, 5> collection;
    
    int size = collection.size();
    
    for (int value : collection)
        std::cout << value << std::endl;
    
    for (int i = 0; i < collection.size(); i++)
        std::cout << collection[i] << std::endl;
}
```

### 3. custom array

now we are writing the `custom array` based on the source code of `std::array<>`

#### 1. two template arguments and Size() function

first we use `template` to define the `custom array` and we can leverage the benefit of the `template argument`, which takes no storage and is specified at compiling time

```c++
template<typename T, size_t S>
class Array
{
public:
    size_t Size() const { return S; }  // no need of additional storage for "size"
private:
	T m_Data[S];    
};

int main()
{
    Array<int, 5> data;
    
    // leverage the template of the size
    static_assert(data.Size() < 10, "Size is too long!");  // Wrong! Compiling error.
    
    Array<std::string, data.Size()> newArray;  // Wrong! Compiling error.
}
```

#### 2. add constexpr key word

however, the `Size() function` can't be evaluated at compiling time without the `constexpr` key word

```c++
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }
    // "constexpr" makes this function can be evaluated at compiling time 
    // "constexpr" can help a lot, you can see a lot of "constexpr" in the source code
private:
	T m_Data[S];    
};

int main()
{
    Array<int, 5> data;
    
    static_assert(data.Size() < 10, "Size is too long!");
    
    Array<std::string, data.Size()> newArray;
}
```

#### 3. add operator[]

one of the key `function` of the `array` is `operator[]`

```c++
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }
    
    T operator[](size_t index)
    {
        return m_Data[index];
    }
    // problems of the upper implementation:
    // 1. if "T" is "std::string", there will be multiple copy actions
    // 2. we can only read but not assign
    // therefore we want to return a "reference"
private:
	T m_Data[S];    
};

int main()
{
    Array<int, 5> data;
    for (int i = 0; i < data.Size(); i++)
    {
        std::cout << data[i] << std::endl;
        data[i] = 0;  // Wrong! Compiling error.
    }
}
```

#### 4. add reference to the return value of operator[]

now we add reference to the return value of `operator[]` for modifying elements

```c++
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }
    
    // add reference
    T& operator[](size_t index) { return m_Data[index]; }
    // if we have a "const reference: const Array& referenceArray", we can't access "referenceArray[i]" because "no operator[] match", therefore we need another version which returns "const reference"

private:
	T m_Data[S];    
};

int main()
{
    Array<int, 5> data;
    for (int i = 0; i < data.Size(); i++)
    {
        std::cout << data[i] << std::endl;
        data[i] = 0;
    }
    
    const auto& referenceArray = data;
    for (int i = 0; i < referenceArray.Size(); i++)
    {
        std::cout << referenceArray[i] << std::endl;  // Wrong! Compiling error.
        referenceArray[i] = 0;  // Wrong! Compiling error.
    }
}
```

#### 5. add const T& operator[]

now we add another version of `operator[]`

```c++
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    const T& operator[](size_t index) const { return m_Data[index]; }
    // this kind of overloading is permitted as these are class member functions

private:
	T m_Data[S];    
};

int main()
{
    Array<int, 5> data;
    for (int i = 0; i < data.Size(); i++)
    {
        std::cout << data[i] << std::endl;
        data[i] = 0;
    }
    
    const auto& referenceArray = data;
    for (int i = 0; i < referenceArray.Size(); i++)
    {
        std::cout << referenceArray[i] << std::endl;
        referenceArray[i] = 0;  // Wrong! Compiling error.
    }
}
```

#### 6. Data() function to access the data

```c++
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    const T& operator[](size_t index) const { return m_Data[index]; }
    
    T* Data() { return m_Data; }  // access "m_Data"
    
    const T* Data() const { return m_Data; }
private:
	T m_Data[S];
};

int main()
{
    Array<int, 5> data;
    
    memset(data.Data(), 0, data.Size() * sizeof(int));
    // memset(&data[0], 0, data.Size() * sizeof(int));
    
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << std::endl;
    }
    
    const auto& referenceArray = data;
    for (int i = 0; i < referenceArray.Size(); i++)
    {
        std::cout << referenceArray.Data()[i] << std::endl;
    }
}
```

