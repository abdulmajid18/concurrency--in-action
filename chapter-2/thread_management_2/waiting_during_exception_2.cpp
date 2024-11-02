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

// This pattern is helpful for RAII (Resource Acquisition Is Initialization) management, which ensures
// that resources (like threads) are properly cleaned up when they are no longer needed. In this case,
// thread_guard takes responsibility for the thread and guarantees that it will be joined, avoiding
// potential issues if the thread outlives its intended lifetime or accidentally tries to access invalid resources.
class thread_gaurd {
    std::thread& t;

    public:
        explicit thread_gaurd(std::thread& t_) : t(t_) {}
        ~thread_gaurd() {
            if (t.joinable()) {
                t.join();
            }
        }
        thread_gaurd(thread_gaurd const&) = delete;
        thread_gaurd& operator=(thread_gaurd const&)=delete;
};

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    thread_gaurd gaurd(my_thread);
    
    do_something_in_current_thread();

}