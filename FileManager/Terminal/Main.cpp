#include "../Files/Manager.h"
#include <iostream>
#include <thread>
#include <chrono>

void clearLine(int line) {
    // Move the cursor to the specified line
    std::cout << "\033[" << line << ";1H";
    // Clear the line
    std::cout << "\033[2K";
}

int main() {

    // Print multiple lines
    //std::cout << "Line 1: Hello" << std::endl;
    //std::cout << "Line 2: World" << std::endl;
    //std::cout << "Line 3: !" << std::endl;

    //// Wait for 2 seconds
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    //// Clear the second line
    //clearLine(2);
    //std::cout << "\033[2;1HLine 2: New Content" << std::endl;

    //std::this_thread::sleep_for(std::chrono::seconds(5));


    // Print new content on the second line


    Manager fileManager(".");
    fileManager.run();

    return 0;
}