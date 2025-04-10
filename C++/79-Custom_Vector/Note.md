## 79. Custom Vector

**Knowledge Points**: `std::vector<>`, `custom vector: template, ReAlloc(), PushBack(), operator[], Size(), how to avoid copy, std::move(), EmplaceBack(), delete, PopBack(), Clear(), placement new operator to void move, ::operator delete, ::operator new, manually call the destrutor of the elements`

### 1. std::vector<>

```c++
// std::vector<>
int main()
{
    std::vector<int> vector;
    
    vector.reserve(3);
    
    vector.push_back(1);
    vector.push_back(2);
    
    vector.emplace_back(3);
    
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;
}
```

### 2. custom vector

#### 1. basics: template, ReAlloc(), PushBack(), operator[], and Size()

first of all, we will add some basics for the `custom vector`

```c++
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }  // for simplicity, we allocate storage for 2 elements in advance
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    // in STL, typically there has an "assert" to check the boundaries in the "Debug" mode, here we ignore it for simplicity
    const T& operator[](size_t index) const { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() const { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        // note that this is not we currently need but just a simple check if we are downing the capacity
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = m_Data[i];  // if we want to use "memcpy()" here, we need to make sure that the "copy constructor" of the element is called correctly because there maybe have something like "deep copy"
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};


template<typename T>
void PrintVector(const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[i] << std::endl;
    
    std::cout << "----------" << std::endl;
}

int main()
{
    Vector<std::string> vector;
    
    vector.PushBack("xiaoli");
    vector.PushBack("C++");
    vector.PushBack("Vector");
    
    PrintVector(vector);
}
// outputs: 
// xiaoli
// C++
// Vector
// ----------
```

#### 2. the copy problem

1. here we use a simple `Vertex3D struct` with just three `float` elements to illustrate the **copy** problem of the `custom vector`
2. as the outputs show,  there are a lot of **Copy**s, which is not a severe problem in this case because the `Vertex3D struct` only constains three `float` elements, but in the case of like `std::string`, it will affect the performance

```c++
struct Vertex3D
{
  	float x = 0.0f, y = 0.0f, z = 0.0f;
    
    Vertex3D() {}
    
    Vertex3D(float scalar)
    	: x(scalar), y(scalar), z(scalar) {}
    
    Vertex3D(float x, float y, float z)
    	: x(x), y(y), z(z) {}
    
    Vertex3D(const Vertex3D& other)
        : x(other.x), y(other.y), z(other.z)
    {
        std::cout << "Copy\n";
    }
    
 	Vertex3D(Vertex3D&& other)
        : x(other.x), y(other.y), z(other.z)
    {
        std::cout << "Move\n";
    }
    
    Vertex3D& operator=(const Vertex3D& other)
    {
        std::cout << "operator= Copy\n";
        x = other.x;
        y = other.y;
        z = other.z;
        
        return *this;
    }
    
    Vertex3D& operator=(Vertex3D&& other)
    {
        std::cout << "operator= Move\n";
        x = other.x;
        y = other.y;
        z = other.z;
        
        return *this;
    }
    
    ~Vertex3D()
    {
        std::cout << "Destroyed\n";
    }
};

template<typename T>
void PrintVector(const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[index] << std::endl;
    
    std::cout << "----------" << std::endl;
}

void PrintVector(const Vector<Vertex3D>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[index].x << ", " << vector[index].y << ", " << vector[index].z << std::endl;
    
    std::cout << "----------" << std::endl;
}

int main()
{
    Vector<Vertex3D> vector;
    
    vector.PushBack(Vertex3D(1.0f));
    vector.PushBack(Vertex3D(2, 3, 4));
    vector.PushBack(Vertex3D());
    
    PrintVector(vector);
}
// outputs: 
// opeartor= Copy
// Destroyed
// opeartor= Copy
// Destroyed
// opeartor= Copy
// opeartor= Copy
// Destroyed
// Destroyed
// opeartor= Copy
// Destroyed
// 1, 1, 1
// 2, 3, 4
// 0, 0, 0
// ----------
```

#### 3. add void PushBack(T&& value) to move the temporary value

1. for the `Vertex3D` case, there are two kinds of `copy`, one happens when we `PushBack()` elements and the other happens when we `ReAlloc()` and `copy` the old data to the new data block
2. for the first one, we can directly add a `void PushBack(T&& value) function` to solve it

```c++
// version 3:
// note that the elements we "PushBack()" are all temporaries, so we can add "void PushBack(T&& value)" to "move" them
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    void PushBack(T&& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = std::move(value);  // std::move()
        m_Size++;
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = m_Data[i];
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    vector.PushBack(Vector3(1.0f));
    vector.PushBack(Vector3(2, 3, 4));
    vector.PushBack(Vector3());
    
    PrintVector(vector);
}
// outputs: 
// opeartor= Move
// Destroyed
// opeartor= Move
// Destroyed
// opeartor= Copy
// opeartor= Copy
// Destroyed
// Destroyed
// opeartor= Move
// Destroyed
// 1, 1, 1
// 2, 3, 4
// 0, 0, 0
// ----------
// now we have fixed the "move temporaries", but there are still some "Copy"s when we "ReAlloc()" the "Vector"
```

#### 4. use std::move() in ReAlloc() function

we can also use `std::move` in `ReAlloc() function` to avoid `copy`

```c++
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    void PushBack(T&& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = std::move(value);
        m_Size++;
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            //newBlock[i] = m_Data[i];
            newBlock[i] = std::move(m_Data[i]);  // std::move()
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    vector.PushBack(Vector3(1.0f));
    vector.PushBack(Vector3(2, 3, 4));
    vector.PushBack(Vector3());
    
    PrintVector(vector);
}
// outputs: 
// opeartor= Move
// Destroyed
// opeartor= Move
// Destroyed
// opeartor= Move
// opeartor= Move
// Destroyed
// Destroyed
// opeartor= Move
// Destroyed
// 1, 1, 1
// 2, 3, 4
// 0, 0, 0
// ----------
```

#### 5. add EmplaceBack() function

for `EmplaceBack()`, we just need to give the **parameters** of the `constructor` of the element directly and do the construction right in place in the `Vector` data block rather than in the `main` function, in this case we need to use `variadic template` and `std::forward()` for `perfect forwarding`

```c++
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    void PushBack(T&& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = std::move(value);
        m_Size++;
    }
    
    template<typename...Args>  // variadic template
    T& EmplaceBack(Args&&...args)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = T(std::forward<Args>(args)...);  // "..." means "unpack arguments" and we are constructing "T" right here and std::forward() is for perfect forwarding
        // this will print "operator= Move Destroyed"
        
        return m_Data[m_Size++];
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            //newBlock[i] = m_Data[i];
            newBlock[i] = std::move(m_Data[i]);
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    vector.EmplaceBack(Vector3(1.0f));
    vector.EmplaceBack(Vector3(2, 3, 4));
    vector.EmplaceBack(Vector3());
    
    PrintVector(vector);
}
// outputs: 
// opeartor= Move
// Destroyed
// opeartor= Move
// Destroyed
// opeartor= Move
// opeartor= Move
// Destroyed
// Destroyed
// opeartor= Move
// Destroyed
// 1, 1, 1
// 2, 3, 4
// 0, 0, 0
// ----------
```

#### 6. destructor, pop elements, and clear the vector

```c++
// what about "delete", "pop elements" and "clear the vector"
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    ~Vector()
    {
        delete[] m_Data;  // destructor
    }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    template<typename...Args>
    T& EmplaceBack(Args&&...args)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = T(std::forward<Args>(args)...);
        
        return m_Data[m_Size++];
    }
    
    void PopBack()  // pop elements
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();  // manually call the destructor of the poped element
        }
    }
    
    void Clear()  // clear the vector
    {
		for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        
        m_Size = 0;
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    vector.EmplaceBack(1.0f);
    vector.EmplaceBack(2, 3, 4);
    vector.EmplaceBack(1, 3, 4);
    vector.EmplaceBack();
    PrintVector(vector);
    
    vector.PopBack();
    vector.PopBack();
    PrintVector(vector);
    
    vector.EmplaceBack(5, 2, 0);
    vector.EmplaceBack(1, 7, 9);
    PrintVector(vector);
    
    vector.Clear();
    PrintVector(vector);
    
    vector.EmplaceBack(5, 2, 0);
    vector.EmplaceBack(1, 7, 9);
    PrintVector(vector);
}
// outputs: 
// opeartor= Move
// Destroy
// opeartor= Move
// Destroy
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// opeartor= Move
// Destroy
// opeartor= Move
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// Destroy
// opeartor= Move
// Destroy
// 1, 1, 1
// 2, 3, 4
// 1, 3, 4
// 0, 0, 0
// ----------
// Destroy
// Destroy
// 1, 1, 1
// 2, 3, 4
// ----------
// opeartor= Move
// Destroy
// opeartor= Move
// Destroy
// 1, 1, 1
// 2, 3, 4
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
// Destroy
// Destroy
// ----------
// opeartor= Move
// Destroy
// opeartor= Move
// Destroy
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
// Destroy
// Destroy
// in the "EmplaceBack()" function, although the element is created in the function rather than in the "main()" fucntion, it still needs "Move" and "Destroy", how can we avoid them?
```

#### 7. use placement new operator to avoid move and destroy in EmplaceBack()

in the `EmplaceBack() function`, although the element is created in the `function` rather than in the `main() fucntion`, it still needs `Move` and `Destroy`, we can use `placement new operator` to avoid them

```c++
// placement new operator
template<typename T>
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    ~Vector()
    {
        delete[] m_Data;
    }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    template<typename...Args>
    T& EmplaceBack(Args&&...args)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        //m_Data[m_Size] = T(std::forward<Args>(args)...);
        // we can just construct inside the "m_Data", instead of "Move" and "Destroy" after constructing this object on the stack
        // placement new operator: grab the memory address of this element, which is where the element is supposed to live
        new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
        
        return m_Data[m_Size++];
    }
    
    void PopBack()
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }
    
    void Clear()
    {
		for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        
        m_Size = 0;
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = new T[newCapacity];
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    vector.EmplaceBack(Vector3(1.0f));
    vector.EmplaceBack(Vector3(2, 3, 4));
    vector.EmplaceBack(Vector3(1, 3, 4));
    vector.EmplaceBack(Vector3());
    PrintVector(vector);
    
    vector.PopBack();
    vector.PopBack();
    PrintVector(vector);
    
    vector.EmplaceBack(Vector3(5, 2, 0));
    vector.EmplaceBack(Vector3(1, 7, 9));
    PrintVector(vector);
    
    vector.Clear();
    PrintVector(vector);
    
    vector.EmplaceBack(Vector3(5, 2, 0));
    vector.EmplaceBack(Vector3(1, 7, 9));
    PrintVector(vector);
}
// outputs: 
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// opeartor= Move
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// Destroy
// 1, 1, 1
// 2, 3, 4
// 1, 3, 4
// 0, 0, 0
// ----------
// Destroy
// Destroy
// 1, 1, 1
// 2, 3, 4
// ----------
// 1, 1, 1
// 2, 3, 4
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
// Destroy
// Destroy
// ----------
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
// Destroy
// Destroy
// we can set a breakpoint at here: "new(&m_Data[m_Size]) T(std::forward<Args>(args)...);" and we will see there is no "operator= Move Destroyed" of "EmplaceBack()" anymore and there are only "move" and "destroy" for "ReAlloc()" and "destroy" for "PopBack()" and "Clear()"
```

#### 8. add memory block in Vertex3D class

now we will add `memory block ` in `Vertex3D class` to illustrate the memory allocation case

```c++
struct Vertex3D
{
  	float x = 0.0f, y = 0.0f, z = 0.0f;
    int* m_MemoryBlock = nullptr;  // add a memory block to the "Vertex3D" class
    
    Vertex3D()
    {
        m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed
    }
    
    Vertex3D(float scalar)
    	: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed
	}
    
    Vertex3D(float x, y, z)
    	: x(x), y(y), z(z)
    {
		m_MemoryBlock = new int[5];  // allocate storage for five "int" data and we need to delete it when needed
	}
    
    Vertex3D(const Vertex3D& other) = delete;  // we won't copy in our case
    
 	Vertex3D(Vertex3D&& other)
        : x(other.x), y(other.y), z(other.z)
    {
        std::cout << "Move\n";
            
        m_MemoryBlock = other.m_MemoryBlcok;
		other.m_MemoryBlcok = nullptr;
    }
    
    Vertex3D& operator=(const Vertex3D& other) = delete;  // we won't copy in our case
    
    Vertex3D& operator=(Vertex3D&& other)
    {
        std::cout << "operator= Move\n";
        
        m_MemoryBlock = other.m_MemoryBlcok;
		other.m_MemoryBlcok = nullptr;
        
        x = other.x;
        y = other.y;
        z = other.z;
        
        return *this;
    }
    
    ~Vertex3D()
    {
        std::cout << "Destroyed\n";
        delete[] m_MemoryBlock;  // delete when destructing
    }
};

int main()
{    
    {
	    Vector<Vector3> vector;
        
        vector.EmplaceBack(Vector3(1.0f));
        vector.EmplaceBack(Vector3(2, 3, 4));
        vector.EmplaceBack(Vector3(1, 3, 4));
        vector.EmplaceBack(Vector3());
        PrintVector(vector);

        vector.PopBack();
        vector.PopBack();
        PrintVector(vector);

        vector.EmplaceBack(Vector3(5, 2, 0));
        vector.EmplaceBack(Vector3(1, 7, 9));
        PrintVector(vector);

        vector.Clear();
        PrintVector(vector);

        vector.EmplaceBack(Vector3(5, 2, 0));
        vector.EmplaceBack(Vector3(1, 7, 9));
        PrintVector(vector);
    }
}

// if we debug the code, we will get an "Exception" because we are trying to delete a memory block which has already been deleted: "delete[] m_MemoryBlock;"

// we manually call the "destructor" of the element in the "PopBack()" and "Clear()" functions and when it gets out of the scope, the "destructor" of "Vector" will be called and "delete[] m_Data", which will delete the deleted memory block, so we need to change the way to allocate and deallocate memory of "Vector"
```

#### 9. fix the delete bug

we need to use another version of `new` and `delete` which won't call the `constructor` or `destructor` of the element (note that the change of `new` has business with the change of the `delete`, otherwise it may cause `memory leak`)

```c++
// change the way to allocate and deallocate memory of "Vector"
class Vector
{
public:
    Vector() { ReAlloc(2); }
    
    ~Vector()
    {
        //delete[] m_Data;
        Clear();  // not call "delete[]" but manually call the "destructor" of the existing elements
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }
    
    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        m_Data[m_Size] = value;
        m_Size++;
    }
    
    template<typename...Args>
    T& EmplaceBack(Args&&...args)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(std::max(m_Capacity + m_Capacity / 2, m_Size + 1));
        
        new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
        
        return m_Data[m_Size++];
    }
    
    void PopBack()
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }
    
    void Clear()
    {
		for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        
        m_Size = 0;
    }
    
    const T& operator[](size_t index) { return m_Data[index]; }
    
    T& operator[](size_t index) { return m_Data[index]; }
    
    size_t Size() { return m_Size; }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        //T* newBlock = new T[newCapacity];
        // we don't need to call the "constructor" of the elements here, we just need to allocate enough memory
        // moreover, note that we have changed the way we "delete" the elements, we need to change the way we "allocate", if we still use "T* newBlock = new T[newCapacity]", there will construct some elements that won't be deleted, leading to memory leak
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        	// in fact this is wrong, if we are using "Vector<std::string>", this will cause "Exception" because we didn't call the "constructor" of the element and thus the "std::string _Tidy_deallocate()" function will goes wrong (see more information in "81. Custom Iterator")
        
        //delete[] m_Data;
        for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        // here is same as "~Vector()"
        
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

int main()
{
    Vector<Vector3> vector;
    
    {
        vector.EmplaceBack(Vector3(1.0f));
        vector.EmplaceBack(Vector3(2, 3, 4));
        vector.EmplaceBack(Vector3(1, 3, 4));
        vector.EmplaceBack(Vector3());
        PrintVector(vector);

        vector.PopBack();
        vector.PopBack();
        PrintVector(vector);

        vector.EmplaceBack(Vector3(5, 2, 0));
        vector.EmplaceBack(Vector3(1, 7, 9));
        PrintVector(vector);

        vector.Clear();
        PrintVector(vector);

        vector.EmplaceBack(Vector3(5, 2, 0));
        vector.EmplaceBack(Vector3(1, 7, 9));
        PrintVector(vector);
    }
}
// outputs: 
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// opeartor= Move
// opeartor= Move
// opeartor= Move
// Destroy
// Destroy
// Destroy
// 1, 1, 1
// 2, 3, 4
// 1, 3, 4
// 0, 0, 0
// ----------
// Destroy
// Destroy
// 1, 1, 1
// 2, 3, 4
// ----------
// 1, 1, 1
// 2, 3, 4
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
// Destroy
// Destroy
// ----------
// 5, 2, 0
// 1, 7, 9
// ----------
// Destroy
// Destroy
```

### 3. TODO

`TODO`: `std::vector<>::erase() function`, remove element, add or pop element in the middle, iterator of the container

