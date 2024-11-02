#include <iostream>
#include <string>
#include <thread>
#include <functional> // for std::ref

// Type definitions for `widget_id` and `widget_data`
using widget_id = int;

struct widget_data {
    int value;
};

void update_data_for_widget(widget_id w, widget_data& data) {
    std::cout << "Updating widget data for widget " << w << "\n";
    data.value = 42;  // Arbitrary update
}

void display_status() {
    std::cout << "Displaying status...\n";
}

void process_widget_data(const widget_data& data) {
    std::cout << "Processing widget data. Value: " << data.value << "\n";
}

void oops_again(widget_id w) {
    widget_data data;
    std::thread t(update_data_for_widget, w, std::ref(data));  // Use std::ref to pass `data` by reference
    display_status();
    t.join();  // Ensure thread completes before accessing `data`
    process_widget_data(data);  // `data` includes updates made by the thread
}

int main() {
    widget_id wid = 1;
    oops_again(wid);
    return 0;
}
