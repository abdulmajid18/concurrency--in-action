#include <iostream>
#include <thread>
#include <mutex>

int shared_counter = 0;
std::mutex mtx;


void increment_counter(int count) {
    for (int i = 0; i < count; i++) {
        mtx.lock();
        ++shared_counter;
        mtx.unlock();
    }
}

void incrementCounter(int numIncrements) {
    for (int i = 0; i < numIncrements; ++i) {
        std::lock_guard<std::mutex> guard(mtx); // Automatically locks and unlocks
        ++shared_counter;
    }
}


int main() {
    const int numIncrements = 10000;

    // Create two threads that increment the counter
    std::thread t1(increment_counter, numIncrements);
    std::thread t2(increment_counter, numIncrements);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Output the final value of sharedCounter
    std::cout << "Final value of sharedCounter: " << shared_counter << std::endl;

    return 0;
}