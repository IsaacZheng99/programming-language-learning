## 11. Class

**Knowledge Points**:

1. `visibility: private by default`
2. `what can a class do: syntax suger`
3. `calss and struct: visibility; POD`
4. `write a C++ class: class Log`

### 1. Visibility

By default, a `class` makes everything `private`, which means only `functions` **inside** that `class` can access those `variables`.

### 2. What can a class do

1. Anything we can do with `classes`, we can also do **without** `classes`.

    For example, the `class Player` has a `Move()` `method`: 

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

    We can also implement a stand-alone `Move()` `function`:

    ```c++
    void Move(Player& player, int xa, int ya)
    {
        player.x += xa * player.speed;
        player.y += ya * player.speed;
    }
    ```

2. Anything we can't do without `classes`, we can't do with `classes` either.

3. Essentially speaking, `class` is a **syntax suger**.

### 3. Comparison between class and struct

#### 1. Only difference between class and struct technically

1. The default of `visibility` in `class` is `private`, but the default in `struct` is `public`, the only reason why `struct` still exists in `C++` is because of the **backwards compatibility** that it wants to maintain with `C`.
2. In fact, we can use `#define struct class` to solve this problem to some extent , but we need to be careful with the `visibility`.

#### 2. Which one to use

When talking about some kind of structure which **just** represents `variables`/data (e.g., `Plain Old Data` (`POD`)), we tend to use `struct`, when it comes to **inheritance**, we usually use `class`.

```c++
// just a vector variable/a strcture of data
struct Vec2
{
  float x, y;
  
  // we can have some methods, which just manipulate these variables but not do other things
  void Add(const& Vec2 other)
  {
    x += other.x;
    y += other.y;
  }
};
```

### 3. Write a Log class in C++

(Check the `Code` part and note that this is not a good code but a simple and logical code)

1. A good way to create a `class` or design an `API` is by its **usage**.
1. `Private member variable`: for `private int m_LogLevel`, use `m_` to indicate this is a `private member variable` and help distinguish it from `local variables`.

