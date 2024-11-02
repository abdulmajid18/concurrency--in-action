#include <iostream>
#include <thread>
#include <chrono> // Include for std::chrono
#include <cassert>

void do_background_work() {
    std::cout << "Hello Concurrent World!\n";
}

int main() {
    std::thread my_thread(do_background_work); // Create a new thread
    my_thread.detach(); // Detach the thread

    // Wait for a short duration to allow the detached thread to finish
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust the time as needed
    
    assert(!my_thread.joinable()); // Check that my_thread is no longer joinable
    return 0; // Main thread exits
}
