#include "FileExplorer.h"
#include <filesystem>
#include <windows.h>
#include "DualMenu.h"
#include <iostream>
#include <cstdlib>

int main() {
    std::vector<std::string> menuItems = {
        "Option 1",
        "Option 2",
        "Option 3"
    };

    std::string defaultPath = ".";
    FileExplorer fe(defaultPath);
    fe.run();

    return 0;
}