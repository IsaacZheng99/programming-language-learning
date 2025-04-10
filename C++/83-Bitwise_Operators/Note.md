## 83. Bitwise Operators

**Knowledge Points**: `<<`, `>>`, `&`, `|`, `^`, `~`

### 1. different kinds of bitwise operators

1. `<<`: bit shift left (multiply 2^n)

2. `>>`:  bit shift right (divided by 2^n)

3. `&`: bitwise and (for mask in some cases)

4. `|`: bitwise or (for combine in some cases)

5. `^`: bitwise xor

6. `~`: bitwise not

### 2. <<

```c++
int a = 1;
int b = a * 2;  // in fact, the compiler will produce "b = a << 1"
int c = a << 1;
```

### 3. & for masking

```
11001010 & 01000000 = 01000000
// we can check the second bit by "& 01000000"

11001010 & 00001111 = 00001010
// we can remove the first four bits by "&00001111"
```

### 4. | for combining

```c++
// 11001010 & 00001111 = 00001010
// 1100 << 4 = 11000000
// 11000000 | 00001010 = 11001010

int main()
{
    int mask = 0b1111;
    int a = 0b11101010;
    int b = 0b1100;
    
    // combine a and b

    int c = (a & mask) | (b << 4);
    
    std::cout << std::bitset<8>(c) << std::endl;  // 11001010
}
```

### 5. ^

when the two numbers are **different**, `&` and `|` will give `0` and `1` separately, but we want an operator that can give us always `1` in this case

```
a ^ a = 0, a cool way to set variables to be 0
```

