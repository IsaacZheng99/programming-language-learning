## 5. Debug in Visual Studio

**Knowledge Points**:

1. `commands of the debugger: step into, step over, step out`
2. `difference of Debug mode and Release mode: fact of the memeory`

### 1. Commands of the debugger

There are three commands of the debugger:

1. `step into`: step into the `function` in the current line.

2. `step over`: go to the next line.

3. `step out`: step out of the `function` in the current line and go back to whatever called this `function`.

### 2. Difference of Debug mode and Release mode

In the `Debug` mode, the compiler will help us debug, e.g., the fact of the memory is `0xcccccccc` (please set the `solution platform` as `x86`), which means it is the `uninitialized stack memory`, so what acctually happened is that the compiler knows we are trying to make a `variable` but we have not initialized it yet. In the `Release` mode, the content is just **random**.

