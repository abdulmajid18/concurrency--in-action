#include <iostream>

class MyClass {
public:
    int value;

    MyClass(int v) : value(v) {}  // Constructor

    // Copy constructor
    MyClass(const MyClass& other) : value(other.value) {
        std::cout << "Copy constructor called\n";
    }
};

int main() {
    MyClass obj1(42);               // Creating obj1
    MyClass obj2 = obj1;            // Copying obj1 to obj2 using the copy constructor

    std::cout << "obj1 value: " << obj1.value << "\n";
    std::cout << "obj2 value: " << obj2.value << "\n";

    return 0;
}
