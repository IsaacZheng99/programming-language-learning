## 36. Dynamic Array

**Knowledge Points**: `why need dynamic`, `common methods of std::vector<>`, `optimization of std::vector<>: reserve(), emplace_back()`

1. **why call std::vector as vector**: 

    I have searched for it and maybe it's just a naming mistake, and maybe it's better to call it "arraylist"

2. **why need dynamic**: 

    ```c++
    struct Vertex
    {
    	float x, y, z;
    };
    
    int main()
    {
        Vertex* vertices = new Vertex[500000];
        // if we simply set the initial size as many as possible, there will be huge waste if there is only several vertices, but if we set it too small, it won't satisfy the demands, therefore we need a dynamic container
    }
    ```

3. **simple usage of std::vector<>**: 

    ```c++
    #include <vector>
    
    struct Vertex
    {
    	float x, y, z;
    };
    
    // make sure passing the "std::vector" object by "reference", otherwise you will copy the entire array into this function
    void Function(const std::vector<Vertex>& vertices)
    {
      
    }
    
    std::ostream& operator<<(std::ostream& stream, const Vector3& vector3)
    {
        stream << vector3.x << ", " << vector3.y << ", " << vector3.z;
        return stream;
    }
    
    int main()
    {
        std::vector<Vertex> vertices;
        // unlike "Java", which can't take the primitive type as template type but should use types like "Integer", in "C++", we can use "int" as template type like "std::vector<int>"
        // generally, use "std::vector" to store the objects directly instead of the pointers which pointing to the objects, this is similar to the case of "stack" against "heap"
        vertices.push_back({ 1, 2, 3 });
        vertices.push_back({ 4, 5, 6 });
    
        Function(vertices);
    
        for (int i = 0; i < vertices.size(); i++)
        	std::cout << vertices[i] << std::endl;
    
        for (Vertex v : vertices)  // copy each "Vertex" object during the "for" loop
        	std::cout << v << std::endl;
    
        for (const Vertex& v : vertices)  // use "&" to avoid copying
        	std::cout << v << std::endl;
    
        vertices.erase(vertices.begin() + 1);  // remove the second element (notice the parameter of the "erase()" function)
    
    	vertices.clear();  // will set the array size back to 0
    }
    ```

4. **optimization of using std::vector<>**: 

    1. **problem**: 

        **frequent reallocation and copy**

        basically, you create a `vector`, then `push_back()` elements into that `vector`, if the capacity of the `vector` is **not** large enough to contain the new element you are trying to add, the `vector` needs to allocate **new** memory that is at least large enough to hold these new elements as well as the current contents in the `vector`, and **copy** everything across  from that old location of `memory` into the new location of `memory`, then `delete` that old location

        we want to **avoid** frequent reallocation and copy

    2. **too many copies**: 

        ```c++
        struct Vertex
        {
            float x, y, z;
        
            Vertex(float x, float y, float z)
            	: x(x), y(y), z(z)
            {
            }
        
            Vertex(const Vertex& vertex)  // copy constructor
            	: x(vertex.x), y(vertex.y), z(vertex.z)
            {
            	std::cout << "Copied!" << std::endl;
            }
        };
        
        int main()
        {
            std::vector<Vertex> vertices;
            vertices.push_back(Vertex(1, 2, 3));
            vertices.push_back(Vertex(4, 5, 6));
            vertices.push_back(Vertex(7, 8, 9));
            // in this case, you will see six "Copied!" printed
            // check the "capacity" of "vertices", you will see it increase from 0 to 1, then to 2, finally to 3
            // the first "Copied!" shows because we create a "Vertex" object "Vertex(1, 2, 3)" in the stack frame of the "main()" function, we need to copy the "Vertex(1, 2, 3)" object into the memory that "vertices" has allocated
            // if we can construct the "Vertex(1, 2, 3)" object in the actual memory that then "vertices" has actually allocated, we can optimize the first copy
            // for the second and the third "Copied!"s, one of them shows because of the same reason and the other shows because there is a "resize" and we need to copy the current content
            // for the last three "Copied!"s, they show because of the same reasons
            // if we can avoid frequently increasing capacity and reallocation, we can optimize a lot
        }
        ```

    3. **reserve() at the beginning**: 

        ```c++
        int main()
        {
            std::vector<Vertex> vertices;
            vertices.reserve(3);
            vertices.push_back(Vertex(1, 2, 3));
            vertices.push_back(Vertex(4, 5, 6));
            vertices.push_back(Vertex(7, 8, 9));
            // in this case, there will be three "Copied!" printed because we create the "Vertex" objects in the stack frame of the "main()" function and we need to copy them into the memory allocated by "vertices"
            // the decreased "Copied!" are due to we "reserve()" enough memory at the beginning and thus we don't need to "resize" and "copy" the old content
        }
        ```

    4. **emplace_back() to construct the object in place in the memory of the std::vector<>**: 

        ```c++
        int main()
        {
            std::vector<Vertex> vertices;
            vertices.reserve(3);
            vertices.emplace_back(1, 2, 3);
            vertices.emplace_back(4, 5, 6);
            vertices.emplace_back(7, 8, 9);
            // in this case, we are not passing a "Vertex" object we've constructed, we instead just pass the parameter list for the constructor, which tells the "vector": construct the "Vertex" object with the following parameters in place in our actual "vector" memory
            // in this case it will be much faster
        }
        ```

