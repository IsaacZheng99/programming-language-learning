## 54. Union

**Knowledge Points**: `memory of union`, `type punning and union`, `nested struct`, `nested union`, `anonymous struct`, `anonymous union`

### 1. what is union

`union` can **only** occupy the `memory` of **one** member at a time and it's very useful when you want to give two different names to **one** `variable`

### 2. some examples

1. **occupy the memory of one member**: 

    ```c++
    int main()
    {
        struct Union
        {
            union
            {
                double a;
                int b;
            }
        }
    
        Union u;
        u.b = 2;
        std::cout << u.a << ", " << u.b << std::endl;  // -9.25596e+61, 2
        std::cout << sizeof(Union) << std::endl;  // 8
    }
    ```

2. **type punning and union**: 

    1. **type punning**: 

        ```c++
        struct Vector2
        {
            float x, y;
        };
        
        struct Vector4
        {
            float x, y, z, w;
          
            Vector2& GetFirstVector2()
            {
                return *(Vector*)&x;  // type punning, we don't need to create new things and copy anything
            }
          
            Vector2& GetSecondVector2()
            {
                return *(Vector*)&z;  // type punning
            }
        };
        
        void PrintVector2(const Vector2& vector)
        {
            std::cout << vector.x << ", " << vector.y << std::endl;
        }
        
        
        int main()
        {
            // here the printing function "PrintVector2()" only accepts "Vector2" parameter and we can't print "Vector4" directly, but we can take "Vector4" as two "Vector2"s
            Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };
            PrintVector2(Vector4.GetFirstVector2());  // 1, 2
            PrintVector2(Vector4.GetSecondVector2());  // 3, 4
        }
        ```

    2. **union**: 

        ```c++
        struct Vector2
        {
            float x, y;
        };
        
        struct Vector4
        {
            union
            {
                struct
                {
                    float x, y, z, w;
                };
                struct
                {
                    Vector2 a, b;
                };
            };
        };
        
        void PrintVector2(const Vector2& vector)
        {
            std::cout << vector.x << ", " << vector.y << std::endl;
        }
        
        
        int main()
        {
            Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };
            PrintVector2(vector.a);  // 1, 2
            PrintVector2(vector.b);  // 3, 4
            vector.z = 123;
            PrintVector2(vector.b);  // 123, 4
        }
        ```

    