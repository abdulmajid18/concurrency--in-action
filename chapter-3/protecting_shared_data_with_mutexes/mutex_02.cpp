#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <algorithm>


std::list<int>  some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> gtuard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}


void writer_thread(int id) {
    for (int i = 1; i <= 10; ++i) {
        add_to_list(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate work
    }
}

void reader_thread(int id) {
    for (int i = 1; i <= 10; ++i) {
        if (list_contains(i)) {
            std::cout << "Thread " << id << " found " << i << "\n";
        } else {
            std::cout << "Thread " << id << " did not find " << i << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Simulate work
    }
}

int main() {
    std::thread t1(writer_thread, 10);
    std::thread t2(reader_thread, 1);
    std::thread t3(reader_thread, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}