#include <iostream>
#include <thread>

class scoped_thread {
public:
    // Constructor accepts a std::thread by value and takes ownership
    explicit scoped_thread(std::thread t) : t_(std::move(t)) {
        // Check if the thread is valid before proceeding
        if (!t_.joinable()) {
            throw std::logic_error("Thread must be joinable");
        }
    }

    // Destructor automatically joins the thread if it's joinable
    ~scoped_thread() {
        if (t_.joinable()) {
            t_.join();  // Ensure the thread finishes before the scope ends
        }
    }

    // Disable copy constructor and copy assignment to prevent multiple ownerships
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;

    // Enable move constructor and move assignment
    scoped_thread(scoped_thread&& other) noexcept : t_(std::move(other.t_)) {}

    scoped_thread& operator=(scoped_thread&& other) noexcept {
        if (this != &other) {
            if (t_.joinable()) {
                t_.join();  // Join the current thread if needed
            }
            t_ = std::move(other.t_);  // Move the thread from the other object
        }
        return *this;
    }

private:
    std::thread t_;
};

// A simple function to be run by a thread
void some_function() {
    std::cout << "Hello from the thread\n";
}

int main() {
    try {
        // Create a thread and pass it to scoped_thread
        scoped_thread st1(std::thread(some_function));

        // Another example with move semantics
        std::thread t2(some_function);
        scoped_thread st2(std::move(t2));  // Transfer ownership

        // After this, t2 is no longer valid and cannot be used

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
