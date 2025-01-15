#include <iostream>
#include <conio.h>  // for _getch() on Windows
#include <iomanip>  // for std::setw
#include <filesystem>  // for std::filesystem
#include "FileExplorer.h"

namespace fs = std::filesystem;

FileExplorer::FileExplorer(const std::string& path)
    : selectedIndex(0), defaultPath(path)
{
    loadItemsFromPath(defaultPath);
}

void FileExplorer::clearScreen() const {
    system("cls");  // Windows
    // system("clear"); // Linux
}

void FileExplorer::displayMenuItems(int row) const {
    const int columnWidth = 40;  // Width of the first column

    if (row < static_cast<int>(items.size())) {
        if (row == selectedIndex) {
            std::cout << "* ";
        }
        else {
            std::cout << "  ";
        }
        std::cout << std::left << std::setw(columnWidth - 2) << items[row];  // Adjust width for the selection marker
    }
    else {
        std::cout << std::setw(columnWidth) << " ";  // Empty space for alignment
    }
}

void FileExplorer::displayAdditionalData(int row) const {
    if (row == 0) {
        std::cout << "Additional Data:";
    }
    else if (row == 1) {
        std::cout << "Selected Index: " << selectedIndex;
    }
}

void FileExplorer::display() const {
    clearScreen();
    const int maxRows = std::max(items.size(), static_cast<size_t>(2));  // Ensure at least 2 rows for additional data

    for (int i = 0; i < maxRows; ++i) {
        displayMenuItems(i);
        std::cout << " | ";  // Separator between columns
        displayAdditionalData(i);
        std::cout << '\n';
    }
}

char FileExplorer::getKeyPress() const {
    return _getch();  // Windows
    // return getchar(); // Linux
}

void FileExplorer::handleInput(char key) {
    switch (key) {
    case 72:  // Up arrow
        if (selectedIndex > 0) {
            --selectedIndex;
        }
        break;

    case 80:  // Down arrow
        if (selectedIndex < static_cast<int>(items.size()) - 1) {
            ++selectedIndex;
        }
        break;
    }
}

int FileExplorer::getSelectedIndex() const {
    return selectedIndex;
}

void FileExplorer::run() {
    char key;
    bool running = true;

    while (running) {
        display();
        key = getKeyPress();

        if (key == 13) {  // Enter key
            running = false;
        }
        else {
            handleInput(key);
        }
    }
}

void FileExplorer::loadItemsFromPath(const std::string& path) {
    items.clear();
    for (const auto& entry : fs::directory_iterator(path)) {
        items.push_back(entry.path().filename().string());
    }
}