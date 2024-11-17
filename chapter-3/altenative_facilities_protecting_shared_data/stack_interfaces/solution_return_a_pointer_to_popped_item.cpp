#include <memory>
#include <stack>          // For std::stack
#include <mutex> 

template<typename T>
class ThreadSafeStack {
private:
    std::stack<T> stack;
    mutable std::mutex m;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(m);
        stack.push(value);
    }

    void push(T&& value) {
        std::lock_guard<std::mutex> lock(m);
        stack.push(std::move(value));
    }

    // Option 3: Return a pointer to the popped value
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        auto result = std::make_shared<T>(std::move(stack.top()));
        stack.pop();
        return result;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return stack.empty();
    }
};
