#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Explorer.h"

class Display {
private:

    void displayDetailsPane(int index, const std::string& selectedItem, int width) const;

public:
    void display(const std::vector<Explorer::Item>& items, int selectedIndex, const std::string& selectedItem, int width) const;
};

#endif // DISPLAY_H