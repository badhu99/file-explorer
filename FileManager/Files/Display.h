#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Explorer.h"
#include "ItemDetails.h"

class Display {
private:
    std::vector<ItemDetails> _items;
    int panelWidth = 40;
    int _rightPanelOffset = 5;
    int _topPanelHeight = 3;

    void displayLeftItem(const ItemDetails& item) const;
    void displayLeftPanel(int selectedIndex) const;
    void displayRightPanel(const ItemDetails& selectedItem) const;
    void clearRightPanel() const;
    void displayTopPanel(const std::string& path) const;
public:
    explicit Display(std::vector<ItemDetails> items);
    Display();

    void display(int selectedIndex, const std::string& currentPath) const;
    void moveCursor(int index, int oldIndex) const;
    void setItems(std::vector<ItemDetails> items);
};

#endif // DISPLAY_H