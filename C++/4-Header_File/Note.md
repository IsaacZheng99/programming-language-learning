## 4. Header File

**Knowledge Points**:

1. `make one single header file be included only once: #pragma once, header guard: #ifndef`
2. `#include <> and #include ""`
3. `.h in header files`

### 1. How to make one single header file be included only once

#### 1. #pragma once

1. Only include the current file once, i.e., prevent including a single `header file` multiple times to a single `translation unit`.
2. For example, there are two `header files` `Log.h` and `Common.h` and `Log.h` has included `Common.h`, if we include both `Common.h` and `Log.h` in `Main.cpp`, `Common.h` will be included twice without `#pragma once`.

#### 2. #ifndef

We can also use `#ifndef` to make the contents of a single header file be included only once, we call it `header guard`.

```c++
#ifndef _LOG_H
#define _LOG_H

void Log();

#endif
```

### 2. <> and "" (angle brackets and quotes) in #include

#### 1. #include <>

1. If the included file is inside one of the **include paths**, we can use `#include <>`.

    ```c++
    #include <iostream>
    ```

#### 2. #include ""

1. `#include ""` is usually used to include files that are **relative** to the current file, if this file **can't** be relatively found, it will look for the compiler **include paths**.

    ```c++
    #include "Log.h"
    
    #include <Log.h>  // this is wrong!
    ```

    `#include ""` basically can be used in all cases:

    ```c++
    #include "iostream"
    ```

2. If this file is inside the solution, we will use `#include ""`, but if it is a completely **external** dependency or external library that we are **not** compiling with the actual solution, we can use `#include <>` to indicate it's external.

3. When the `header file` is in the parent directory:

    ```c++
    #include "../Time.h"
    ```

### 3. Header files with and without .h extension

The `iostream` `header file` doesn't have the `.h` extension, this is one way to distinguish the `C++` `header files` from the `C` `header files`.

```c++
#include <iostream>
#include <stdlib.h>
```

