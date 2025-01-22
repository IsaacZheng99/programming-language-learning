## 41. Stack and Heap Memory

**Knowledge Points**: `the location of stack and heap`, `difference of memory allocation of stack and heap memory`, `new`, `cache miss`

### 1. where are stack and heap

When the application gets lunched, what the `operating system` does is it will load the **entire program** into the `memory`, as well as acllocate a whole bunch of physical `ram`, so that our actual application can run.

The `stack` and the `heap` are two areas that we actually have in our `ram`, and the `stack` is typically an area of `memory` that has a **pre-defined** size, usually around `2M` bytes or so and the `heap` is an area that the size of which is also **kind of pre-defined** to a defalut value, however **can grow and change** as our application goes on.

It's important to know that the physical location of these two areas in `memory` is ultimately the **same**, they are both in the `ram`.

### 2. memory allocation

#### 1. stack

1. **close**: 

    `varibales` created on the stack are very **close** in the memory

2. **fast**: 

    `stack memory` will be freed once it gets out of the scope and the `free` operation doesn't cost anything because it just needs the `stack pointer` to move backwards and return the address, this is simply like **one** `CPU instruction`

```c++
struct Vector3
{
    float x, y, z;

    Vector3()
    	: x(10), y(11), z(12) {}
}

int main()
{
    int value = 5;
    int array[5];
    for (int i = 0; i < 5; i++)
    	array[i] = i;
    Vector3 vector;
    // if we check the memory, we will see that these varibales are very close in the memory because when allocate variables in the stack, all that happens is the "stack pointer" basically just move that amount of bytes: 4 bytes, 5 * 4 bytes and 3 * 4 bytes
    // this is also the reason why stack allocation is so fast 
}
```

#### 2. heap

compare the two kinds of `memory`

```c++
int main()
{
    int value = 5;
    int array[5];
    for (int i = 0; i < 5; i++)
    	array[i] = i;
    Vector3 vector;
    std::cout << &value << std::endl;  // 000000F34998F384
    std::cout << array << std::endl;  // 000000F34998F3A8
    std::cout << &vector << std::endl;  // 000000F34998F3F8
    // if we check the memory, we will see that these varibales are very close in the memory because when allocate variables in the stack, all that happens is the "stack pointer" basically just move that amount of bytes: 4 bytes, 5 * 4 bytes and 3 * 4 bytes
    // this is also the reason why stack allocation is so fast 

    int* hvalue = new int;
    *hvalue = 5;
    int* harray = new int[5];
    for (int i = 0; i < 5; i++)
    	harray[i] = i;
    Vector3* hvector = new Vector3();
    std::cout << hvalue << std::endl;  // 000002886FF348D0
    std::cout << harray << std::endl;  // 000002886FF371D0
    std::cout << hvector << std::endl;  // 000002886FF36D70
    delete hvalue;
    delete[] harray;
    delete hvector;
}
// you can simply check the assembly code of this code and you will see the "stack" part calls much less instructions that the "heap" part does
```

### 3. what does new do

The `new` key word really just calls a `function` called `malloc()` and what this `function` will do is usually to call the underlying `operating system specific function` and allocate memory for us on the heap.

When we start up your application, you get a certain amount of physical `ram` acllocated to us, and our program maintains something called `free list`, which basically keeps track of which blocks of memory are **free** and **where** they are, so when we actually ask for `dynamic memory using`, it will go through the `free list` and give us a `pointer` pointing to a `block memory` which is at least as same as the size we want and there are a lot of recordings such as the size of the allocation and the fact that it has been allocated.

If you ask for a` block memory` which **exceeds** the size of memory in that `free list`, your applcation will ask your `operating system` and this will be very **expensive**.

### 4. cache miss

almost **no** `cache misses` on the `stack`, a couple of `cache misses` on the `heap`, but this won't affect much

