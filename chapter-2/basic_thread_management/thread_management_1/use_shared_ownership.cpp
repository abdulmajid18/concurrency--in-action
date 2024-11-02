#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

void printMessage(std::shared_ptr<int> data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Data from thread: " << *data << std::endl;
}

int main() {
    auto data = std::make_shared<int>(42);  // Create `data` with shared ownership

    std::thread t(printMessage, data);  // Pass `data` to the thread
    t.detach();  // Detach the thread

    std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Ensure thread completes

    std::cout << "Main thread ending, data safely managed by shared_ptr." << std::endl;
    return 0;
}
