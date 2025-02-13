#include <iostream>
#include <thread>
#include <chrono>

#include "GlobalManager.h"

int main() {
    FileBrowserData managerFB{};

    GlobalManager fileManager(".", managerFB);
    fileManager.run();

    return 0;
}