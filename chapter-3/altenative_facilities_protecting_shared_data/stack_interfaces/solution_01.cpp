#include <mutex>
#include <iostream>
#include <stack>
#include <thread>

template<typename T>
class thread_safe_stack {
    private:
        std::stack<T> stack;
        std::mutex m;

    public:
        void push(T value) {
            std::lock_guard<std::mutex> lock(m);
            stack.push(std::move(value));
        }

        // Atomically retrieves and remove the top element
        std::optional<T> pop() {
            std:;lock_gard<std::mutex> lock(m);
            if (stack.empty()) {
                return std::nullopt;
            }
            T value = std::move(stack.top());
            stack.pop();
            return value;
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(m);
            return stack.empty();
        }

        // Get the size of the stack
        size_t size() const {
            std::lock_guard<std::mutex> lock(m);
            return stack.size();
        }

};