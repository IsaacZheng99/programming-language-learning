## 57. Condition and Action Breakpoints

**Knowledge Points**: `condition breakpoints`, `action breakpoints`, `keep the current memory state`, `affect the performance`

### 1. why need them?

you could just add code that **prints something** in the actual source code of the application but you **haven't** stopped your application or recompiled anything, not only fast and convenient but also you can **save the current memory state** because if you use other ways, you need to re-compile and the bug state may not be reproducible

### 2. condition breakpoints

1. want the `breakpoint` to trigger under a certain condition
2. very useful in `loops`, e.g., if you want to break when it iterates the 100th `entity`, you just set the condition `e.GetIdx() == 100` and you don't need to press `F5` continuously until it comes the 100th `entity`

### 3. action breakpoints

1. allow us to take some kinds of actions when a breakpoint hits
2. two types: breakpoint hits and then keep the program running or break the program

### 4. others

1. if use `condition` and `action breakpoints` at the same place, you can print something under the condition 
2. note that these two `breakpoints` will lag the application and thus affect the performance, if you are currently caring about the performance, it's better to recompile and use some codes to help you

