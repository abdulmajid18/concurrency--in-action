#include <memory>
#include <iostream>

void unique_ptr_demo() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);

    // Attempting to copy will cause a compilation error
    // std::unique_ptr<int> ptrCopy = ptr; // Error: std::unique_ptr is non-copyable

    // Moving is allowed
    std::unique_ptr<int> ptrMoved = std::move(ptr);

    if (ptr) {
        std::cout << "ptr still owns the resource\n";
    } else {
        std::cout << "ptr no longer owns the resource after move\n";
    }

    if (ptrMoved) {
        std::cout << "ptrMoved now owns the resource\n";
    }
}

int main() {
    unique_ptr_demo();
    return 0;
}
