## 37. Library

### 1. Static Linking

#### 1. what a library contains

`library` usually constains two parts: `include` and `library`

1. the `include` directory has a bunch of `header files` that we need to use so we can actually use functions that are in the `pre-built binaries`
2. the `library` directory has those `pre-built binaries`

#### 2. static library and dynamic library

1. `static library` means the `library` actually gets basically put into your executable file (e.g., `.exe` file in `Windows`), which is faster and usually the better choice
2. `dynamic library` gets linked at runtime

#### 3. GLFW library

1. download the `pre-compiled binaries` of [GLFW](https://www.glfw.org/) (here we directly use the `pre-compiled binaries` instead of compiling the source by ourself, there will be a chapter about creating our own library later)

2. use `glfw3.lib` as an example, which is a `staic library`

    ```c++
    #include <GLFW/glfw3.h>  // we need to "include"
    
    int main()
    {
      int a = glfwInit();
      std::cout << a << std::endl;  // 1
      
      std::cin.get();
    }
    ```



