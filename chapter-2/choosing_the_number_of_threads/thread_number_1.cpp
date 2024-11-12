#include <iostream>
#include <thread>
#include <vector>

void example_task(int thread_id) {
    std::cout << "Thread id: " << thread_id << " is running" << std::endl;
}

int main() {
    unsigned int num_threads = std::thread::hardware_concurrency();
    
    if (num_threads == 0) {
        num_threads = 2; // Default if hardware_concurrency() fails
    }

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(example_task, i);
    }

    // Join each thread to ensure they complete before main() exits
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads completed" << std::endl;
    return 0;
}
