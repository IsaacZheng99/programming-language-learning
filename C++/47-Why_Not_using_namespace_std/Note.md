## 47. Why not "using namespace std"

**Knowledge Points**: `how to "using namespace": write std::, not in header files, use in the smallest possible scope`

### 1. some examples

1. distinguish your own `functions` fron the `std functions`: 

    ```c++
    void ForEach() {}
    void for_each() {}
    void find_if() {}
    
    int main()
    {
        ForEach();
        for_each();
        find_if();
        std::find_if();  // How to distinguish if there is no "std::" ?
    }
    ```

2. distinguish your own `containers` fron the `std containers`: 

    ```c++
    int main()
    {
        std::vector<int> v1;
        eastl::vector<int> v2;
    
        vector<int> v3;  // Which namespace? Maybe we need to check the "using namespace" code which is far away.
    }
    ```

3. silent `runtime error`: 

    ```c++
    namespace apple {
      
        void print(const std::string& text)
        {
        	std::cout << text << std::endl;
        }
    }
    
    namespace orange {
      
        void print(const char* text)
        {
            std::string temp = text;
            std::reverse(temp.begin(), temp.end());
            std::cout << temp << std::endl;
        }
    }
    
    using namespace apple;
    using namespace orange;
    
    int main()
    {
        print("Hello");  // olleH
        print(std::string("Hello"));  // Hello
    	// it can run successfully but it is in fact a kind of silent runtime error
    }
    ```

### 2. how to "using namespace"

1. write `std::` prefix can help us tell that they are from the `C++ standard library` rather than defined by ourselves
2. **never** `using namespace` in `header files` because you can't predict where this `header file` wiil be included
3. you can `using namespace` in the **smallest** possible scope