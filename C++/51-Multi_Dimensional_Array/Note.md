## 51. Multi-Dimensional Array

**Knowledge Points**: `create multi-dimensional array`, `delete multi-dimensitional array (notice the order)`, `how to avoid memory fragments`

### 1. 2D array

1. a `2D array` is an `array` of `arrays`, i.e., a collection of `pointers` to `arrays`

    ```c++
    int main()
    {
        int* array = new int[50];  // "int*" means a "pointer to a integer"
        int** a2d = new int*[50];  // "int**" means a "pointer" to a "pointer to a integer"
        // in fact, this two lines do the same thing: allocate 200-byte memory, we can actually leverage the allocated memory to do other things like storing some float variables
    }
    ```

2. note that the codes above havn't created a complete `2D array` because we **only** have the `pointers` but not `the lowest level arrays`

### 2. create and delete complete multi-dimensional arrays

1. **create**: 

    ```c++
    int main()
    {
        int** a2d = new int*[50];
        for (int i = 0; i < 50; i++)
        	a2d[i] = new int[50];
    
        //int*** a3d = new int**[50];
        //for (int i = 0; i < 50; i++)
        //	for (int j = 0; j < 50; j++)
        //		a3d[i][j] = new int[50];  // Wrong! runtime error
        // we ignore the "second level pointers"
      
        int*** a3d = new int**[50];
        for (int i = 0; i < 50; i++)
        {
        	a3d[i] = new int*[50];
            for (int j = 0; j < 50; j++)
            {
                a3d[i][j] = new int[50];
                // we can also write in this way: 
                //int** ptr = a3d[i];
                //ptr[j] = new int[50];
            }
        }
      
    	a3d[0][0][0] = 0;
    }
    ```

2. **delete**: 

    ```c++
    int main()
    {
    	// delete[] a2d;  // here we just delete the "50 pointers" of the top layer and there are "50 * 50 * 4 bytes memory" left
        for (int i = 0; i < 50; i++)
        	delete[] a2d[i];
        delete[] a2d;
      
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
                delete[] a3d[i][j];
            delete[] a3d[i];  // if you "delete[] a3d[i]" before "delete[] a3d[i][j]", there will be runtime error
        }
        delete[] a3d;
    }
    ```

3. **avoid memory fragments**: 

    **Problem**: The code above has created a lot of `memory fragments` and may cause `cache misses` because the `buffers` (the lowest dimensional arrays) are **not allocated together**.

    e.g., the 2-D array `a2d` first asks for `200-byte memory` for storing `50 pointers`, then each `pointer` points to a `200-byte memory` which stores `50 int-type data`, but these `50 separate buffers` of `50 int-type data` distributes separately but **not continuously**.

    If we iterate all these `2500 integers`, it will be much more **slower** than iterator a `one-dimensional array`.

    ```c++
    int main()
    {
        int* array = new int[50 * 50];
        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
    			array[j + i * 50] = 1;
    
        delete[] array;
    }
    // try to use the "Timer" to compare the speed
    ```

