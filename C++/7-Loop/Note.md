## 7. Loop

**Knowledge Points**:

1. `for`
2.  `while`
3.  `do while`
4. `other ways to write a for loop`

### 1. for

There are three parts in `for` statement:

1. `Initialization expression`: `int i = 0` is executed only once at the **beginning** of the loop.
2. `Condition expression`: `i < 10` is evaluated **before** the **next** iteration.
3. `Iteration expression`: `i++` is executed at the **end** of each iteration.

```c++
for (int i = 0; i < 10; i++)
{
  // ...
}
```

### 2. while

```c++
int i = 0;
while (i < 10)
{
  // ...
  i++;
}
```

### 3. do while

```c++
int i = 0;
do
{
  // ...
  i++; 
} while (i < 10);
```

### 4. Other ways to write a for loop

Note the below `for` loop will be executed for `11` times.

```c++
int i = 0;
bool condition = true;
for (; condition; )
{
  if (!(i < 10))
    condition = false
  // ...
  i++;
}
```

