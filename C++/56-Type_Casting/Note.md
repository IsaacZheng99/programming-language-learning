## 56. Type Casting

**Knowledge Points**: `C style type casting`, `C++ style type casting: static_cast<>, dynamic_cast<>, reinterpret_cast<>, const_cast<>`

### 1. C style type casting

1. **implicit and explicit conversion**: 

    ```c++
    int main()
    {
        double a = 5.5;
        int b = a;  // implicit conversion
        int c = (int)a;  // "C style" explicit conversion
        std::cout << b << std::endl;  // 5
        std::cout << c << std::endl;  // 5
    }
    ```

2. **implicit and explicit conversion at the same time**:

    ```c++
    int main()
    {
        double a = 5.5;
        double b = (int)a + 5.3;  // implicit and explicit conversion at the same time
        std::cout << b << std::endl;  // 10.3
        double c = (int)(a + 5.3); 
        std::cout << c << std::endl;  // 10
    }
    ```

3. **C++ style type casting: static_cast**: 

    ```c++
    int main()
    {
        double a = 5.5;
        double b = static_cast<int>(a) + 5.3;  // "C++"-style cast
        std::cout << b << std::endl;  // 10.3
    }
    ```

### 2. C++ style type casting

There are four kinds of `C++` style casts and they do **not** do anything that `C` style casts can **not** do.

The benefit of these `C++` style casts is that it's more **readable** than the `C` style casts and it will do some `compiling time checking` and `runtime checking`, and we can also **search for** them in the code base, e.g., we can simply search the word `static_cast` to check it, but for `C` style cast, we can't because they are all in the same form, besides they can help us reduce the errors of `type incompatible`

1. **static_cast<>**: 

    the most generic way usually used for base data type conversion, parent class pointer/reference and subclass pointer/reference

    here we have a parent class and two subclasses

    ```c++
    class Base
    {
    public:
        Base() {}
        virtual ~Base() {}
    }
    
    class Derived : public Base
    {
    public:
        Derived() {}
        ~Derived() {}
    }
    
    class AnotherClass : public Base
    {
    public:
        AnotherClass() {}
        ~AnotherClass() {}
    }
    ```

    1. we can use `static_cast` to cast downwards: 

        `static_cast` doesn't do runtime checking, so we need to make it safe by ourselves

        ```c++
        int main()
        {
            Base* base = new Base();
            Derived* derived = static_cast<Derived*>(base);
            AnotherClass anotherClass = static_cast<anotherClass*>(base);  // Not safe!
        }
        ```

    2. `static_cast` can do compiling time checking: 

        ```c++
        int main()
        {
            Derived* derived = new Derived();
            AnotherClass anotherClass = static_cast<anotherClass*>(derived);  // Wrong! compile error
        }
        ```

2. **dynamic_cast<>**: 

    `dynamic_cast` depends on the `RTTI`, which is implemented by the `v table`, so it only applies to the `classes` containing `virtual function`

    ```c++
    int main()
    {
        Derived* derived = new Derived();
        
        Base* base = derived;
        
        Derived* de = dynamic_cast<Derived*>(base);
        AnotherClass* ac = dynamic_cast<AnotherClass*>(base);
        if (de)
            std::cout << "Derived!" << std::endl;  // Derived!
        if (!ac)
            std::cout << "Not AnotherClass!" << std::endl;  // Not AnotherClass!
    }
    ```

3. **reinterpret_cast<>**: 

    `reinterpret_cast` is a low-level conversion which can be used for conversion between irrelevant types, just like `type punning`

    ```c++
    int main()
    {
        double a = 5.5;
       	AnotherClass* b = reinterpret_cast<AnotherClass*>(&a);
    }
    ```

4. **const_cast<>**: 

    `const_cast` doesn't do type conversion, and it's usually used for adding `const` and sometimes for deleting `const`, which is not safe and may case `undefined behaviour` in this case

    1. cast to `const`: 

        ```c++
        int main()
        {
            int a = 1;
            int* ptr1 = &a;
            const int* ptr2 = const_cast<const int*>(ptr1);
        }
        ```

    2. cast to `non-const`: 

        ```c++
        int main()
        {
            const int a = 1;
            const int* ptr1 = &a;
            int* ptr2 = const_cast<int*>(ptr1);
            *ptr2 = 2;
            std::cout << a << std::endl;  // 1 (constant folding optimization)
            std::cout << *ptr1 << std::endl;  // 2
            std::cout << *ptr2 << std::endl;  // 2
            std::cout << ptr1 << std::endl;  // 0000002D55CFF514
            std::cout << ptr2 << std::endl;  // 0000002D55CFF514
        }
        ```

