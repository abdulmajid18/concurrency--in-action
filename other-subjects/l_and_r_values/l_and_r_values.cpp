#include<iostream>
#include<vector>
#include<utility>



class Item {
    public:
        Item(int value): value(value) {
             std::cout << "Item created: " << value << std::endl;
        }
        Item(const Item& other) : value(other.value) {
            std::cout << "Item copied: " << value << std::endl;
        }
        Item(Item&& other) noexcept : value(other.value) {
            std::cout << "Item moved: " << value << std::endl;
            other.value = 0;  // Leave the moved-from object in a valid state
        }
        ~Item() {
            std::cout << "Item destroyed: " << value << std::endl;
        }

    public:
        int value;
};

class Stack {
public:
    // Using perfect forwarding
    template <typename T>
    void push(T&& item) {
        // Store the item in the vector, using move semantics if possible
        items.emplace_back(std::forward<T>(item));
    }

    // Using lvalue reference
    void push(Item& item) {
        items.emplace_back(item);  // This will copy the item
    }

    void printSize() const {
        std::cout << "Stack size: " << items.size() << std::endl;
    }

private:
    std::vector<Item> items;
};

int main() {
    Stack stack;

    // Pushing a temporary (rvalue) item
    stack.push(Item(1));  // This will invoke the move constructor

    // Pushing a named (lvalue) item
    Item item2(2);
    stack.push(item2);    // This will invoke the copy constructor

    // Check the size of the stack
    stack.printSize();

    // Pushing another temporary item
    stack.push(Item(3));  // Move constructor again

    return 0;
}