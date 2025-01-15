#pragma once

#include <string>
#include <vector>
#include <map>

class DualMenu {
private:
    struct MenuItem {
        std::string name;
        std::vector<std::string> subItems;
    };

    std::vector<MenuItem> menuItems;
    int leftSelectedIndex;
    int rightSelectedIndex;
    bool isLeftPanelActive;

    void display() const;
    void clearScreen() const;
    char getInput() const;
    void handleInput(char input);
    void drawLine(size_t length) const;
    void displayLeftPanel() const;
    void displayRightPanel() const;

public:
    void addMenuItem(const std::string& mainItem, const std::vector<std::string>& subItems);
    void run();
    std::pair<int, int> getSelectedIndices() const;
};


