## 3. Function

**Knowledge Points**:

1. `call a function: call instruction, stack frame`
2. `declaration and definition`

### 1. What happens when we call a function

Every time we call a `function`, the compiler generates a `call` instruction, which basically means that in a running program, in order to call a `function`, we need to create a **stack frame** for the **parameters and returing address**, and we need to **jump to** somewhere of the binary file to excute the `function` and **jump back** to return the value.

### 2. Declaration and Definition of function

Usually the `declaration` is in the `header` file and the `definition` is in the `.cpp` file.

