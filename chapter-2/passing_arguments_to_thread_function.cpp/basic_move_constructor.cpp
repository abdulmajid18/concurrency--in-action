#include<iostream>
#include<utility>

class Resource {
    int* data;
    size_t size;

    public:
        Resource(size_t s) : size(s), data(new int[s]){
            std::cout << "Constructing Resource with size " << size << std::endl;
        }

        ~Resource() {
            delete[] data;
            std::cout << "Destroying Resource" << std::endl;
        }

        // copy constrctor
        Resource(const Resource& other) : size(other.size), data(new int[other.size]) {
            std::cout << "Copy Constructing Resource" << std::endl;
            std::copy(other.data, other.data + size, data);
        }

        Resource(Resource&& other) noexcept : size(other.size), data(other.data) {
            std::cout << "Move Constructing Resource" << std::endl;
            other.data = nullptr;
            other.size = 0;
        }

        // Copy Assignment Operator
        Resource& operator=(const Resource& other) {
            if (this != &other) {
                delete[] data; // Free existing data
                size = other.size;
                data = new int[size];
                std::copy(other.data, other.data + size, data);
                std::cout << "Copy Assigning Resource" << std::endl;
            }
            return *this;
        }

        // Move Assignment Operator
        Resource& operator=(Resource&& other) noexcept {
            if (this != &other) {
                delete[] data; // Free existing data
                size = other.size;
                data = other.data;
                other.data = nullptr;
                other.size = 0;
                std::cout << "Move Assigning Resource" << std::endl;
            }
            return *this;
        }
};


int main() {
    // Creating a Resource instance
    Resource res1(10); // Calls the constructor

    // Move constructing a new Resource instance
    Resource res2(std::move(res1)); // Calls the move constructor

    // Creating another Resource instance
    Resource res3(20);

    // Move assigning res2 to res3
    res3 = std::move(res2); // Calls the move assignment operator

    return 0;
}