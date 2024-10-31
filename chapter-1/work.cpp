#include<thread>
#include<iostream>

void do_some_work() {
    std::cout << "Doing some work!\n";
}

int main() {
    std::thread my_thread(do_some_work);
    my_thread.join();
    return 0;
}