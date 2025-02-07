## 49. Thread

**Knowledge Points**: `thread joining: worker.join();`

### 1. thread joining

`thread joining`: block the `current thread` and wait until the `joined thread` finishes

### 2. an example

**Demand**: we want to print `Working...` all the time until we press the `enter`

1. write `std::cin.get()` in the `while loop`, and in this case we are actually doing the two things in just **one** thread and it can't achieve the goal

    ```c++
    void DoWork()
    {
        while (true)
        {
            std::cout << "Working...\n";
            std::cin.get();
        }
    }
    
    
    int main()
    {
        std::thread worker(DoWork);
    
        worker.join();
    }
    // outputs:
    // Working...
    ```

2. introduce a `global variable` to control the printing and use **two** threads to complete the goal (`inter-thread communication by condition variables`)

    ```c++
    static bool s_Finished = false;
    
    void DoWork()
    {
        using namespace std::literals::chrono_literals;
    
        std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
    
        while (!s_Finished)
        {
            std::cout << "Working...\n";
            std::this_thread::sleep_for(1s);
        }
    }
    
    
    int main()
    {
        std::thread worker(DoWork);
    
        std::cin.get();  // manually block the "main thread"
        s_Finished = true;
    
        worker.join();  // wait for the "worker thread" finishes because if the "main thread" exits directly, it may compulsorily stop the "worker thread" and thus cause "undefined behaviour"
    
        std::cout << "Finished!" << std::endl;
        std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
    }
    // outputs:
    // Started thread id = 13340
    // Working...
    // Working...
    // Working...
    // 
    // Finished
    // Started thread id = 11700
    ```

