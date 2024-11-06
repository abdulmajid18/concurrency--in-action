#include<atomic>
#include<thread>
#include<iostream>
#include<vector>

struct Counters {
    std::atomic<size_t> counter1;
    std::atomic<size_t> counter2;
};

void increment_counter(std::atomic<size_t>& counter) {
    for (int i = 0; i < 1'000'000; ++i)
    {
        counter++;
    }
}

// int main() {
//     Counters counters;
//     counters.counter1 = 0;
//     counters.counter2 = 0;

//     std::vector<std::thread> threads;

//     for (int i = 0; i < 10; ++i) {
//         threads.emplace_back(increment_counter, std::ref(counters.counter1));
//         threads.emplace_back(increment_counter, std::ref(counters.counter2));
//     }

//     for (auto& t : threads) {
//         t.join();
//     }

//     std::cout << "Counter 1: " << counters.counter1 << std::endl;
//     std::cout << "Counter 2: " << counters.counter2 << std::endl;

//     return 0;
// }



int main() {
    Counters counters;

    std::thread t1(increment_counter, std::ref(counters.counter1));
    std::thread t2(increment_counter, std::ref(counters.counter2));

    t1.join();
    t2.join();

    std::cout << "Counter1: " << counters.counter1.load() << "\n";
    std::cout << "Counter2: " << counters.counter2.load() << "\n";

    return 0;
}