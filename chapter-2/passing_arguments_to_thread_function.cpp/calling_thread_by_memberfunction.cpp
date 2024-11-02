#include <iostream>
#include <thread>

class X {
public:
    void do_lengthy_work(int times) {
        for (int i = 0; i < times; ++i) {
            std::cout << "Working... (" << i + 1 << ")\n";
        }
    }
};

int main() {
    X my_x;
    std::thread t(&X::do_lengthy_work, &my_x, 5); // `5` is the argument for `do_lengthy_work`
    
    t.join(); // Wait for the thread to complete

    std::cout << "Thread completed.\n";
    return 0;
}
