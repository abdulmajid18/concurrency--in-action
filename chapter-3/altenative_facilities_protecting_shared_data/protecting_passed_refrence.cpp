#include <iostream>
#include <mutex>
#include <string>
#include <functional>

class some_data {
    int a;
    std::string b;

public:
    void do_something() {
        std::cout << "Doing something with some_data.\n";
    }
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template<typename Function>
    void process_data(Function func) {
        std::lock_guard<std::mutex> l(m);
        auto data_copy = data; // Pass a copy
        func(data_copy);
    }
};

void safe_function(some_data data_copy) {
    data_copy.do_something(); // Works on a copy
}

int main() {
    data_wrapper x;

    // Pass a safe function
    x.process_data(safe_function);

    return 0;
}
