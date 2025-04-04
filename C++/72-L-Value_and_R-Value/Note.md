## 72. L-Value and R-Value

**Knowledge Points**: `l-value`, `r-value`, `l-value reference`, `const l-value reference`, `r-value reference`

### 1. what is l-value and r-value

`l-value` is a lot of the times something that is on the left side of the equal sign and `r-value` is something on the right side

#### 1. l-value

```c++
int main()
{
    int i = 10;
    // we have a variable called "i", which is of course an actual variable with a location in memory
    // we have simply a value ,10, just a numerical literal, it has no storage, no loacation until it is assigned to an l-value, which is what "i" is
    
	int a = i;
    // here we are setting an l-value equal to something that is also an l-value
}
```

#### 2. r-value

```c++
int GetValue()
{
    return 10;
}

int main()
{
    int i = GetValue();
    // "GetValue()" returns an r-value, a temporary value
    GetValue() = 5;  // Wrong! Compiling error. "experssion must be a modifiable lvalue", here "modifiable" means it has to be "non-const"
}
```

### 2. l-value reference

#### 1. function returning l-value reference

for `GetValue() = 5` in `1.2`, we can try to make `GetValue()` become an `l-value`, so we can use `l-value reference` in this case and we need a storage for this `l-value reference`

```c++
int& GetValue()
{
    static int value = 10;
    return value;
}

int main()
{
    GetValue() = 1;
}
```

#### 2. function with l-value parameter

here we have a `function` which has an `l-value` parameter and it can take both the `l-value` and `r-value`, this case is similar to `1.1`

```c++
void SetValue(int value)  // "int value" is "l-value"
{
}

int main()
{
    int a = 10;
    SetValue(a);   // l-value used to create the l-vaue
    SetValue(10);  // r-value used to create the l-vaue
}
```

#### 3. function with l-value reference parameter

there is a rule that we can't assign an `r-value` to an `l-value reference`

```c++
void SetValue(int& value)
{
}

int main()
{
    int a = 10;
    SetValue(a);
    SetValue(10);  // Wrong! Compiling error. "initial value of reference to non-const must be an lvalue"
    // you can not take an l-value reference from a r-value
}
```

#### 4. function with l-value reference parameter: std::string&

```c++
void PrintName(std:string& name)
{
    std::cout << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    std::string fullName = firstName + lastName;
    // l-values: firstName, lastName, fullName
    // r-values: "xiao", "li", firstName + lastName
    // a temporary string gets constructed from "firstName" and "lastName" and then it gets assigned into an l-value: "fullName"
    
    PrintName(fullName);
    PrintName(firstName + lastName); // Wrong! Compiling error. "initial value of reference to non-const must be an lvalue"
}
```

#### 5. function with l-value const reference parameter

1. `l-value const reference` can accept both `r-value` and `l-value` and we can leverage this rule to detect `l-value` by setting `non-const l-value reference`
2. as for why, for `non-const l-value reference` if we can assign an `r-value` to it, we can modify a temporary value, which makes no sense and may cause `UB`, whereas for `cosnt l-value reference`, the `const` makes sure when won't modify it and thus this is safe, besides it can extend the life time of the `r-value` since in general case the `r-value` will be destroyed right at the end of the expression, but if we assign it to a `const l-value reference`, it will exist until the end of the scope

```c++
void PrintName(const std:string& name)  // you can see a lot of const references being written in "C++", because they are compatible with both temporaries, r-values and also actual kind of real existing variables, l-values
// so we clearly have a way to detect whether or not something is an actual l-value, we can do that by just writing an l-value reference that's not const, because a non-const l-value reference can only accept l-values
{
    std::cout << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    
    std::string fullName = firstName + lastName;
    
    PrintName(fullName);
    PrintName(firstName + lastName);
}
```

### 3. r-value reference

`r-value reference` is a  way to write a `function` that **only** accepts temporaries

#### 1. function with r-value reference parameter

```c++
void PrintName(std:string&& name)
{
    std::cout << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    
    std::string fullName = firstName + lastName;
    
    PrintName(fullName);  // Wrong! Compiling error. "an rvalue reference cannot be bound to an lvalue"
    PrintName(firstName + lastName);
}
```

#### 2. override functions with r-value reference parameter and l-value reference parameter

```c++
void PrintName(std:string&& name)
// with "r-value reference", we can do many things without worrying about making sure that we keep it alive, we keep it intact, we copy it, in fact we can steal the resources from the temporary value because it is temporary
{
    std::cout << "[rvalue] " << name << std::endl;
}

void PrintName(std:string& name)
{
    std::cout << "[lvalue] " << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    
    std::string fullName = firstName + lastName;
    
    PrintName(fullName);
    PrintName(firstName + lastName);
}
// outputs: 
// [lvalue] xiaoli
// [rvalue] xiaoli
```

#### 3. override functions with r-value reference parameter and const l-value reference parameter

```c++
void PrintName(std:string&& name)
{
    std::cout << "[rvalue] " << name << std::endl;
}

void PrintName(const std:string& name)  // even you use "const reference"
{
    std::cout << "[lvalue] " << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    
    std::string fullName = firstName + lastName;
    
    PrintName(fullName);
    PrintName(firstName + lastName);
}
// outputs: 
// [lvalue] xiaoli
// [rvalue] xiaoli
```

#### 4. function with const r-value reference

```c++
void PrintName(const std:string&& name)
{
    std::cout << name << std::endl;
}

int main()
{
    std::string firstName = "xiao";
    std::string lastName = "li";
    
    std::string fullName = firstName + lastName;
    
    PrintName(fullName);  // Wrong! Compiling error. an rvalue reference cannot be bound to an lvaue (no special rule here)
    PrintName(firstName + lastName);
}
```

### 4. summary

1. `l-values` are basically variables that have some kind of storage backing them, `r-values` are temporary values
2. `l-value references` can only take in `l-values` unless they are `const`, `r-value references` only take in these temporary `r-values`

