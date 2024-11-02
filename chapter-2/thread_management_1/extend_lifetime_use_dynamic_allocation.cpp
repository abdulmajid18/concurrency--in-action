#include <iostream>
#include <thread>
#include <chrono>

void printMessage(int* data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Data from thread: " << *data << std::endl;
}

int main() {
    int* data = new int(42);  // Dynamically allocate `data`

    std::thread t(printMessage, data);  // Pass `data` pointer to thread
    t.detach();  // Detach the thread

    std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Ensure thread completes
    delete data;  // Free memory only after the thread is done

    std::cout << "Main thread ending, data safely deleted." << std::endl;
    return 0;
}
