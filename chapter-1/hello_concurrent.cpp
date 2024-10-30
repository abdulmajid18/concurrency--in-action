#include<iostream>
#include<thread>

void hello() {
    std::cout << "Hello Concurrent World!\n";
}

int main() {
    std::thread my_thread(hello);
    my_thread.join();
}