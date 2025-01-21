## 30. Operator

**Knowledge Points**: `operator`, `some examples of operators`

1. **what is operator**: 

    `operator` is basically some kind of symbol that we use usually instead of a `function` to perform something

2. **some examples of operators**: 

    1. **operator+**:

        without `operator+`: 

        ```c++
        struct Vector2
        {
            float x, y;
        
            Vector2(float x, float y)
            	: x(x), y(y) {}
        
            Vector2 Add(const Vector2& other) const
            {
            	return Vector2(x + other.x, y + other.y);
            }
        
            Vector2 Multiply(const Vector2& other) const
            {
            	return Vector2(x * other.x, y * other.y);
            }
        }
        
        int main()
        {
            Vector2 position(2.0f, 2.0f);
            Vector2 speed(1.0f, 1.0f);
            Vector2 powerup(1.1f, 1.1f);
        
            Vector2 result = position.Add(speed.Multiply(powerup));  // this is what you can only do in "Java" and it's a little difficult to read
        }
        ```

        with `operator+`: 

        ```c++
        struct Vector2
        {
            float x, y;
        
            Vector2(float x, float y)
            	: x(x), y(y) {}
        
            Vector2 Add(const Vector2& other) const
            {
            	return Vector2(x + other.x, y + other.y);
            }
        
            Vector2 Multiply(const Vector2& other) const
            {
            	return Vector2(x * other.x, y * other.y);
            }
        
            Vector2 operator+(const Vector2& other) const  // operator "+"
            {
            	return Add(other);  // call the "Add()" function
            }
        }
        
        int main()
        {
            Vector2 position(2.0f, 2.0f);
            Vector2 speed(1.0f, 1.0f);
            Vector2 powerup(1.1f, 1.1f);
        
            Vector2 result1 = position.Add(speed.Multiply(powerup));
            Vector2 result2 = position + speed; \\ * powerup
        }
        ```

        the `Add() function` can also call the `operator+`: 

        ```c++
        struct Vector2
        {
            float x, y;
        
            Vector2(float x, float y)
            	: x(x), y(y) {}
        
            Vector2 Add(const Vector2& other) const  // the "Add()" function can also call the plus operator
            {
            	return *this + other;
            	// return operator+(other);
            }
        
            Vector2 Multiply(const Vector2& other) const
            {
            	return Vector2(x * other.x, y * other.y);
            }
        
            Vector2 operator+(const Vector2& other) const
            {
            	return Vector2(x + other.x, y + other.y);
            }
        }
        
        int main()
        {
            Vector2 position(2.0f, 2.0f);
            Vector2 speed(1.0f, 1.0f);
            Vector2 powerup(1.1f, 1.1f);
        
            Vector2 result1 = position.Add(speed.Multiply(powerup));
            Vector2 result2 = position + speed; \\ * powerup
        }
        ```

    2. **operator***: 

        ```c++
        struct Vector2
        {
            float x, y;
        
            Vector2(float x, float y)
            	: x(x), y(y) {}
        
            Vector2 Add(const Vector2& other) const
            {
            	return Vector2(x + other.x, y + other.y);
            }
        
            Vector2 Multiply(const Vector2& other) const
            {
            	return Vector2(x * other.x, y * other.y);
            }
        
            Vector2 operator+(const Vector2& other) const
            {
            	return Add(other);
            }
        
            Vector2 operator*(const Vector2& other) const
            {
            	return Multiply(other);
            }
        }
        
        int main()
        {
            Vector2 position(2.0f, 2.0f);
            Vector2 speed(1.0f, 1.0f);
            Vector2 powerup(1.1f, 1.1f);
        
            Vector2 result1 = position.Add(speed.Multiply(powerup));
            Vector2 result2 = position + speed * powerup; // make more sense and more readable 
        }
        
        ```

    3. **operator== (equality operator), operator!= (inequality operator), operator<< (left-shift operator)**: 

        ```c++
        struct Vector2
        {
            float x, y;
        
            Vector2(float x, float y)
            	: x(x), y(y) {}
        
            Vector2 Add(const Vector2& other) const
            {
            	return Vector2(x + other.x, y + other.y);
            }
        
            Vector2 Multiply(const Vector2& other) const
            {
            	return Vector2(x * other.x, y * other.y);
            }
        
            Vector2 operator+(const Vector2& other) const
            {
            	return Add(other);
            }
        
            Vector2 operator*(const Vector2& other) const
            {
            	return Multiply(other);
            }
        
            bool operator==(const Vector2& other) const
            {
            	return x == other.x && y == other.y;
            }
        
            bool operator!=(const Vector2& other) const
            {
                return !(*this == other);
                // return !operator==(other);
            }
        }
        
        // left-shift operator
        // like "ToString()" in "Java" or "C#", which is commonly override
        std::ostream& operator<<(std::ostream& stream, const Vector2& vector2)
        {
            stream << vector2.x << ", " << vector2.y;
            return stream;
        }
        
        
        int main()
        {
            Vector2 position(2.0f, 2.0f);
            Vector2 speed(1.0f, 1.0f);
            Vector2 powerup(1.1f, 1.1f);
        
            Vector2 result1 = position.Add(speed.Multiply(powerup));
            Vector2 result2 = position + speed * powerup;
            std::cout << (result1 == result2) << std::endl;  // 1
            std::cout << (result1 != result2) << std::endl;  // 0
            std::cout << result2 << std::endl;  // 3.1, 3.1
        }
        ```


