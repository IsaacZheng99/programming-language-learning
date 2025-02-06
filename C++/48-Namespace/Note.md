## 48. Namespace

**Knowledge Points**: `naming conflicts`, `using`, `alias`, `nested namespace`, `write codes in namespace if this is a serious project`

### 1. what can namespace do

1. the primary purpose of `namespace` is to avoid `naming conflicts`
2. there is no `namespace` in `C` , so we usually add some prefix to distinguish, e.g., `"glfw" of glfwInit()`, `"gl" of glBegin()`

### 2. some examples

we have two `namespaces`: 

```c++
namespace apple {
  
    void print(const std::string& text)
    {
    	std::cout << text << std::endl;
    }

    void print_again()
    {
        std::cout << "print again" << std::endl;
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
```

1. `using` a `function` in a `namespace`: 

    ```c++
    int main()
    {
        using apple::print();
        print("Hello");  // Hello
        apple::print_again();  // print again
        // print_again();  // Wrong!
    }
    ```

2. create an `alias` for a `namespace`: 

    ```c++
    int main()
    {
        namespace a = apple;  // this is useful when you have nested namespace
        a::print("Hello");  // Hello
        apple::print("Hello");  // Hello
    }
    ```

3. `nested namespace`: 

    ```c++
    namespace watermelon {
        
        namespace functions {
            
            void print(const std::string& text)
            {
                std::cout << text << std::endl;
            }
    
            void print_again()
            {
                std::cout << "print again" << std::endl;
            }
        }
    }
    ```

    ```c++
    int main()
    {
        {
            watermelon::functions::print("Hello");  // Hello
        }
        
        {
            using namespace watermelon::functions;
        	print("Hello");  // Hello
        }
        
        {
            using namespace watermelon;
            using namespace functions;
            print("Hello");  // Hello
        }
        
        {
            namespace wf = apple::functions;  // alias
        	wf::print("Hello");   // Hello
        }
    }
    ```

### 3. Summarization

if it is a serious project, write codes in `namespace`, e.g., the codes in  `C++` standard libraries are all in `namespace std`

