#include<iostream>
#include<thread>

struct Data {
    int x;
    int y;
};

Data data1, data2;

void thread1() {
    while (true) {
        data1.x++;
    }
}

void thread2() {
    while (true) {
        data2.y++;
    }
}

// Even though thread1 and thread2 access different variables, 
// if data1.x and data2.y happen to be on the same cache line, false sharing can occur

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    std::cout << "data1.x: " << data1.x << ", data2.y: " << data2.y << std::endl;

    return 0;
}

constexpr size_t CACHE_LINE_SIZE = 64;

// fix
struct Data {
    int x;
    char padding[CACHE_LINE_SIZE - sizeof(int)];
    int y;
};