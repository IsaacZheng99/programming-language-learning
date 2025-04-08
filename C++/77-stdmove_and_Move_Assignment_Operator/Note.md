## 77. std::move and Move Assignment Operator

**Knowledge Points**: `std::move`, `move constructor`, `move assignment operator`

### 1. when does move assignment operator get called

when we want to `move` an object into an **exsiting** object

### 2. an example

here we use the customized `String class` to illustrate `move`

#### 1. explicitly cast: (String&&)

if we want to use the `move constructor`, we need to make the `string variable` become a temporary value, i.e., `String dest = (String&&)string;`

```c++
class String
{
public:
    String() = default;
    
    String(const char* string)
    {
        printf("Created\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }
    
    String(const String& other)
    {
        printf("Copied\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }
    
    String(String&& other) noexcept
    {
        printf("Moved\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        
        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    
    ~String()
    {
        printf("Destroyed\n");
        delete[] m_Data;
    }
    
    void Print()
    {
  		for (uint32_t i = 0; i < m_Size; i++)
            printf("%c", m_Data[i]);
        
        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

int main()
{
    String string = "Hello";
    String dest = (String&&)string;
    //String dest((String&&)string);
}
// outputs: 
// Created
// Moved
// Destroyed
// Destroyed
```

#### 2. std::move()

`std::move()` is called when we want to convert an `object` to be a **temporary**

```c++
// in "2.1" we need to know the type, but sometimes we will use auto and in this case it won't work, so we use "std::move", which can help you convert an object to be a temporary and is more elegant
int main()
{
    String string = "Hello";
    // we are creating new objects by the move constructor and this is not move assignment operation
    String dest = std::move(string);
    //String dest(std::move(string));
}
// outputs: 
// Created
// Moved
// Destroyed
// Destroyed
```

#### 3. move assignment operator

the assignment operator only gets called when we actually assign a variable into an existing variable, so in the former case it's the `move constructor` gets called

```c++
class String
{
public:
    String() = default;
    
    String(const char* string)
    {
        printf("Created\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }
    
    String(const String& other)
    {
        printf("Copied\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }
    
    String(String&& other) noexcept
    {
        printf("Moved\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        
        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    
    String& operator=(String&& other) noexcept
    {
        printf("Move Assignment\n");
        delete[] m_Data;  // Important! remember delete the current data because if don't do this, these data will be wild
        
        if (this != &other)  // remember not to assign it with itself because firstly you assign the same data and secondly you need to "delete[] m_Data" at first, meaning you will assign deleted data by "m_Data = other.m_Data;", which is unsafe
        {
            m_Size = other.m_Size;
        	m_Data = other.m_Data;
            
            other.m_size = 0;
            other.m_Data = nullptr;
        }
        
        return *this;
    }
    
    ~String()
    {
        printf("Destroyed\n");
        delete[] m_Data;
    }
    
    void Print()
    {
  		for (uint32_t i = 0; i < m_Size; i++)
            printf("%c", m_Data[i]);
        
        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

int main()
{
    String string1 = "123";
    String string2 = "456";
    string1.Print();
    string2.Print();

    string2 = std::move(string1);  // move assignment operator
	string1.Print();
    string2.Print();
    
}
// Created
// Created
// 123
// 456
// Move Assignment
// 
// 123
// Destroyed
// Destroyed
// note that the second "string1.Print();" output nothing because "string1.m_Data" has been set to "nullptr"
```

### 3. summary

1. I personally think there are three keys in the `move assignment operator`: 

    1. we need to `delete` the current data

    2. we need to `move` the resource of the other data to the current data

    3. we need to "clear" the members of the other data

2. `The Rule of Third` and `The Rule of Fifth`

3. when called `move assignment operator` and when called `move constructor`

    ```c++
    String string1 = "1";
    String string2 = "2";
    string2 = std::move(string1);  // this is same as string2.operator=(std::move(string1))
    
    String string3 = "3";
    String string4 = string3;  // here we can't use string4.operator=() because we can't call the non-static function without an instantiated object and we are indeed constructing a new object
    ```

