## 81. Custom Iterator

**Knowledge Points**: `custom iterator: template, pointer, begin(), end(), operators, the ReAlloc() bug`, `check the custom classes with different kinds of data`

### 1. review the iterator

`iterator` is like keeping track of a `pointer` and `iterating` something is like **increamenting** the `pointer` until you reach to the end

### 2. custom iterator

we are going to add the `custom iterator` for the `custom vector` we have implemented in `79. Custom Vector`

#### 1. normal traverse

```c++
int main()
{
    Vector<int> values;
    values.EmplaceBack(1);
    values.EmplaceBack(2);
    values.EmplaceBack(3);
    values.EmplaceBack(4);
    values.EmplaceBack(5);
    
    std::cout << "Not using iterator:\n";
    for (int i = 0; i < values.Size(); i++)
        std::cout << values[i] << std::endl;
}
```

#### 2. add iterator basics: template, pointer, begin(), and end()

the `custom iterator` basically needs a `pointer` to know where it is currently pointing

```c++
template <typename Vector>  // the template "Vector" means the iterator is used for some kind of "vector"
class VectorIterator  // iterator class
{
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    VectorIterator(PointerType ptr)
        : m_Ptr(ptr) {}
private:
    PointerType m_Ptr;
};

class Vector
{
public:
    // same implementation with "std::vector<>"
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;
public:
    Vector() { ReAlloc(2); }
    
    ~Vector()
    {
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }
    
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
    
    Iterator begin()  // "begin()" and "end()" used for "range_based for loop"
    {
        return Iterator(m_Data);
    }
    
    Iterator end()
    {
        return Iterator(m_Data + m_Size);
    }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = (T&)::operator new(newCapacity * sizeof(T));
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = std::move(m_Data[i]);
        
        for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};
```

#### 3. add operators to manipulate custom iterator

now we need some `operators` to manipulate the `custom iterator`

```c++
template <typename Vector>
class VectorIterator
{
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    VectorIterator(PointerType ptr)
        : m_Ptr(ptr) {}
    
    VectorIterator& operator++()  // prefix ++
    {
        m_Ptr++;
        return *this;
    }
    
    VectorIterator operator++(int)  // postfix ++
    {
        VectorIterator iterator = *this;  // this is a cheap "copy" in our case because there is only a pointer "m_Ptr"
        ++(*this); // call "VectorIterator& operator++()"
        return iterator;
    }
    
    VectorIterator& operator--()  // prefix --
    {
        m_Ptr--;
        return *this;
    }
    
    VectorIterator operator--(int)  // postfix --
    {
        VectorIterator iterator = *this;
        --(*this); // call "VectorIterator& operator--()"
        return iterator;
    }
    
    ReferenceType operatorp[](int index)
    {
        return *(m_Ptr + index);
        // "return m_Ptr[index];" is also fine
    }
    
    PointerType operator->()
    {
        return m_Ptr;  // return whatever the position we are at has
    }
    
    ReferenceType operator*()
    {
        return *m_Ptr;
    }
    
    bool operator==(const VectorIterator& other) const
    {
        return m_Ptr == other.m_Ptr;
    }
    
    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other);  // call "bool operator==(const VectorIterator& other) const"， note that "*this" won't call "operator*()" and it just gets the current object
    }
private:
    PointerType m_Ptr;
};


int main()
{
    Vector<int> values;
    values.EmplaceBack(1);
    values.EmplaceBack(2);
    values.EmplaceBack(3);
    values.EmplaceBack(4);
    values.EmplaceBack(5);
    
    std::cout << "Range-based for loop:\n";
    for (int value : values)
        std::cout << value << std::endl;
    
    std::cout << "Iterator:\n";
    for (Vector<int>::Iterator it = values.begin(); it != values.end(); it++)
        std::cout << *it << std::endl;
}
// in our casem what we need to do is just to "increment the pointer", e.g., if you want to traverse a map or a tree, you just need to change the code of "operator++"
```

#### 4. fix the ReAlloc() bug

1. when testing `Vector<std::string>`, we find that there is a problem in the `ReAlloc()` function
2. therefore, don't forget test with other `primitive classes` and `custom classes` when you complete a `custom class`

```c++

class Vector
{
public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;
public:
    Vector() { ReAlloc(2); }
    
    ~Vector()
    {
        Clear();
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
    
    Iterator begin()
    {
        return Iterator(m_Data);
    }
    
    Iterator end()
    {
        return Iterator(m_Data + m_Size);
    }
private:
    void ReAlloc(size_t newCapacity)
    {
        // 1. allocate a new block of memory
        // 2. copy/move old elements into the new block
        // 3. delete the old block
        
        T* newBlock = (T&)::operator new(newCapacity * sizeof(T));
        
        if (newCapacity < m_Size)
            m_Size = newCapacity;
        
        for (size_t i = 0; i < m_Size; i++)
            //newBlock[i] = std::move(m_Data[i]);  // Wrong! if we are using "Vector<std::string>", this will cause exception because we didn't call the "constructor" of the element and thus the "std::string _Tidy_deallocate()" will go wrong
            new(&newBlock[i]) T(std::move(m_Data[i]));  // placement new operator
        	
        
        for (size_t i = 0; i < m_Size; i++)
            m_Data[i].~T();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
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
    Vector<int> values;
    values.EmplaceBack("1");
    values.EmplaceBack("2");
    values.EmplaceBack("3");
    values.EmplaceBack("4");
    values.EmplaceBack("xiaoli");
    
    std::cout << "Range-based for loop:\n";
    for (int value : values)
        std::cout << values[i] << std::endl;
    
    std::cout << "Iterator:\n";
    for (Vector<int>::Iterator it = values.begin(); it != values.end(); it++)
        std::cout << *it << std::endl;
}
```

### 3. TODO

`TODO`: `custom iterator` for `custom array`, check the `iterator` of other class, e.g., `unordered_map`

