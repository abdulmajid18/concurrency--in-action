#include <iostream>
#include <thread>


void some_function() {
    int data = 42;
    std::thread my_thread([&data] {
        std::cout << "Data in the thread: " << data << std::endl;
    });
    my_thread.detach();
};