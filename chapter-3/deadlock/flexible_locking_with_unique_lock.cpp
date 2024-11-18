#include <iostream>
#include <mutex>
#include <thread>

class SomeBigObject {
    int data;

public:
    explicit SomeBigObject(int d) : data(d) {}
    friend void swap(SomeBigObject& lhs, SomeBigObject& rhs) {
        std::swap(lhs.data, rhs.data);
    }
    void print() const {
        std::cout << "Data: " << data << std::endl;
    }
};

class X {
private:
    SomeBigObject some_detail;
    std::mutex m;

public:
    explicit X(SomeBigObject const& sd) : some_detail(sd) {}

    friend void swap(X& lhs, X& rhs) {
        if (&lhs == &rhs) return;

        // Defer locking the mutexes initially
        std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);

        // Lock both mutexes without deadlock
        std::lock(lock_a, lock_b);

        // Swap the internal data
        swap(lhs.some_detail, rhs.some_detail);
    }

    void print() const {
        some_detail.print();
    }
};

// Demo
int main() {
    X obj1(SomeBigObject(10));
    X obj2(SomeBigObject(20));

    std::cout << "Before swap:" << std::endl;
    obj1.print();
    obj2.print();

    // Perform swap
    swap(obj1, obj2);

    std::cout << "After swap:" << std::endl;
    obj1.print();
    obj2.print();

    return 0;
}
