#include <string>
#include<iostream>
#include<thread>

void f(int i, std::string const& s) {
    std::cout << "Running" << std::endl;
}

// In this case, it’s the pointer to the local variable buffer B that’s passed through to the
// new thread c, and there’s a significant chance that the function oops will exit before
// the buffer has been converted to a std::string on the new thread, thus leading to
// undefined behavior. The solution is to cast to std::string before passing the buffer
// to the std::thread constructor:
void oops (int some_param) {
    char buffer[1024];
    sprintf(buffer, "Oops! %d\n", some_param);
    std::thread my_thread(f, 3, buffer);
    my_thread.detach();
}


// In this case, the problem is that you were relying on the implicit conversion of the
// pointer to the buffer into the std::string object expected as a function parameter,
// because the std::thread constructor copies the supplied values as is, without converting to the expected argument type
void not_oops (int some_param) {
    char buffer[1024];
    sprintf(buffer, "Not Opps! %d\n", some_param);
    std::thread my_thread(f, 3,std::string(buffer));
    my_thread.detach();
}