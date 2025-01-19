## 5. Debug in Visual Studio

**Knowledge Points**: `commands of the debugger`, `difference of Debug mode and Release mode`

1. **three commands of the Debugger**: 

    `step into`: step into the function in the current line

    `step over`: go to the next line

    `step out`: step out of the function in the current line and go back to whatever called this function

2. **difference of Debug mode and Release mode**: 

    in the `Debug` mode, the compiler will help us debug, e.g., the fact of the memory is `0xcccccccc`, which means it is the `uninitialized stack memory`, so what acctually happened is that the compiler knows we are trying to make a `variable` but we have not initialized it yet. In the `Release` mode, the content is just random