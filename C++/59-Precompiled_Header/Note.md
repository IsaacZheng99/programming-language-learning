## 59. Precompiled Header

**Knowledge Pointers**: 

### 1. why need precompiled header

1. `precompiled headers` give you the opportunity to grab a bunch of `header files` and convert them into the compiled format, then the compiler can use them instead of reading those `header files` over and over again (e.g., every time when we `#include <vector>`, it needs to read the entire `header file` and `compile` it, not only the `<vector>` header file but also the included files in this `header file`)
2. precompile the header files and store them as binary files, which are much **faster** for the compiler to deal with than the text files

### 2. when to use precompiled header

1. do **not** put **frequently** changing files into the `precompiled headers` 
2. widely used for `header files` which are not yours, like `C++ standard libraries`, `Windows.h`...
3. it's more readable not to put all files into the `PCH`, e.g., if you have just one `.cpp` file needs to `#include <glfw>`, simply include it but not put it into the `PCH`

