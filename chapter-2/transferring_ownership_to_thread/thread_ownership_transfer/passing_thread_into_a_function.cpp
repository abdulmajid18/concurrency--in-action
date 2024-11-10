#include <iostream>
#include <thread>

void some_function() {
    std::cout << "Hello from Some Function thread\n";
}

// Function accepting a thread by value
void f(std::thread t) {
    t.join();  // Ensure the thread is joined when the function scope ends
}

void g() {
    // Create a thread and pass it by value to f()
    f(std::thread(some_function));  // Pass a temporary thread by value

    std::thread t(some_function);  // Create another thread
    f(std::move(t));  // Move ownership of t to f()
}

int main() {
    g();  // Call g to run the threads
    return 0;
}
