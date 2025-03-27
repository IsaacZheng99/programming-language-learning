## 62. Structured Bindings

**Knowledge Points**: 

### 1. what is structured bindings

in `39.Multiple Return Values`, we have learned some ways to handle this case and `structured binding` is a new feature that lets us deal with **multiple return values** a little better

### 2. some examples

#### 1. old way: std::tuple<> + std::get<>

```c++
std::tuple<std::string, int> CreatePerson()
{
    return { "xiaoli", 26 };
}

int main()
{
    auto person = CreatePerson();
    std::string name = std::get<0>(person);
    int age = std::get<1>(person);
}
```

#### 2. std::tuple<> + std::tie

```c++
std::tuple<std::string, int> CreatePerson()
{
    return { "xiaoli", 26 };
}

int main()
{
    std::string name;
    int age;
    std::tie(name, age) = CreatePerson();
}
```

#### 3. structured bindings

```c++
std::tuple<std::string, int> CreatePerson()
{
    return { "xiaoli", 26 };
}

int main()
{
    auto[name, age] = CreatePerson();  // a new feature of "C++17"
}
```

#### 4. struct vs. structured bindings

```c++
std::tuple<std::string, std::string> ReturnTwoStrings()
{
    // do something and get two strings
    std::string fs = "fs";
    std::string ss = "ss";

    return { fs, ss };
}

int main()
{
	auto[firstString, secondString] = ReturnTwoStrings();
}
// in the former case, we simply create a "struct" to store the return values, but this "struct TwoStrings" is only used here once, so it's better for us to use "structured binding" instead of using a disposable type
```

