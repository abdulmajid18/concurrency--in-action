#include <iostream>
#include <thread>
#include <chrono>

void printMessage(int &data) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Data from thread: " << data << std::endl;
}

int main() {
    int data = 42;

    std::thread t(printMessage, std::ref(data)); // Start the thread, passing `data` by reference

    // Detach the thread, allowing it to run independently from the main thread
    t.detach();

    // End of `main` function, so `data` goes out of scope
    std::cout << "Main thread ending, data goes out of scope." << std::endl;

    // Simulate some delay to show possible issue
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    return 0;
}
