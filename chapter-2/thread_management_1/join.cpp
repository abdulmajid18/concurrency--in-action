#include <iostream>
#include <thread>
#include <chrono>

// Using join() guarantees that the main thread waits for t to complete before it exits, ensuring that data is still valid when printMessage accesses it.
void printMessage(int& data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Data from thread: " << data << std::endl;
}

int main() {
    int data = 42;

    std::thread t(printMessage, std::ref(data));  // Start the thread
    t.join();  // Wait for `t` to complete before `data` goes out of scope

    std::cout << "Main thread ending, data is safe." << std::endl;
    return 0;
}
