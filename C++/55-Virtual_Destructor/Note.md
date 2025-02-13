## 55. Virtual Destructor

**Knowledge Points**: `how the constructors and destructors are called when there is a base pointer to derived object`

### 1. why need virtual destructor

`virtual destructor` is very important when you are dealing with `polymerphism`

if you have a series of `subclasses` and all that inheritance, you want reference `class B` as `class A`, which is actually `class B` and then you decide to delete it and you want the `destructor` of `B` to run not `A`

### 2. some examples

1. **the normal case**: 

    for completeness of object creation, the `constructors` of parents will be called and called **first**, because maybe there are some initialization in the parents' `constructors` and they must be executed

    ```c++
    class Base
    {
    public:
        Base() { std::cout << "Base Constructor\n"; }
        ~Base() { std::cout << "Base Destructor\n"; }
    };
    
    class Derived
    {
    public:
        Derived() { std::cout << "Derived Constructor\n"; }
        ~Derived() { std::cout << "Derived Destructor\n"; }
    };
    
    int main()
    {
        Base* base = new Base();
        delete base;
    	std::cout << "----------\n";
        Derived* derived = new Derived();
        delete derived;
    }
    // outputs: 
    // Base Constructor
    // Base Destructor
    // ----------
    // Base Constructor
    // Derived Constructor
    // Derived Destructor
    // Base Destructor
    ```

2. **Base pointer to Derived object**: 

    this may case `memory leak`

    ```c++
    int main()
    {
        Base* poly = new Derived();
        delete poly;
    }
    // outputs: 
    // Base Constructor
    // Derived Constructor
    // Base Destructor
    ```

3. **memory leak**: 

    ```c++
    class Base
    {
    public:
    	Base() { std::cout << "Base Constructor\n"; }
    	~Base() { std::cout << "Base Destructor\n"; }
    };
    
    class Derived
    {
    private:
        int* m_Array;
    public:
        Derived() { m_Array = new int[5]; std::cout << "Derived Constructor\n"; }
        ~Derived() { delete[] m_Array; std::cout << "Derived Destructor\n"; }  // "memory leak" because of no calling "~Derived()"
    };
    
    int main()
    {
        Base* derived = new Derived();
        delete derived;
    }
    // outputs: 
    // Base Constructor
    // Derived Constructor
    // Base Destructor
    ```

4. **virtual destructor of Base**: 

    ```c++
    class Base
    {
    public:
    	Base() { std::cout << "Base Constructor\n"; }
    	virtual ~Base() { std::cout << "Base Destructor\n"; }
    };
    
    class Derived
    {
    private:
        int* m_Array;
    public:
        Derived() { m_Array = new int[5]; std::cout << "Derived Constructor\n"; }
        ~Derived() { delete[] m_Array; std::cout << "Derived Destructor\n"; }  // "memory leak" because of no calling "~Derived()"
    };
    
    int main()
    {
        Base* derived = new Derived();
        delete derived;
    }
    // outputs: 
    // Base Constructor
    // Derived Constructor
    // Derived Destructor
    // Base Destructor
    ```

### 3. when to use virtual destructor

**whenever** you are writing a `class` that might have `subclasses`, you need to **hundred percent** declare your destructor of this `class` as virtual

