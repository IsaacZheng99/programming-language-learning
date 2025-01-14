## 11. Class

**Knowledge Points**: `class`, `struct`, `visibility`, 

1. **visibility**: 

    by default, a `class` makes everything private, which means only functions inside that class can access those variables

2. **what class can do**: 

    1. anything you can do with `classes`, you can also do without `classes`

        `class Player` has a `Move()` method: 

        ```c++
        class Player
        {
        public:
         	int x, y;
            int speed;
          
            void Move(int xa, int ya)
            {
                x += xa * speed;
                y += ya * speed;
            }
        };
        ```

        a stand-alone function: 

        ```c++
        void Move(Player& player, int xa, int ya)
        {
            player.x += xa * player.speed;
            player.y += ya * player.speed;
        }
        ```

    2. anything you can't do without `classes`, you can't do with `classes` either

    3. `class` is essentially a syntax suger

3. **only difference between class and struct technically**: 

    the default of `visibility` in `class` is `private`, but the default in `struct` is `public`, the only reason why `struct` still exists in `C++` is because of the backwards commatibility that it wants to maintain with `C`

    in fact, we can use `#define struct class` to solve this problem to some extent , but we need to be careful with the visibility

4. **which one to use**: 

    when talking about some kind of structure which just represents variables/data (e.g., `Plain Old Data` (`POD`)), we tend to use `struct`, when it comes to inheritance, we usually use `class`

    ```c++
    // just a vector variable/a strcture of data
    struct Vec2
    {
      float x, y;
      
      // we can have some methods, which just manipulates these variables but not does other things
      void Add(const& Vec2 other)
      {
        x += other.x;
        y += other.y;
      }
    };
    ```

5. **Write a Log class in C++** (check the `Code` part and note that this is not a good code but a simple and logical code)

    1. `private int m_LogLevel`: use `m_` to indicate this is a `private member variable` and helps distinguish it wich `local variables`

    