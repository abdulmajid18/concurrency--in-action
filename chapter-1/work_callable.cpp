#include<iostream>
#include<thread>

class backgroud_task {
    public:
        void operator() () {
            do_something();
            do_something_else();
        }

        void do_something() {
            std::cout << "Doing some work in the background...\n";
        }

        void do_something_else() {
            std::cout << "Doing something else in the background...\n";
        }
};

backgroud_task task;
std::thread my_thread(task);