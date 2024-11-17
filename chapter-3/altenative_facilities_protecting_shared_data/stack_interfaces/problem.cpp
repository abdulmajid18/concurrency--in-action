#include <iostream>
#include <mutex>
#include <thread>
#include <stack>
#include <chrono>


std::stack<int>  shared_stack;

void do_something(int value) {
    std::cout << "Processing value: " << value << std::endl;
}

// Multi-threaded Case (Unsafe):

// When multiple threads operate on the same stack, the following can happen:
// Thread A checks !shared_stack.empty() and finds it true.
// Thread B does the same.
// Both threads read the same value from shared_stack.top().
// Both threads then call shared_stack.pop(), causing one value to be skipped or processed incorrectly.

void unsafe_thread_access(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        if (!shared_stack.empty()) {
            int value = shared_stack.top();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            shared_stack.pop();
            std::cout << "Thread " << thread_id << " popped: " << value << "\n";
            do_something(value); // Process the value
        }  else {
            std::cout << "Thread " << thread_id << " found the stack empty.\n";
        }
     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

std::mutex stack_mutext;

int pop_and_process() {
    std::lock_guard<std::mutex> lock(stack_mutext);
    if (shared_stack.empty())
        throw std::runtime_error("stack is empty");
    int value = shared_stack.top();
    shared_stack.pop();
    return value;;
}

void safe_thread_access(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        try {
            int value = pop_and_process();
            std::cout << "Thread " << thread_id << " popped: " << value << "\n";
            do_something(value);
        } catch (const std::runtime_error& e) {
            std::cout << "Thread " << thread_id << " found the stack empty.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Simulate work
    }
}

int main() {
    // Initialize the stack with some values
    for (int i = 1; i <= 5; ++i) {
        shared_stack.push(i);
    }

    // Start two threads operating on the shared stack
    std::thread t1(unsafe_thread_access, 1);
    std::thread t2(unsafe_thread_access, 2);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}