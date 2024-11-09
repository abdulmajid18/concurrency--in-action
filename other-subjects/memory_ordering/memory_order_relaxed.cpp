#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> event_count{0};

void increment() {
    for (int i = 0; i < 1000; ++i) {
        event_count.fetch_add(1, std::memory_order_relaxed); // Increment count with relaxed ordering
    }
}

void print_count() {
    int count = event_count.load(std::memory_order_relaxed); // Load count with relaxed ordering
    std::cout << "Event count: " << count << std::endl;
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    print_count();
    return 0;
}