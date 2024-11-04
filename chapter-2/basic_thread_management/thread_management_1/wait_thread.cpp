#include <iostream>
#include <thread>


void some_function() {
    int data = 42;
    std::thread my_thread([&data] {
        std::cout << "Data in the thread: " << data << std::endl;
    });
    my_thread.detach();   // `detach` allows `t` to run independently.
    // `data` goes out of scope here, potentially before `t` completes
};


// To solve this, ensure that either:

// Join the thread (using t.join()) so that it completes before data goes out of scope.
// Extend the lifetime of data (for example, by using dynamic allocation) so that it remains valid until the thread is done, or
//Use thread-safe techniques like mutexes or shared ownership (e.g., std::shared_ptr) for synchronized access and lifetime management of shared data.

// solution
#include <iostream>
#include <thread>
#include <chrono>

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
