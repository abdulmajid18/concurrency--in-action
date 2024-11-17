#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void thread1()
{
    // Always lock mutexA first, then mutexB
    std::lock_guard<std::mutex> lock1(mutexA);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate some work
    std::lock_guard<std::mutex> lock2(mutexB);
    std::cout << "Thread 1 is working with both resources\n";
}

void thread2()
{
    // Always lock mutexA first, then mutexB
    std::lock_guard<std::mutex> lock1(mutexA);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate some work
    std::lock_guard<std::mutex> lock2(mutexB);
    std::cout << "Thread 2 is working with both resources\n";
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
