## 80. Iterator

**Knowledge Points**: `range-based for loop`, `begin() and end()`, `iterator, reverse_iterator, const_iterator, const_reverse_iterator`, `range-based for loop with structured binding`

### 1. what is iterator

1. `iterator` is essentially a way for you to iterate over a collection of elements

2. `iterator` is really up to the implementation in terms of how it is used, you can use `iterator` to do anything, kind of like `operator overloading` (e.g., you can make `operator++` do anything), but in general we use it to iterate over data structure

### 2. some examples

#### 1. range-based for loop

```c++
int main()
{
    std::vector<int> values = { 1, 2, 3, 4, 5 };
    
    for (int i = 0; i < values.size(); i++)
		std::cout << values[i] << std::endl;
    
    for(int value : values)  // "range-based for loop", which depends on the "begin()" and "end()" methods provided by the container
        std::cout << value << std::endl;
}
```

#### 2. std::vector<>::iterator

```c++
int main()
{
    std::vector<int> values = { 1, 2, 3, 4, 5 };
    
    // when you want to manipulate the position of the iterator, use this kind of code, e.g., when you want to erase an element but still keep iterating the rest of the collection or you want to insert something
    for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
    {
		std::cout << *it << std::endl;  // "*it"  dereference the iterator, which is implemented by "operator*"
    }
}
```

#### 3. different kinds of iterator

```c++
std::vector<int>::iterator
std::vector<int>::reverse_iterator
std::vector<int>::const_iterator
std::vector<int>::const_reverse_iterator
```

#### 4. iterate std::unordered_map<>

when we traverse a `std::vector` or `std::array`, we can simply index them by one value, which is the ascending index (`int i = 0; i < container.size(); i++`), but when it comes to `tree`, `unordered set`, we can't and we need to use `iterator`

##### 1. const_iterator

```c++
int main()
{
    using ScoreMap = std::unordered_map<std::string, int>;
    ScoreMap map;
    map["xiaoli"] = 5;
    map["C++"] = 2;
    
    for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++)
    {
        auto& key = it->first;
        auto& value = it->second;
        
    	std::cout << key << " = " << value << std::endl;
    }
}
```

##### 2. range-based for loop

```c++
int main()
{
    using ScoreMap = std::unordered_map<std::string, int>;
    ScoreMap map;
    map["xiaoli"] = 5;
    map["C++"] = 2;
    
    for (auto kv : map)  // "kv" is a "std::pair"
    {
        auto& key = kv.first;
        auto& value = kv.second;
        
    	std::cout << key << " = " << value << std::endl;
    }
}
```

##### 3. range-based for loop with structured binding

```c++
int main()
{
    using ScoreMap = std::unordered_map<std::string, int>;
    ScoreMap map;
    map["xiaoli"] = 5;
    map["C++"] = 2;
    
    for (auto [key, value] : map)  // structured binding
    	std::cout << key << " = " << value << std::endl;
}
```

#### 3. TODO

`TODO`: delete or add element in the assigned place

