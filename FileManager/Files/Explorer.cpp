#include "Explorer.h"
#include <filesystem>


Explorer::Explorer(const std::string& path)
    : selectedIndex(0), path(path) {
    loadItemsFromPath(path);
}

void Explorer::loadItemsFromPath(const std::string& path) {
    items.clear();
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        items.push_back({ entry.path().filename().string(), entry.is_directory() });
    }
}

void Explorer::handleInput(char key) {
    switch (key) {
    case 72:  // Up arrow
        if (selectedIndex > 0) {
            --selectedIndex;
        }
        break;
    case 80:  // Down arrow
        if (selectedIndex < static_cast<int>(items.size()) - 1) {
            ++selectedIndex;
        }
        break;
    }
}

int Explorer::getSelectedIndex() const {
    return selectedIndex;
}

const std::string& Explorer::getSelectedItem() const {
    return items[selectedIndex].name;
}

const std::vector<Explorer::Item>& Explorer::getItems() const {
    return items;
}