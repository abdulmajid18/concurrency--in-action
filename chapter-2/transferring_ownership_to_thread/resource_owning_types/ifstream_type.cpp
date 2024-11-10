#include <fstream>
#include <iostream>

void ifstream_demo() {
    std::ifstream file("example.txt");

    // Attempting to copy will cause a compilation error
    // std::ifstream fileCopy = file; // Error: std::ifstream is non-copyable

    // Moving is allowed
    std::ifstream fileMoved = std::move(file);

    // After moving, `file` no longer has access to the file, but `fileMoved` does
    if (file) {
        std::cout << "file is still open\n";
    } else {
        std::cout << "file is no longer valid after move\n";
    }

    if (fileMoved) {
        std::cout << "fileMoved is now managing the file\n";
    }
}

int main() {
    ifstream_demo();
    return 0;
}
