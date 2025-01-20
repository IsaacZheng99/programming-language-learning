## 26. Ternary Operator

**Knowledge Points**: `ternary operator`, `return value optimization (RVO)`, `nested ternary operator`

1. **what is ternary operator**: 

    `ternary operator` is `syntax suger` for `if` statement

2. **return value optimization**: 

    ```c++
    static int s_Level = 1;
    static int s_Speed = 2;
    
    int main()
    {
        s_Speed = s_Level > 5 ? 10 : 5;
    
        std::string rank = s_Level > 10 ? "Master" : "Beginner";  // Return Value Optimmization (RVO): no intermediate string created
        std:: string otherRank;  // it's slower than the former one because you are constructing an empty string and assign it with "Master" or "Beginner" immediately
        // in my opinion, there are one kind of optimization called "Small String Optimization (SSO)", so maybe it wouble be more accurate if we use some benchmarks to test this
        if (s_Level > 10)
            otherRank = "Master";
        else
            otherRank = "Beginner";
    }
    ```

3. **nested ternary operator**: 

    ```c++
    int main()
    {
        s_Speed = s_Level > 5 ? (s_Level > 10 ? 15 : 10) : 5;
    	s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
    }
    ```

    