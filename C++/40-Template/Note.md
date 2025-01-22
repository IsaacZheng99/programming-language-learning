## 40. Template

**Knowledge Points**: `template`, `what can template do`, `template and overload`, `template parameter`, `when to use template`

### 1. what can template do

a `template` typically allows you to define a `template` that will be compiled by your usage if that makes sense, meaning the compiler writes code for you

### 2. template and overload

we can make a function accept different `types` of parameter by overloading it but this will lead to code duplication, `template` can help avoid the duplication

### 3. template parameter

here we use `typename` as the `type` of `template parameter` and `T` as a name (we can also use `class T`, which is the same in this case but `typenama` makes more sense as we can simply use `primitive type` like `int`, which is not a `class`, but if we use `class`, we can also use the `primitive type` `int`, so there is ambiguity for `class`)

```c++
template<typename T>
void Print(T value)  // this is not a real function and it gets created when we actually call it and when we call it, based on how we call it with what types, it actually gets created and compiled as the source code
// if there are "Print(5);" and "Print(5.5f);", it will create two versions of this function: "void Print(int value)" and "void Print(float value)"
{
	std::cout << value << std::endl;
}

int main()
{
    Print(5);
    Print<int>(5);  // we don't have to specify "<int>" if it can be worked out based on the parameter "5"

    Print("Hello");
    Print<std::strings>("Hello");
    Print<std::string>(1);  // Wrong!

    Print(5.5f);
}
```

### 4. template in a class

1. **template an integer**: 

    ```c++
    // in this case, when we create an array "Array<5> array;", a version of the "Array" class gets created which replaces "N" with 5
    template<int N>
    class Array
    {
    private:
    	int array[N];
    public:
    	int GetSize() const { return N; }
    };
    
    int main()
    {
        Array<5> array;
        std::cout << array.GetSize() << std::endl;  // 5
    }
    ```

2. **template the data type**: 

    ```c++
    // this is a sort of "meta programming" in "C++", instead of actually programming what our code does at runtime, we are kind of programming what the compiler will actually do during the compile time
    template<typename T, int N>
    class Array
    {
    private:
    	T array[N];
    public:
    	int GetSize() const { return N; }
    };
    
    int main()
    {
        Array<std::string, 50> array;
        std::cout << array.GetSize() << std::endl;
    }
    ```

### 5. when to use template

use `template` in a system where you need to handle different `types` of data under the **same logic**, like `logging system` where you want to log many different types of information, or a `buffer` which you want to store different types of data, but when it becomes difficult to read because there are too many `templates`, **stop** using it