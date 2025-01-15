#include "DualMenu.h"

#include <iostream>
#include <limits>
#include <iomanip>

void DualMenu::addMenuItem(const std::string& mainItem, const std::vector<std::string>& subItems) {
    menuItems.push_back({ mainItem, subItems });
}

void DualMenu::clearScreen() const {
    std::cout << std::string(100, '\n');
}

void DualMenu::drawLine(size_t length) const {
    std::cout << std::setfill('-') << std::setw(length) << "-" << std::setfill(' ') << '\n';
}

void DualMenu::displayLeftPanel() const {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == leftSelectedIndex && isLeftPanelActive) {
            std::cout << "* ";
        }
        else {
            std::cout << "  ";
        }
        std::cout << std::setw(20) << std::left << menuItems[i].name;
        std::cout << "│ ";
    }
}

void DualMenu::displayRightPanel() const {
    if (!menuItems.empty()) {
        const auto& subItems = menuItems[leftSelectedIndex].subItems;
        for (size_t i = 0; i < subItems.size(); ++i) {
            if (i == rightSelectedIndex && !isLeftPanelActive) {
                std::cout << "* ";
            }
            else {
                std::cout << "  ";
            }
            std::cout << subItems[i] << '\n';
        }
    }
}

void DualMenu::display() const {
    clearScreen();
    std::cout << "Controls: 'w/s' - move up/down, 'tab' - switch panels, 'enter' - select\n\n";

    // Draw header
    std::cout << std::setw(23) << std::left << "Main Menu";
    std::cout << "│ Sub Menu\n";
    drawLine(50);

    // Display panels
    displayLeftPanel();
    std::cout << '\n';
    drawLine(50);
    displayRightPanel();
}

char DualMenu::getInput() const {
    char input;
    std::cin.get(input);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

void DualMenu::handleInput(char input) {
    switch (input) {
    case 'w': // Up
    case 'W':
        if (isLeftPanelActive) {
            if (leftSelectedIndex > 0) {
                --leftSelectedIndex;
                rightSelectedIndex = 0;  // Reset right panel selection
            }
        }
        else {
            if (rightSelectedIndex > 0) {
                --rightSelectedIndex;
            }
        }
        break;

    case 's': // Down
    case 'S':
        if (isLeftPanelActive) {
            if (leftSelectedIndex < static_cast<int>(menuItems.size()) - 1) {
                ++leftSelectedIndex;
                rightSelectedIndex = 0;  // Reset right panel selection
            }
        }
        else {
            if (rightSelectedIndex < static_cast<int>(menuItems[leftSelectedIndex].subItems.size()) - 1) {
                ++rightSelectedIndex;
            }
        }
        break;

    case '\t': // Tab
        isLeftPanelActive = !isLeftPanelActive;
        break;
    }
}

void DualMenu::run() {
    leftSelectedIndex = 0;
    rightSelectedIndex = 0;
    isLeftPanelActive = true;

    char input;
    bool running = true;

    while (running) {
        display();
        input = getInput();

        if (input == '\n') {  // Enter key
            running = false;
        }
        else {
            handleInput(input);
        }
    }
}

std::pair<int, int> DualMenu::getSelectedIndices() const {
    return { leftSelectedIndex, rightSelectedIndex };
}