#include <iostream>
#include <thread>

int main() {
    // Get the number of hardware threads
    unsigned int num_threads = std::thread::hardware_concurrency();
    
    // Display the number of threads
    if (num_threads != 0) {
        std::cout << "Number of hardware threads available: " << num_threads << std::endl;
    } else {
        std::cout << "Could not determine the number of hardware threads." << std::endl;
    }
    
    return 0;
}
