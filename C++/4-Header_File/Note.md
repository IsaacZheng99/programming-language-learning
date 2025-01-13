## 4. Header File

**Knowledge Points**: `#pragma once`, `#ifndef`, `#include <> and #include ""`, `.h in header files`

1. **#pragma once**: 

    ```c++
    #pragma once  // only include this file once, i.e., prevent including a single header file multiple times to a single translation unit
    // e.g., there are two header files "Log.h" and "Common.h" and "Log.h" includes "Common.h", if we include "Common.h" and "Log.h" in "Main.cpp", "Common.h" will be included twice without "#pragma once"
    ```

2. **#ifndef**: 

    ```c++
    // we can also use "#ifndef" to make the contents of a single header file be included only once, we call it "header guard"
    
    #ifndef _LOG_H
    #define _LOG_H
    
    void Log();
    
    #endif
    ```

3. **<> and "" (angle brackets and quotes) in #include**

    ```c++
    #include <iostream>  // if the included file is inside one of the include paths
    #include "Log.h"  // usually used to include files that are relative to the current file, if this file can't be relatively found, it will look for the compiler include paths
    
    // if this file is inside the solution, we will use ""
    // if it is a completely external dependency or external library that we are not compiling with the actual solution, we will use <> to indicate it's external
    
    #include "../Time.h"  // the header file is in the parent directory
    
    #include "iostream"  // this is also fine
    
    #include <Log.h>  // this is wrong!
    
    // the "iostream" header file doesn't have the ".h" extension, this is one way to distinguish the C++ header files from the C header files
    #include <iostream>
    #include <stdlib.h>
    ```

