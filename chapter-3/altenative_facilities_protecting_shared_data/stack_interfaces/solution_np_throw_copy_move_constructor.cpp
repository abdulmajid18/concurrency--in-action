#include <stack>          // For std::stack
#include <mutex>          // For std::mutex and std::lock_guard
#include <stdexcept>      // For std::runtime_error
#include <type_traits>    // For std::is_nothrow_move_constructible and std::is_nothrow_copy_constructible

template<typename T>
class ThreadSafeStack {
private:
    std::stack<T> stack;
    mutable std::mutex m;

public:
    // Static assertion to ensure the type T can be safely moved or copied without throwing exceptions
    static_assert(std::is_nothrow_move_constructible<T>::value ||
                  std::is_nothrow_copy_constructible<T>::value,
                  "Type must have a no-throw copy or move constructor");

    // Push by const reference (copy)
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(m);
        stack.push(value);
    }

    // Push by rvalue reference (move)
    void push(T&& value) {
        std::lock_guard<std::mutex> lock(m);
        stack.push(std::move(value));
    }

    // Pop by returning the value (requires move/copy constructor to be noexcept)
    // Option 2: Return by value (requires no-throw move/copy constructor)
    T pop() {
        std::lock_guard<std::mutex> lock(m);
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = std::move(stack.top());  // Move the top value
        stack.pop();
        return value;  // Return the moved value
    }

    // Check if the stack is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return stack.empty();
    }
};
