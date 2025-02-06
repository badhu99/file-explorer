#pragma once
#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>
#include <vector>
#include <filesystem>

class Explorer {
public:
    struct Item {
        std::string name;
        bool isDirectory;
    };

private:
    std::vector<Item> items;
    int _selectedIndex;
    int _oldIndex;
    std::filesystem::path _path;
    std::filesystem::path _oldPath;

    void updateCurrentPath(const std::string& path);
    std::vector<Item> getCurrentItems() const;

    void changeDirectory(const std::string& name);

public:
    explicit Explorer(const std::string& path);

    void loadItemsFromPath();
    void handleInput(char key);
    const std::string& getSelectedItem() const;
    const std::vector<Item>& getItems() const;

    int getSelectedIndex() const;
    int getOldIndex() const;
    bool hasIndexChanged() const;
    void updateOldIndex();

    bool hasDirectoryChanged() const;
    void updateOldDirectoryPath();

};

#endif // EXPLORER_H