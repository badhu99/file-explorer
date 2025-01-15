#pragma once
#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include <vector>

class FileExplorer {
private:
    std::vector<std::string> items;
    int selectedIndex;
    std::string defaultPath;

    void display() const;
    void clearScreen() const;
    void displayMenuItems(int row) const;
    void displayAdditionalData(int row) const;
    char getKeyPress() const;
    void handleInput(char key);
    void loadItemsFromPath(const std::string& path);

public:
    explicit FileExplorer(const std::string& path);
    void run();
    int getSelectedIndex() const;
};

#endif // FILE_EXPLORER_H