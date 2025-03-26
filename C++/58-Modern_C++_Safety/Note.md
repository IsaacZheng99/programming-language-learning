## 58. Modern C++ Safety

**Knowledge Points**: `safe programming`, `an example of smart pointers`

### 1. safe programming

`safe programming` means we hope reduce crashes, memory leaks, access violations, etc.

### 2. when to use smart pointers

1. for `smart pointers`, not only it can help us **automatically** manage the memory, but also in some cases, e.g., you have two `functions` that need one pointer and you don't know which one would be called later, now it's impossible for you to **manually** `delete` the pointer because you even don't know when it will not be used anymore
2. in the context of real frame, real application, use `smart pointers` in general cases

