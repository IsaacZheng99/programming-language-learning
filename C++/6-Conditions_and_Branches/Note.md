## 6. Conditions and Branches

**Knowedge Points**:

1. `overhead of conditionals: check and jump`
2. `Go To Disassembly`
3. `else if`

### 1. Overhead of conditionals

1. The `if` statements and `branching` statements generally do carry a little bit **overhead** because we have to check condition and then **jump to a different portion** of the `memory` and start executing instructions.
2. We can use`Go To Disassembly` to check the `assembly code` in the `Debug` mode during debugging and see what really happens.

### 2. else if

The `else if` is not a key word , it's just a combination of `else` and `if`.

```c++
if (a == 1)
{
  // ...
}
else if (a == 2)
{
  // ...
}

if (a == 1)
{
  // ...
}
else
{
  if (a == 2)
  {
     // ...
  }
}
```

