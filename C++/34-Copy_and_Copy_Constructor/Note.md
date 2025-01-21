## 34. Copy and Copy Constructor

**Knowledge Points**: `when to copy`, `examples of copy`,`shallow copy`, `copy constructor`

1. **when to copy**:

    1. `copy` costs so we need to use it when **necessary**
    2. you are "**always**" copying when you use one `variable` to assign another `variable` (e.g., the `operator=`) except `reference (&)`

2. **examples of copy**: 

    1. **copy the primitive-typed object**: 

        ```c++
        int main()
        {
            int a = 1;
            int b = a ;
            b = 2;  // now a = 1 and b = 2, in this case we simply copy the value
        }
        ```

    2. **copy the non-primitive-typed object**: 

        ```c++
        struct Vector2
        {
        	float x, y;
        };
        
        int main()
        {
            Vector2 v1 = { 1, 2 };
            Vector2 v2 = v1;  // in this case we also copy the value, we are copying what "v1" is into "v2"
            v2.x = 3;  // now v2 = {3, 2} and v1 = {1, 2}
        }
        ```

    3. **copy the pointer**: 

        ```c++
        int main()
        {
            Vector2* v1 = new Vector2();
            Vector2* v2 = v1;
        
            v2->x = 1;  // in this case, it will affect both "v1" and "v2" because "v1" and "v2" are pointing to the same memory, where the "x" is set to be "1"
            v2++; // it will only change "v2"
        }
        ```

3. **shallow copy with custom class String**: 

    1. **create a custom class String**: 

        ```c++
        // version 1:
        class String
        {
        private:
            char* m_Buffer;
            int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size];
                // for (int i = 0; i < m_size; i++)
                // {
                //   m_Buffer[i] = string[i];
                // }
                memcpy(m_Buffer, string, m_Size);
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        std::ostream& operator<<(std::ostream& stream, const String& string)
        {
            stream << string.m_Buffer;
            return stream;
        }
        
        int main()
        {
            String string = "xiaoli";
            std::cout << string << std::endl;  // xiaoli    葺葺葺  抙?
            // note that we simply use the "strlen(string)" as the size of the buffer, but there needs one more byte to store the "null termination character", so we can use "strcpy()" or "m_Size + 1"
        }
        ```

    2. **use m_Size + 1**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;  // add the "\0" manually in case that the input "string" doesn't have the "null termination character"
        	}
          
        	friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
            String string = "xiaoli";
            std::cout << string << std::endl;  // xiaoli
        }
        ```

    3. **when we use new to allocate memory, we need to use delete to free the memory**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
        	String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];  // here we use "new" to allocate memory and we need to "delete" it
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
          
            ~String()
            {
            	delete[] m_Buffer;  // delete
            }
          
        	friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
            String string = "xiaoli";
            std::cout << string << std::endl;  // xiaoli
        }
        ```

    4. **shallow copy**: 

        ```c++
        int main()
        {
            String string = "xiaoli";
            String second = string;
            std::cout << string << std::endl;
            std::cout << second << std::endl;
            // the output is two "xiaoli", which is correct, but when you are trying to exit the console, it will crash
            // in this case, it will do "shallow copy" and all the value of "string" object will be copied to "second", which means the two "m_Buffer" pointers in these two objects are pointing to the same memory address and when destroying these two "String" objects, the deconstrutor will be called and the "delete" operation will be called twice, which results in freeing the same memory twice and it causes the crash because we can't free the memory which has been freed
        }
        ```

        add `operator[]`: 

        ```c++
        // version 5:
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
        
            ~String()
            {
            	delete[] m_Buffer; 
            }
        
            char& operator[](unsigned int index)  // operator[]
            {
            	return m_Buffer[index];
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
            String string = "xiaoli";
            String second = string;
        
            second[0] = 'a';
        
            std::cout << string << std::endl;
            std::cout << second << std::endl;
            // in this case, you will see both the printing results are "aiaoli" and it will also crash
            // we really want to copy the memory but now we just copy the "pointer", so we need to do "deep copy"
        }
        ```

4. **copy constructor**: 

    when you are trying to create a new `variable` and assign it with another `variable` which has the same type as the `variabe` you are actually creating, you are calling the `copy constructor`

    1. **default copy constructor**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
        
            String(const String& other)
            	: m_Buffer(other.m_Buffer), m_Size(other.m_Size)  // this is exactly the default "copy constructor"
            {
            }
        
            //String(const String& other)
            //{
            //	memcpy(this, &other, sizeof(String));  // this is also fine
            //}
        
            ~String()
            {
            	delete[] m_Buffer; 
            }
        
            char& operator[](unsigned int index)
            {
            	return m_Buffer[index];
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
          String string = "xiaoli";
          String second = string;
          
          second[0] = 'a';
          
          std::cout << string << std::endl;
          std::cout << second << std::endl;
        }
        ```

    2. **don't allow copy constructor**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
        
            String(const String& other) = delete;  // don't allow copy constructor
        
            ~String()
            {
            	delete[] m_Buffer; 
            }
        
            char& operator[](unsigned int index)
            {
            	return m_Buffer[index];
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
            String string = "xiaoli";
            String second = string;  // Wrong!
        
            second[0] = 'a';
        
            std::cout << string << std::endl;
            std::cout << second << std::endl;
        }
        ```

    3. **deep copy: allocate new memory in the copy constructor**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
        
            String(const String& other)
            {
                m_Buffer = new char[m_Size + 1];  // allocate new memory
            	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
            }
        
            ~String()
            {
            	delete[] m_Buffer; 
            }
        
            char& operator[](unsigned int index)
            {
            	return m_Buffer[index];
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        int main()
        {
            String string = "xiaoli";
            String second = string;
        
            second[0] = 'a';
        
            std::cout << string << std::endl;  // aiaoli
            std::cout << second << std::endl;  // xiaoli
        }
        ```

    4. **how many times the copy happens**: 

        ```c++
        class String
        {
        private:
            char* m_Buffer;
            unsigned int m_Size;
        public:
            String(const char* string)
            {
                m_Size = strlen(string);
                m_Buffer = new char[m_Size + 1];
                memcpy(m_Buffer, string, m_Size);
                m_Buffer[m_Size] = 0;
            }
        
            String(const String& other)
            {
                std::cout << "Copied String!" << std::endl;
                m_Buffer = new char[m_Size + 1];  // allocate new memory
            	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
            }
        
            ~String()
            {
            	delete[] m_Buffer; 
            }
        
            char& operator[](unsigned int index)
            {
            	return m_Buffer[index];
            }
        
            friend std::ostream& operator<<(std::ostream& stream, const String& string);
        };
        
        void PrintString(String string)
        {
        	std::cout << string << std::endl;
        }
        
        int main()
        {
            String string = "xiaoli";
            String second = string;
        
            second[0] = 'a';
        
            PrintString(string);
            PrintString(second);
        }
        // output:
        // Copied String!
        // Copied String!
        // aiaoli
        // Copied String!
        // xiaoli
        
        // there are two more unnecessary "copy" operations because of the parameter of the "PrintString()" function
        ```

        change the parameter of the `function` to `reference (&)`: 

        ```c++
        // by using "reference", we can avoid unnecessary copy and directly using the existing "String" object
        // by using "const", not only we won't modify it in the function, but also we can pass temporary r-values in to the function (note: "r-value" will be introduced in the later chapter)
        void PrintString(const String& string)
        {
        	std::cout << string << std::endl;
        }
        // if we really need to copy in the "PrintString()" function, we can simply write:
        // void PrintString(const String& string)
        // {
        //   String copy = string;
        //   std::cout << string << std::endl;
        // }
        // so "always" pass your objects by "const reference" because we can decide copying in the function and in most cases it will be faster
        
        int main()
        {
            String string = "xiaoli";
            String second = string;
        
            second[0] = 'a';
        
            PrintString(string);
            PrintString(second);
        }
        // output:
        // Copied String!
        // aiaoli
        // xiaoli
        ```

