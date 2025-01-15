#include "Manager.h"

#include <conio.h>  // for _getch() on Windows
#include <iostream>
#include <iomanip>  // for std::setw

#include "Display.h"

Manager::Manager(const std::string& path)
    : explorer(path) {}

void Manager::run() {
    char key;
    bool running = true;
    const int panelWidth = 40;  // Width of each panel
    Display display;

    while (running) {
        system("cls");  // Clear screen (Windows)

        const auto& items = explorer.getItems();
        int selectedIndex = explorer.getSelectedIndex();
        std::string selectedItem = explorer.getSelectedItem();

        // Use the Display class to show both panels side by side
        display.display(items, selectedIndex, selectedItem, panelWidth);

        key = _getch();  // Get key press (Windows)
        if (key == 3) {  // Ctrl+C
            running = false;
        }
        else {
            explorer.handleInput(key);
        }
    }
}