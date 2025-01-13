## 3. Function

1. every time we call a `function`, the compiler generates a `call` instruction, which basically means that in a running program, in order to call a function, we need to create a **stack frame** for the parameters and returing address, and we need to jump to somewhere of the binary file to excute the function and jump back to return the value
2. usually the declarition is in the `header` file and the definition is in the `cpp` file