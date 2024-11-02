#include <iostream>
#include <thread>

struct Worker {
    int data;

    Worker(int d) : data(d) {} // Constructor to initialize data

    void operator()() {
        std::cout << "Working with data: " << data << std::endl;
        data += 5; // Modify the copy in the thread
        std::cout << "Data after processing: " << data << std::endl;
    }
};

int main() {
    Worker worker(10); // Original object
    std::thread t(worker); // Thread gets a copy of `worker`

    t.join(); // Wait for the thread to finish
    std::cout << "Original data is still: " << worker.data << std::endl; // Original remains unchanged

    return 0;
}


struct Callable {
    int value; // Member variable

    Callable(int v) : value(v) {} // Constructor

    void operator()() {
        std::cout << "Thread ID: " << std::this_thread::get_id() 
                  << ", Value: " << value << std::endl;
        // Modify the value in the thread
        value += 10;
        std::cout << "Thread ID: " << std::this_thread::get_id() 
                  << ", Modified Value: " << value << std::endl;
    }
};

void createThread() {
    Callable myCallable(42); // Original object with value 42

    std::thread myThread(myCallable); // Copy of myCallable is created for the thread
    myThread.join(); // Wait for the thread to finish
}

int main() {
    createThread(); // Start the thread
    return 0;
}