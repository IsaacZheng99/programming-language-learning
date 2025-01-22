## 37. Library

**Knowledge Points**: `static linking`, `what a library contains: include and library`, `GLFW`, `dynamic linking`, `static linking vs dynamic linking`, `two versions of dynamic linking`, 

### 1. Static Linking

#### 1. what a library contains

`library` usually constains two parts: `include` and `library`

1. the `include` directory has a bunch of `header files` that we need to use so we can actually use functions that are in the `pre-built binaries`
2. the `library` directory has those `pre-built binaries`

#### 2. static library and dynamic library

1. `static library` means the `library` actually gets basically put into your executable file (e.g., `.exe` file in `Windows`), which is faster and usually the better choice because of `linktime optimization`, `__declspec(dllimport)`
2. `dynamic library` gets linked at runtime

#### 3. GLFW static library

1. **download pre-compiled binaries**: 

    download the `pre-compiled binaries` of [GLFW](https://www.glfw.org/) (here we directly use the `pre-compiled binaries` instead of compiling the source by ourself, there will be a chapter about creating our own library later)

2. **create Dependencies directory**: 

    create a directory called `Dependencies` inside the `solution` directory

3. **put the GLFW library inside the Dependencies directory **: 

    create a directory called `GLFW` inside the `Dependencies` directory and put the `include` and `library` file inside `GLFW` (the concrete file seen in the `Code` part, note that the `32-bit` or `64-bit` `binaries` depends on the `solution platform` and here I use `64-bit`)

4. **give the declaration**: 

    set `Additional Include Directories` in the `project properties`: `$(SolutionDir)\Dependencies\GLFW\include`

5. **link to the actual library**: 

    if you don't `link`, there will have `linking error`: `1 unresolved externals` when you call like `int a = glfwInit();`

    1. set `Additional Library Directories `in the `project properties`: `$(SolutionDir)\Dependencies\GLFW\lib-vc2022`
    2. set `Additional Dependencies` in the `project properties`: `glfw3.lib`

6. **run the program and check the result**: 

    1. use `glfw3.lib` as an example, which is a `staic library`: 

        ```c++
        #include <GLFW/glfw3.h>  // we need to "include"
        
        int main()
        {
            int a = glfwInit();
            std::cout << a << std::endl;  // 1
        
            std::cin.get();
        }
        ```

    2. if we remove the `#include <GLFW/glfw3.h>`: 

        ```c++
        // #include <GLFW/glfw3.h>
        
        int main()
        {
            int a = glfwInit();
            std::cout << a << std::endl;  // Wrong! identidier not found
        
            std::cin.get();
        }
        ```

    3. if we manually add a declaration: 

        **name-mangling**: `glfw` is essentially a `C` library

        ```c++
        // #include <GLFW/glfw3.h>
        int glfwInit();  // add a declaration
        
        int main()
        {
            int a = glfwInit();
            std::cout << a << std::endl;  // Wrong! 1 unresolved externals
            //
        
            std::cin.get();
        }
        ```

    4. add `extern "C"`: 

        ```c++
        // #include <GLFW/glfw3.h>
        extern "C" int glfwInit();
        
        int main()
        {
            int a = glfwInit();
            std::cout << a << std::endl;  // 1
        
            std::cin.get();
        }
        ```

### 2. Dynamic Linking

#### 1. static linking vs dynamic linking

1. `dynamic linking` happens at runtime, `static linking` happens at compile time
2. `static linking` can allow more optimization because the compiler and linker can see more of the picture

#### 2. two versions of dynamic library:

1. "static" dynamic version: we're already **aware** of what functions are in it
2. another version: we want to **arbitrarily** load this library and we don't know what's in it

#### 3. GLFW dynamic library

1. **link to the actual library**: 

    set `Additional Dependencies` in the `project properties`: first remove `glfw3.lib`, then add `glfw3dll.lib`, which is basically a series of `pointers` into the `glfw3.dll` file, so we don't have to retrive the locations of everything at runtime

2. **add the dll file**: 

    copy the `glfw3.dll` file and paste it in the `directory` where the `.exe` file is

3. **run the program and check the result**: 

    ```c++
    #include <GLFW/glfw3.h>  // the header file supports both static linking and dynamic linking
    
    int main()
    {
        int a = glfwInit();
        std::cout << a << std::endl;  // Wrong! 1 unresolved externals
        //
    
        std::cin.get();
    }
    ```

4. **Question**: 

    `GLFWAPI` marco: why no just `__declspec(dllimport)`?

    Answer: we have the `static linking`: `glfw3dll.lib` which helps us do `dynamic linking` `glfw3.dll`, and if we remove `glfw3dll.lib` and use `__declspec(dllimport)`, even though the `functions` are instructed to be imported from a `dll` but we still need `glfw3dll.lib` to resolve the symbols, so we still need `glfw3dll.lib`.

