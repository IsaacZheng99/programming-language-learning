## 85. Map

**Knowledge Points**: `std::map<>`, `std::unordered_map<>`, `operator[]`, `at()`, `custom class as the key for std::map<>: operator<`, `custom class as the key for std::unordered_map<>: hash and equal`, `iterate through a map`,  `erase()`

### 1. what does map do

for `std::array<>` and `std::vector<>`, they basically have an `ascending indexing system`, but if you want to find a specific element from them, you need to search an amount of elements and that's why there comes the `map` which gives a key for you to look up for the specific element

### 2. std::map<>

#### 1. what is std::map<>

1. `std::map` is a `self-balancing binary search tree`, typically a `red-black tree`
2. all the elements are ordered
3. the `key` must have an `operation<`

#### 2. some examples

##### 1. iterate the std::vector<> to get an specific element

```c++
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
    
    CityRecord() = default;
    
    CityRecord(std::string name, uint64_t population, double latitude, double longtitude)
        : Name(name), Population(population), Latitude(latitude), Longtitude(long) {}
};

int main()
{
    std::vector<CityRecord> cities;
    
    cities.emplace_back("Melbourne", 5000000, 2.4. 9.4);
    cities.emplace_back("Lol-town", 6000000, 2.4. 9.4);
    cities.emplace_back("Berlin", 7000000, 2.4. 9.4);
    cities.emplace_back("Paris", 8000000, 2.4. 9.4);
    cities.emplace_back("London", 9000000, 2.4. 9.4);
    
    for (const auto& city : cities)  // iteration even if you have a sorted vector, you can use like binary search, but you also need to iterate and traverse some amount of elements
    {
        if (city.Name == "Berlin")  // string comparison is expensive
        {
            std::cout << city.Population << std::endl;
            break;
        }
    }        
}
```

##### 2. std::map<>

```c++
int main()
{
    std::map<std::string, CityRecord> cityMap;
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 6000000, 2.4. 9.4 };
    cityMap["Berlin"] = CityRecord{ "Berlin", 7000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 8000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 9000000, 2.4. 9.4 };
    
    CityRecord& berlinData = cityMap["Berlin"];
    std::cout << berlinData.Population << std::endl;
}
```

##### 3. operator[] of std::map<>

`operator[]` can **insert** an element if there is no such an element

```c++
// operator[]
int main()
{
    std::map<std::string, CityRecord> cityMap;
    // "std::unordered_map<std::string, CityRecord> cityMap;" has the same situation
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 6000000, 2.4. 9.4 };
    //cityMap["Berlin"] = CityRecord{ "Berlin", 7000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 8000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 9000000, 2.4. 9.4 };
    
    CityRecord& berlinData1 = cityMap["Berlin"];  // this code here will actually insert "Berlin" into the map and then give me a reference to that newly inserted "CityRecord"
    berlinData1.Name = "Berlin";
    berlinData1.Population = 7000000;
    
    CityRecord berlinData2;
    berlinData2.Name = "Berlin";
    berlinData2.Population = 7000001;
    cityMap["Berlin"] = berlinData2;  // in both cases, we can insert a "CityRecord" but in the second case we need to "copy", so choose the case 1 to avoid copy and create in place
    
    // there is no "const" version of the "operator[]"
    const auto& cities = cityMap;
    const CityRecord& berlinData = cities["Berlin"];  // Wrong! Compiling error.
}
```

##### 4. at() function

`at()` is safer and you can use it everywhere unless you are ok with **inserting** data

```c++
// "at()" function
int main()
{
    std::map<std::string, CityRecord> cityMap;
    // "std::unordered_map<std::string, CityRecord> cityMap;" has the same situation
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 6000000, 2.4. 9.4 };
    //cityMap["Berlin"] = CityRecord{ "Berlin", 7000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 8000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 9000000, 2.4. 9.4 };
    
    CityRecord& berlinData = cityMap.at("Berlin");  // this will throw an exception because there is no "Berlin" data
    // use ".at()" everywhere unless you are ok with inserting data
}
```

before you use `at()`, you need to check it

```c++
int main()
{
    std::map<std::string, CityRecord> cityMap;
    // "std::unordered_map<std::string, CityRecord> cityMap;" has the same situation
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 5000000, 2.4. 9.4 };
    //cityMap["Berlin"] = CityRecord{ "Berlin", 5000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 5000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 5000000, 2.4. 9.4 };
    
    if (cityMap.find("Berlin") != cityMap.end();)  // check first
    {
    	CityRecord& berlinData = cityMap.at("Berlin");
    	std::cout << berlinData.Population << std::endl;
    }
}
```

##### 5. take CityRecord as the key

if we want to take `CityRecord class` as the key, we need to implement `operator<`

```c++
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
    
    bool operator<(const CityRecord& other) const
    {
        return Population < other.Population;
        // in fact, this temporary implementation is wrong because when "Population >= other.Population" the "operator<" will return "false" and in this case "std::map" will take them as the same keys and the latter "key" won't be inserted but the latter "value" will replace the former "value"
        // moreover, "operator<" will be used for other purposes, so implement it properly
    }
};

int main()
{
    std::map<CityRecord, uint32_t> foundedMap;  // type of the "key" is "CityRecord"
    
    foundedMap[CityRecord{ "Melbourne", 5000000, 2.4. 9.4 }] = 1850;
    foundedMap[CityRecord{ "Paris",85000000, 2.4. 9.4 }] = 1888;
    
    std::cout << foundedMap[{ "Paris123", 8000000, 1.1. 1.1 }] << std::endl;  // 1888
    
    for (auto& [city, year] : foundedMap)
    {
        std::cout << city.Name << " " << city.Population << " " << year << std::endl;  // Melbourne 5000000 1850 Paris 8000000 1888
    }
}
```

### 3. std::unordered_map<>

#### 1. what is std::unordered_map<>

1. `std::unprdered_map` is a hash table

2. the `key` must be hashable

3. all the elements are unordered

4. use `std::unordered_map` whenever possible unless you need a sorted data structure, because `std::unordered_map` usually ends up being **faster** than `std::map` or at the very least, the same speed

    when there is no much data, the performance difference is not obvious

    when **iterating** through maps, which of course isn't the most ideal thing in the real world, `std::map` generally performs better than `std::unordered_map`, however it would be a order of magnitude faster to iterate through a `std::vector`

#### 2. some examples

##### 1. std::unordered_map<>

```c++
// use "std::unordered_map<>"
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

int main()
{
    std::unordered_map<std::string, CityRecord> cityMap;
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 5000000, 2.4. 9.4 };
    cityMap["Berlin"] = CityRecord{ "Berlin", 5000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 5000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 5000000, 2.4. 9.4 };
    
    CityRecord& berlinCity = cityMap["Berlin"];
    std::cout << berlinCity.Population << std::endl;
}
```

##### 2. take CityRecord as the key

if we want to take `CityRecord class` as the key, we need to implement the `template specialization` of the `hash` and `equal_to` (there are many other ways and the key is to implement `hash` and `equal`)

```c++
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

// implement these two
namespace std {
    
    template<>
    struct hash<CityRecord>
    {
        size_t operator()(const CityRecord& key) const
        {
            return hash<std::string>()(key.Name);
        }
    };
    
    template<>
    struct equal_to<CityRecord>
    {
        bool operator()(const CityRecord& lhs, const CityRecord& rhs) const 
        {
            return lhs.Name == rhs.Name;
        }
    };
}

int main()
{
    std::unordered_map<CityRecord, uint32_t> foundedMap;  // type of the "key" is "CityRecord"
    
    foundedMap[CityRecord{ "Melbourne", 5000000, 2.4. 9.4 }] = 1850;
    
    uint32_t mebourneFounded = foundedMap[CityRecord{ "Melbourne", 123123123, 2.4. 9.4 }];
    
    std::cout << mebourneFounded << std::endl;
}
```

### 4. iterate through a map

we can use `range-based for loop` and `structured binding` to iterate a map

```c++
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

int main()
{
    std::unordered_map<std::string, CityRecord> cityMap;
    // "std::map<std::string, CityRecord> cityMap;" has the same situation
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 5000000, 2.4. 9.4 };
    cityMap["Berlin"] = CityRecord{ "Berlin", 5000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 5000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 5000000, 2.4. 9.4 };
    
    for (auto& kv : cityMap)
    {
        const std::string& name = kv.first;
        CityRecord city = kv.second;
    }
    
    for (auto& kv : cityMap)
    {
        auto& name = kv.first;
        auto& city = kv.second;
    }
    
    for (auto& [name, city] : cityMap)  // structured binding
    {
        std::cout << name << city.Population << std::endl;
    }
}
```

### 5. remove a specific element: erase()

we can use `erase()` to remove an specific element

```c++
struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

int main()
{
    std::unordered_map<std::string, CityRecord> cityMap;
    // "std::map<std::string, CityRecord> cityMap;" has the same situation
    
    cityMap["Melbourne"] = CityRecord{ "Melbourne", 5000000, 2.4. 9.4 };
    cityMap["Lol-town"] = CityRecord{ "Lol-town", 5000000, 2.4. 9.4 };
    cityMap["Berlin"] = CityRecord{ "Berlin", 5000000, 2.4. 9.4 };
    cityMap["Paris"] = CityRecord{ "Paris", 5000000, 2.4. 9.4 };
    cityMap["London"] = CityRecord{ "London", 5000000, 2.4. 9.4 };
    
    cityMap.erase("Paris");
    cityMap.erase("Paris123");
}
```

