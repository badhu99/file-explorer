#pragma once
#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>
#include <vector>
#include <filesystem>
#include "ItemDetails.h"

class Explorer {
private:
    std::vector<ItemDetails> items;
    int _selectedIndex;
    int _oldIndex;
    std::filesystem::path _path;
    std::filesystem::path _oldPath;

    void updateCurrentPath(const std::string& path);
    std::vector<ItemDetails> getCurrentItems() const;

    void changeDirectory(const std::string& name);
    void updateToAbsolutePath();

public:
    explicit Explorer(const std::string& path);

    void loadItemsFromPath();
    void handleInput(char key);
    const std::string& getSelectedItem() const;
    const std::vector<ItemDetails>& getItems() const;

    int getSelectedIndex() const;
    int getOldIndex() const;
    bool hasIndexChanged() const;
    void updateOldIndex();

    std::string getCurrentPath() const;
    bool hasDirectoryChanged() const;
    void updateOldDirectoryPath();

};

#endif // EXPLORER_H