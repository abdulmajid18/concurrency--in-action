#include <iostream>
#include <thread>

struct Callable {
    int& data; // Reference to an integer

    Callable(int& d) : data(d) {}

    void operator()() {
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", Data: " << data << std::endl;
    }
};

void createThread() {
    int value = 42; // Local variable
    Callable myCallable(value); // Create callable object

    std::thread myThread(myCallable); // The callable object is copied into the thread

    // The original `myCallable` can be destroyed here safely
    // because `myThread` has its own copy of it.
    myThread.detach(); // Now the thread runs independently
}

int main() {
    createThread();
    // Since the thread runs independently, the program may exit before the thread finishes.
    // To see output, we can introduce a sleep, or we could join the thread instead of detach.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
