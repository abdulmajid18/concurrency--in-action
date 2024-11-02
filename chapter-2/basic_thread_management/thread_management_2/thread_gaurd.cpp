#include <iostream>
#include <thread>

class ThreadGuard {
    std::thread& t;

public:
    explicit ThreadGuard(std::thread& t_) : t(t_) {}
    
    ~ThreadGuard() {
        if (t.joinable()) {
            t.join();
        }
    }

    // Deleted copy constructor and assignment operator
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

void threadFunction() {
    std::cout << "Thread is running on thread ID: " << std::this_thread::get_id() << std::endl;
}

void createThread() {
    std::thread t(threadFunction);
    ThreadGuard guard(t);  // ThreadGuard managing the thread
    // Uncommenting the line below would lead to compilation error
    // ThreadGuard guard2 = guard;  // Error: copy constructor is deleted
}

int main() {
    createThread();  // The thread is created and managed by the guard
    return 0;       // Upon exiting, guard goes out of scope and joins the thread
}
