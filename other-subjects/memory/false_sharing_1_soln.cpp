#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

struct alignas(64) PaddedCounter {
    std::atomic<size_t> counter;
    char padding[64 - sizeof(std::atomic<size_t>)];  // Ensures each instance takes up a full cache line
};

struct Counters {
    PaddedCounter counter1;
    PaddedCounter counter2;
};

void increment_counter(PaddedCounter& counter) {
    for (int i = 0; i < 1'000'000; ++i) {
        ++counter.counter;
    }
}

int main() {
    Counters counters;

    std::thread t1(increment_counter, std::ref(counters.counter1));
    std::thread t2(increment_counter, std::ref(counters.counter2));

    t1.join();
    t2.join();

    std::cout << "Counter1: " << counters.counter1.counter.load() << "\n";
    std::cout << "Counter2: " << counters.counter2.counter.load() << "\n";

    return 0;
}
