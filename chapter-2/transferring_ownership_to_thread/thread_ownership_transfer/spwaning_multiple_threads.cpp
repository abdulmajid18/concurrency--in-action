#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id) {
    std::cout << "Thread " << id << " is working\n";
}

void f() {
    std::vector<std::thread> threads;

    // Spawn 20 threads and add them to the vector
    for (unsigned i = 0; i < 20; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

    // Join all threads
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
}

int main() {
    f();
    return 0;
}
