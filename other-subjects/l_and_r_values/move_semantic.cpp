#include <iostream>
#include <vector>
#include <utility>

class MyClass {
public:
    MyClass() { std::cout << "Default constructor\n"; }
    MyClass(const MyClass&) { std::cout << "Copy constructor\n"; }
    MyClass(MyClass&&) noexcept { std::cout << "Move constructor\n"; }
};

void process(MyClass obj) {
    // Processing...
}

int main() {
    MyClass a;
    process(std::move(a)); // Calls move constructor
    return 0;
}