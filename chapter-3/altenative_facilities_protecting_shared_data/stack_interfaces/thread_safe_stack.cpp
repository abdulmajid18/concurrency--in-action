#include <exception>
#include <memory>
#include <stack>
#include <mutex>

// Exception thrown when popping from an empty stack.
struct empty_stack : public std::exception
{
    const char* what() const throw() override {
        return "Stack is empty";
    }
};

// Thread-safe stack implementation.
template<typename T>
class threadsafe_stack {
private:
    std::stack<T> stack;           // The underlying stack.
    mutable std::mutex m;          // Mutex to protect access to the stack.

public:
    threadsafe_stack() = default;

    // Copy constructor.
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other.m);  // Lock the other stack before copying
        stack = other.stack;
    }

    // Deleted copy assignment operator.
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    // Push a new value onto the stack.
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);  // Lock to ensure thread-safety
        stack.push(std::move(new_value));     // Move the value into the stack
    }

    // Pop a value from the stack and return it via a shared_ptr.
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);  // Lock to ensure thread-safety
        if (stack.empty()) {
            throw empty_stack();  // Throw if the stack is empty
        }

        // Get a pointer to the top element, then pop it.
        std::shared_ptr<T> const res = std::make_shared<T>(std::move(stack.top()));
        stack.pop();
        return res;
    }

    // Pop a value from the stack and store it in the provided reference.
    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);  // Lock to ensure thread-safety
        if (stack.empty()) {
            throw empty_stack();  // Throw if the stack is empty
        }

        // Move the top element to the provided reference and pop it.
        value = std::move(stack.top());
        stack.pop();
    }

    // Check if the stack is empty.
    bool empty() const {
        std::lock_guard<std::mutex> lock(m);  // Lock to ensure thread-safety
        return stack.empty();
    }
};
