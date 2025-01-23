## 43. Auto

**Knowledge Points**: `auto`, `bad and good use of auto`, `template and auto`

### 1. what can auto do

`auto` can **automatically** deduce the correct type

```c++
int main()
{
    auto a = 1;
    std::cout << a << std::endl;  // 1
    std::cout << typeid(a).name() << std::endl;  // int

    int b = 1;
    auto c = b;
    std::cout << c << std::endl;  // 1
    std::cout << typeid(c).name() << std::endl;  // int

    auto d = 1;
    auto e = d;
    std::cout << d << std::endl;  // 1
    std::cout << typeid(d).name() << std::endl;  // int
    std::cout << e << std::endl;  // 1
    std::cout << typeid(e).name() << std::endl;  // int

    auto f = 5.5f;
    std::cout << f << std::endl;  // 1
    std::cout << typeid(f).name() << std::endl;  // float
    
    auto l = 1L;
    std::cout << l << std::endl;  // 1
    std::cout << typeid(l).name() << std::endl;  // long
    // this is where "C++" can kind of turn into a "weakly-typed" language
    // besides, we can just change the right hand side and keep the left as "auto"
    // so, here comes the question: if we have "auto", do we still need to write types?
}
```

### 2. if we have auto, do we still need to write types?

1. **in some cases, we only need to change the value on the right hand side of the equal sign**: 

```c++
int main()
{
  auto a = 1;
  // auto a = nullptr;
  // auto a = "xiaoli";
  // auto a = 'a';
}
```

2. **bad use of auto**: 

    1. without `auto`: 

        ```c++
        std::string GetName()
        {
        	return "xiaoli";
        }
        
        int main()
        {
            std::string name = GetName();
            std::cout << typeid(name).name() << std::endl;  // class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >
            std::cout << name.size() << std::endl;  // 6
        }
        ```

    2. use `auto` in the returning place: 

        ```c++
        std::string GetName()
        {
        	return "xiaoli";
        }
        
        int main()
        {
            auto name = GetName();  // use "auto"
            std::cout << typeid(name).name() << std::endl;  // class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >
            std::cout << name.size() << std::endl;  // 6
        }
        ```

    3. only change the `returning type` of the `function`:

        only change the right hand side (here is the `function`) doesn't work all the time

        ```c++
        const char* GetName()
        {
        	return "xiaoli";
        }
        
        int main()
        {
            auto name = GetName();  // when we use "auto" here, we indeed don't need to change the type of "name" when we change the return type of the "GetName()" function, meaning we only need to change one place, but this will cause problem
            std::cout << typeid(name).name() << std::endl;  // const char * __ptr64
            std::cout << name.size() << std::endl;  // Wrong!
        }
        ```

    4. explicitly write the returning type: 

        ```c++
        const char* GetName()
        {
        	return "xiaoli";
        }
        
        int main()
        {
            std::string name = GetName();
            std::cout << typeid(name).name() << std::endl;  // class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >
            std::cout << name.size() << std::endl;  // 6
        }
        ```

    5. use two `auto` both in the `returning type` and the returning place: 

        ```c++
        auto GetName()
        {
        	return "xiaoli";
        }
        
        int main()
        {
            auto name = GetName();
            std::cout << typeid(name).name() << std::endl;  // const char * __ptr64
            std::cout << name.size() << std::endl;  // Wrong!
        }
        ```

3. **good use of auto**: 

    when the `type` is too long

    1. `std::vector<std::string>::iterator`: 

        ```c++
        int main()
        {
            std::vector<std::string> strings;
            strings.push_back("Apple");
            strings.push_back("Orange");
            //for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++)
            for (auto it = strings.begin(); it != strings.end(); it++)
            	std::cout << *it << std::endl;
        }
        ```

    2. custom `class DeviceManager`: 

        1. without `auto`: 

            ```c++
            class Device {};
            
            class DeviceManager
            {
            private:
            	std::unordered_map<std::string, std::vector<Device*>> m_Devices;
            public:
            	const std::unordered_map<std::string, std::vector<Device*>>& GetDevices() const
                {
                	return m_Devices;
                }
            };
            
            int main()
            {
                DeviceManager dm;
                const std::unordered_map<std::string, std::vector<Device*>>& devices = dm.GetDevices();
            }
            ```

        2. use `using`: 

            ```c++
            int main()
            {
                using DeviceMap = std::unordered_map<std::string, std::vector<Device*>>;
            
                DeviceManager dm;
                const DeviceMap& devices = dm.GetDevices();
            }
            ```

        3. use `typedef`: 

            ```c++
            int main()
            {
                typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMap;
            
                DeviceManager dm;
                const DeviceMap& devices = dm.GetDevices();
            }
            ```

        4. use `auto`: 

            ```c++
            int main()
            {
                DeviceManager dm;
                const auto& devices = dm.GetDevices();
                //const auto devices = dm.Devices();  // same as "const std::unordered_map<std::string, std::vector<Device*>> devices = dm.GetDevices();"
                //auto devices = dm.GetDevices();  // same as "std::unordered_map<std::string, std::vector<Device*>> devices = dm.GetDevices();"
                // the last two will copy
            }
            ```

### 3. template and auto

when you use `template` and you don't know the type, you need to use `auto`, but avoid this case as much as possible

