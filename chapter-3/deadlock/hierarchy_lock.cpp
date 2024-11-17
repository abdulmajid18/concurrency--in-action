#include <mutex>
#include <iostream>
#include <stdexcept>
#include <thread>

class HierarchicalMutex {
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation() {
        if (this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error("Mutex hierarchy violated");
        }
    }

    void update_hierarchy_value() {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

public:
    explicit HierarchicalMutex(unsigned long value)
        : hierarchy_value(value), previous_hierarchy_value(0) {}

    void lock() {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock() {
        if (this_thread_hierarchy_value != hierarchy_value) {
            throw std::logic_error("Mutex hierarchy violated during unlock");
        }
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }

    bool try_lock() {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) {
            return false;
        }
        update_hierarchy_value();
        return true;
    }
};

thread_local unsigned long HierarchicalMutex::this_thread_hierarchy_value = ULONG_MAX;

// Example usage
HierarchicalMutex high_level_mutex(1000);
HierarchicalMutex medium_level_mutex(500);
HierarchicalMutex low_level_mutex(100);

void high_level_function() {
    std::lock_guard<HierarchicalMutex> lock(high_level_mutex);
    std::cout << "High level function executed.\n";
}

void medium_level_function() {
    std::lock_guard<HierarchicalMutex> lock(medium_level_mutex);
    std::cout << "Medium level function executed.\n";
    high_level_function(); // Calls function with a higher hierarchy
}

void low_level_function() {
    std::lock_guard<HierarchicalMutex> lock(low_level_mutex);
    std::cout << "Low level function executed.\n";
    medium_level_function(); // Calls function with a higher hierarchy
}

int main() {
    try {
        std::thread t1(low_level_function);
        t1.join();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}
