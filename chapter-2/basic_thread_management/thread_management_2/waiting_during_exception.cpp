#include<iostream>
#include<thread>

struct func;

void do_something(int& i) {
    std::cout << "Thread #" << std::this_thread::get_id() << ": " << i << std::endl;
}

void do_something_in_current_thread() {
     std::cout << "Thread in Current Thread #" << std::this_thread::get_id() << std::endl;
}

struct func {
    int& i;
    func(int& i_):i(i_) {}

    void operator() () {
        do_something(i);
    }
};

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);

    try {
        do_something_in_current_thread();
    }
    catch (...) {
        my_thread.join();
        throw;
    };
    my_thread.join();

}