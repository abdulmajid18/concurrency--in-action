#include <iostream>
#include <thread>
#include <memory>

class BigObject {
    public:
        void prepare_data(int data) {
            std::cout << "Preparing data with value: " << data << std::endl;
        }
};

void process_big_object(std::unique_ptr<BigObject> obj) {
    std::cout << "Processing BigObject on a separate thread: " << std::endl;
}

int main() {
    // std::unique_ptr<BigObject> p(new BigObject);
    std::unique_ptr<BigObject> p = std::make_unique<BigObject>();
    p -> prepare_data(42);

    std::thread my_thread(process_big_object, std::move(p));  // Transfer ownership to the thread
    my_thread.join();  // Wait for the thread to complete

    // p is now a null pointer since ownership has been moved
    if (!p) {
        std::cout << "BigObject has been moved, and is now nullptr." << std::endl;
    }

    return 0;

}