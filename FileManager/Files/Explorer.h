#pragma once
#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>
#include <vector>

class Explorer {
public:
    struct Item {
        std::string name;
        bool isDirectory;
    };

private:
    std::vector<Item> items;
    int selectedIndex;
    std::string path;

public:
    explicit Explorer(const std::string& path);
    void loadItemsFromPath(const std::string& path);
    void handleInput(char key);
    int getSelectedIndex() const;
    const std::string& getSelectedItem() const;
    const std::vector<Item>& getItems() const;
};

#endif // EXPLORER_H