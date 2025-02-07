#pragma once
#include <string>
#include <filesystem>
#include <chrono>
#include <variant>
#include <vector>
#include <iostream>
#include <iomanip>

// Define a variant type that can hold different types of values
using ItemValue = std::variant<std::string, uintmax_t, std::filesystem::file_time_type>;

struct ItemDetailsDisplay {
    std::string displayName;
    ItemValue value;

    ItemDetailsDisplay(const std::string& displayName, const ItemValue& value)
        : displayName(displayName), value(value){}

    // Overload the << operator for ItemDetailsDisplay as a hidden friend
    friend std::ostream& operator<<(std::ostream& os, const ItemDetailsDisplay& item);
};

struct ItemDetails {
    bool isDirectory;
    std::string name;
    uintmax_t size;
    std::filesystem::file_time_type created;
    std::filesystem::file_time_type modified;
    std::filesystem::file_time_type accessed;
    std::vector<ItemDetailsDisplay> data;

    explicit ItemDetails(const std::filesystem::directory_entry& entry)
        : isDirectory(entry.is_directory()),
        name(entry.path().filename().string()),
        size(entry.is_directory() ? 0 : entry.file_size()),
        created(std::filesystem::last_write_time(entry)),
        modified(std::filesystem::last_write_time(entry)),
        accessed(std::filesystem::last_write_time(entry)),
        data({
            {"Name: ", name},
            {"Size: ", size},
            {"Created: ", created},
            {"Modified: ", modified},
            {"Accessed: ", accessed}
            }) {}
};
