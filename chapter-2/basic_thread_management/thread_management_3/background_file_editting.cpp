#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void edit_document(const std::string& document_name) {
    std::cout << "Editing document: " << document_name << " in thread " << std::this_thread::get_id() << std::endl;
    
    // Simulate document editing with a sleep
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Finished editing document: " << document_name << " in thread " << std::this_thread::get_id() << std::endl;
}

void open_document(const std::string& document_name) {
    // Create a detached thread for editing the document
    std::thread editing_thread(edit_document, document_name);
    editing_thread.detach(); // Detach the thread to allow it to run independently
}

int main() {
    open_document("Document1.txt");
    open_document("Document2.txt");
    open_document("Document3.txt");

    std::cout << "Documents are being edited in separate threads." << std::endl;

    // Allow some time for all threads to complete their editing
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Main thread finished. Exiting application." << std::endl;

    return 0; // The main thread exits
}
