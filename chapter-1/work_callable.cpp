#include<iostream>
#include<thread>

class background_task {
    public:
        void operator() () {
            do_something();
            do_something_else();
        }

        void do_something() {
            std::cout << "Doing some work in the background...\n";
        }

        void do_something_else() {
            std::cout << "Doing something else in the background...\n";
        }
};
// Use a Named Variable: Define the function object in a named variable first
background_task task;
std::thread my_thread(task);

// Extra Parentheses: Use an additional set of parentheses
std::thread my_thread((background_task()));

// Uniform Initialization Syntax: Use curly braces to initialize your object
std::thread my_thread{background_task()};

//  DOnt do this Avoid this
// When you mistakenly write std::thread my_thread(background_task());, the compiler interprets this line as a function declaration rather than the intended creation of a thread. 
// Specifically, it declares a function named my_thread that takes no parameters and returns a std::thread. Here’s what can happen as a result:
// No Thread Created: Since the line does not actually create a std::thread object, no new thread will be spawned to execute the background_task. 
// This means any intended concurrent execution of tasks will not occur, potentially leading to a logic error in your program.
// Function Signature: The declaration creates a function prototype. If you try to use my_thread as if it were a std::thread object (e.g., calling my_thread.join()), 
// you'll encounter a compilation error because my_thread is a function and not an instance of std::thread.
// Compiler Confusion: This misinterpretation can lead to confusion when debugging, as the behavior of the program won't match your intentions. 
// The intended functionality (concurrent execution) will not take place, but there will be no immediate errors unless you attempt to use my_thread in a manner appropriate for a thread
std::thread my_thread(background_task());

void do_something() {
        std::cout << "Doing some work in the background...\n";
    }

void do_something_else() {
    std::cout << "Doing something else in the background...\n";
}

// In this version, std::thread is initialized with a lambda function ([] { ... }), which defines the thread’s actions directly in the constructor.
std::thread my_threads([] {
    do_something();
    do_something_else();
});

 