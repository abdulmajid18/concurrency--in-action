#include<iostream>
#include<thread>

void some_fucntion() {
    std::cout << "some_fucntion" << std::endl;
}

void some_other_fucntion() {
    std::cout << "some_other_fucntion" << std::endl;
}

int main() {
    std::thread t1(some_fucntion);

    std::thread t2 = std::move(t1);

    t1 = std::thread(some_other_fucntion);

    std::thread t3;

    t3 = std::move(t2);
    t1 = std::move(t3);
}
