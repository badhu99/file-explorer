#pragma once
#include <string>
#include <filesystem>
#include <chrono>

struct ItemDetails {
    std::string name;
    bool isDirectory;
    uintmax_t size;
    std::filesystem::file_time_type created;
    std::filesystem::file_time_type modified;
    std::filesystem::file_time_type accessed;

    explicit ItemDetails(const std::filesystem::directory_entry& data) :
        name(data.path().filename().string()),
        isDirectory(data.is_directory()),
        size(data.file_size()),
        created(std::filesystem::last_write_time(data)),
        modified(std::filesystem::last_write_time(data)),
        accessed(std::filesystem::last_write_time(data))
    {}
};