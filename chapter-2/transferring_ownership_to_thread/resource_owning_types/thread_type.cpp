#include <thread>
#include <iostream>

void threadFunction() {
    std::cout << "Hello from thread\n";
}

void thread_demo() {
    std::thread t1(threadFunction);

    // Attempting to copy will cause a compilation error
    // std::thread t2 = t1; // Error: std::thread is non-copyable

    // Moving is allowed
    std::thread t2 = std::move(t1);

    if (t1.joinable()) {
        std::cout << "t1 is still managing the thread\n";
    } else {
        std::cout << "t1 no longer manages the thread after move\n";
    }

    if (t2.joinable()) {
        t2.join();
        std::cout << "t2 is managing the thread and has joined it\n";
    }
}

int main() {
    thread_demo();
    return 0;
}
