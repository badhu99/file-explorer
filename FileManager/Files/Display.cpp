#include "Display.h"
#include <iostream>
#include <iomanip>

void Display::display(const std::vector<Explorer::Item>& items, int selectedIndex, const std::string& selectedItem, int width) const {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "|";
        // LEFT PANEl
        if (i == selectedIndex) {
            std::cout << "* ";
        }
        else {
            std::cout << "  ";
        }
        std::string displayName = items[i].name;
        if (items[i].isDirectory) {
            displayName += "/";
        }
        std::cout << std::left << std::setw(width - 2) << displayName;

        // RIGHT PANEL
        std::cout << " || ";
        displayDetailsPane(i, selectedItem, width);
        std::cout << std::endl;
    }
}

void Display::displayDetailsPane(int index, const std::string& selectedItem, int width) const
{
    switch (index) {
    case 0:
        std::cout << std::left << "Details pane";
        break;
    case 2:
        std::cout << std::left << "Name: " << selectedItem;
        break;
    case 3:
        std::cout << std::left <<  "Size: " << 15;
        break;
    }

	//std::cout << std::left << std::setw(width) << "|";
}
