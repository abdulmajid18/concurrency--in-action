#include <iostream>
#include <utility>

class MyClass {
public:
    MyClass() { std::cout << "Default constructor\n"; }
    MyClass(const MyClass&) { std::cout << "Copy constructor\n"; }
    MyClass(MyClass&&) noexcept { std::cout << "Move constructor\n"; }
};

template <typename T>
void process(T&& obj) {
    // Forwarding obj to another function
    anotherFunction(std::forward<T>(obj));
}

void anotherFunction(MyClass obj) {
    // Processing...
}

int main() {
    MyClass a;
    process(a); // Calls copy constructor
    process(MyClass()); // Calls move constructor
    return 0;
}