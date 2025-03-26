## 59. Precompiled Header

**Knowledge Pointers**: `Precompuled Header`, `when to use`, `settings in visual studio`

### 1. why need

1. `precompiled headers` give you the opportunity to grab a bunch of `header files` and convert them into the compiled format, then the compiler can use them instead of reading those `header files` over and over again (e.g., every time when we `#include <vector>`, it needs to read the entire `header file` and `compile` it, not only the `<vector>` header file but also the included files in this `header file`)
2. precompile the header files and store them as binary files, which are much **faster** for the compiler to deal with than the text files

### 2. when to use

1. do **not** put **frequently** changing files into the `precompiled headers` 
2. widely used for `header files` which are not yours, like `C++ standard libraries`, `Windows.h`...
3. it's more readable not to put all files into the `PCH`, e.g., if you have just one `.cpp` file needs to `#include <glfw>`, simply include it but not put it into the `PCH`

### 3. how to use

1. first we can check the size of the pre-processed code by setting `Preprocess to a File` as `Yes` and we will find there are `409086` lines in the `Main.i` file, and this is what we need to recompile every single time when we `#include "pch.h"`, so we need `precompiled headers`
2. in `visual studio`, we need to create a `.cpp` file which inlcudes the `header file`, e.g. `pch.cpp` includes `pch.h`
3. check the `Properties` of the `pch.cpp` file and set the `Precompiled Header` as `Create`
4. check the `Properties` of the current project and set the `Precompiled Header` as `Use` and the `Precompiled Header File` as `pch.h`, and now if you check the check the `Properties` of the `Main.cpp` file, you will find the `Precompiled Header` is `Use` and the `Precompiled Header File` is `pch.h`
5. we can compare the two cases: build by setting `Precompiled Header` as `Not Using Precompiled Headers` and build again after add one line of code, and build by setting `Precompiled Header` as `Use` and build again after add one line of code, the building time is  `3269 ms` vs `873 ms` (don't forget to `clean` and set `Build Timing` as `Yes`)

