#include <iostream>
#include <thread>

void threadFunction() {
    std::cout << "Thread is running\n";
}

int main() {
    std::thread t1(threadFunction);  // Create a thread

    // Attempt to copy the thread
    // std::thread t2 = t1;  // This will cause a compilation error

    // Instead, you can move the thread
    std::thread t2 = std::move(t1);  // Move ownership to t2

    if (t2.joinable()) {
        t2.join();  // Join the moved thread
    }

    return 0;
}
