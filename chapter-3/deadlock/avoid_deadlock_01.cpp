#include <iostream>
#include <mutex>
#include <algorithm> 

class some_big_object {
public:
    some_big_object() {}
    some_big_object(const some_big_object&) = default;
    some_big_object& operator=(const some_big_object&) = default;
    void print() const { std::cout << "Big object details" << std::endl; }
};

class X {
private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const& sd) : some_detail(sd) {}

    friend void swap(X& lhs, X& rhs) {
        if (&lhs == &rhs) return; // Don't swap if same object
        
        // Lock both mutexes simultaneously to avoid deadlock
        std::lock(lhs.m, rhs.m);
        
        // Adopt locks without trying to lock the mutexes again
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);

        // Swap the details of the objects
        std::swap(lhs.some_detail, rhs.some_detail);
        
        std::cout << "Swapped details of X objects" << std::endl;
    }

    void print_details() const {
        some_detail.print();
    }
};

int main() {
    some_big_object obj1, obj2;
    X x1(obj1), x2(obj2);
    
    x1.print_details();
    x2.print_details();

    // Swap the two objects
    swap(x1, x2);

    x1.print_details();
    x2.print_details();

    return 0;
}
