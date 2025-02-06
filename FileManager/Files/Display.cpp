#include "Display.h"
#include <iostream>
#include <iomanip>

Display::Display(std::vector<Explorer::Item> items): _items(items)
{
}

Display::Display() : _items(std::vector<Explorer::Item>()) {}

void Display::display(int selectedIndex) const {
    for (size_t i = 0; i < _items.size(); ++i) {
        // LEFT PANEl
        if (i == selectedIndex) {
            std::cout << "* ";
        }
        else {
            std::cout << "  ";
        }
        std::string displayName = _items[i].name;
        this->displayItem(_items[i]);

        // RIGHT PANEL
        auto selectedItem = this->_items[selectedIndex];
        std::cout << " || ";
        displayDetailsPane(i, selectedItem);
        std::cout << std::endl;
    }
}

void Display::displayDetailsPane(int index, const Explorer::Item& selectedItem) const
{
    switch (index) {
    case 0:
        std::cout << std::left << "Details pane";
        break;
    case 2:
        std::cout << std::left << "Name: " << selectedItem.name;
        break;
    case 3:
        std::cout << std::left <<  "Size: " << 15;
        break;
    }
}

void Display::displayItem(Explorer::Item const item) const
{
    std::string displayName = item.name;
    if (item.isDirectory) {
        displayName += "/";
    }
    std::cout << std::left << std::setw(this->panelWidth - 2) << displayName;
}

void Display::moveCursor(int index, int oldIndex) const {
    if (oldIndex >= 0 && oldIndex < _items.size()) {
        std::cout << "\033[" << oldIndex + 1 << ";1H  ";
        this->displayItem(_items[oldIndex]);
    }

    if (index >= 0 && index < _items.size()) {
        std::cout << "\033[" << index + 1 << ";1H* ";
        this->displayItem(_items[index]);
    }


}

void Display::setItems(std::vector<Explorer::Item> items) {
    _items = items;
}
