#include <iostream>
#include <thread>

// Function to be run by thread f
void some_function() {
    std::cout << "Hello from Some Function thread\n";
}

// Function to be run by thread g, with an argument
void some_other_function(int x) {
    std::cout << "Hello from Some Other Function thread with argument " << x << "\n";
}

std::thread f() {
    // Create and return a thread that runs some_function
    return std::thread(some_function);
}

std::thread g() {
    // Create and return a thread that runs some_other_function with an argument
    return std::thread(some_other_function, 42);
}

int main() {
    // Create threads using f() and g()
    std::thread t1 = f();
    std::thread t2 = g();

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}
