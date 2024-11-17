#include <stack>
#include <mutex>
#include <stdexcept>

template<typename T> 
class thread_safe_stack {
    private:
        std::stack<int> stack;
        mutable std::mutext m;

    public:

        void push(const T& value) {
            std::lock_guard<std::mutex> lock(m);
            stack.push(std::move(value));
        }

        void push(T&& value) {
            std::lock_guard<std::mutex> lock(m);
            stack.push(std::move(value));
        }

        // Option 1: Pass a reference to store the popped value
        void pop(T& result) {
            std::lock_guard<std::mutex> lock(m);
            if (stack.empty()) {
                throw std::runtime_error("Stack is empty");
            }
            result = std::move(stack.top());
            stack.pop();
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(m);
            return stack.e
        }
    };