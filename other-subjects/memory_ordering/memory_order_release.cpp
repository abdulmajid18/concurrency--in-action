#include<atomic>
#include<iostream>
#include<thread>
#include<vector>
#include<memory>


std::atomic<int> write_index;
int buffer[10];
std::atomic<bool> ready{false};

void producer() {
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i; // Prepare data
    }
    write_index.store(10, std::memory_order_release); // Release the write index
    ready.store(true, std::memory_order_release); // Signal that data is ready
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)); // Wait for producer
    int index = write_index.load(std::memory_order_acquire); // Acquire the write index
    std::cout << "Consumed index: " << index << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}