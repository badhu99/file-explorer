#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Explorer.h"

class Display {
private:
    std::vector<Explorer::Item> _items;
    int panelWidth = 40;

    void displayDetailsPane(int index, const Explorer::Item& selectedItem) const;
    void displayItem(Explorer::Item const item) const;
    //void displayLeftPanel(const std::vector<Explorer::Item>& items, int selectedIndex, int width) const;
    //void displayRightPanel(const std::string& selectedItem, int width) const;

public:
    explicit Display(std::vector<Explorer::Item> items);
    Display();

    void display(int selectedIndex) const;
    void moveCursor(int index, int oldIndex) const;
    void setItems(std::vector<Explorer::Item> items);
};

#endif // DISPLAY_H