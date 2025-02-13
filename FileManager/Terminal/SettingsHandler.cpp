#include <iostream>
#include <fstream>
#include <stdexcept>

#include "SettingsHandler.h"

void SettingsHandler::load() {
    std::ifstream file(_filePath);
    if (!file) {
        throw std::runtime_error("Settings file not found: " + _filePath.string());
    }
    file.close();

    pugi::xml_document doc;
    if (!doc.load_file(_filePath.c_str())) {
        throw std::runtime_error("Failed to load settings file");
    }

    pugi::xml_node root = doc.child("Settings");

    pugi::xml_node windowNode = root.child("Window");
    _settings.windowWidth = windowNode.child("Width").text().as_int();
    _settings.windowHeight = windowNode.child("Height").text().as_int();

    pugi::xml_node userNode = root.child("User");
    _settings.username = userNode.child("Username").text().as_string();
    _settings.darkMode = userNode.child("DarkMode").text().as_bool();
}

void SettingsHandler::save(const std::string& filePath) {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("Settings");

    pugi::xml_node windowNode = root.append_child("Window");
    windowNode.append_child("Width").text().set(_settings.windowWidth);
    windowNode.append_child("Height").text().set(_settings.windowHeight);

    pugi::xml_node userNode = root.append_child("User");
    userNode.append_child("Username").text().set(_settings.username.c_str());
    userNode.append_child("DarkMode").text().set(_settings.darkMode);

    if (!doc.save_file(filePath.c_str())) {
        throw std::runtime_error("Failed to save settings file");
    }
}

SettingsModel SettingsHandler::getSettings() const {
    return _settings;
}

void SettingsHandler::setSettings(const SettingsModel& settings) {
    _settings = settings;
}
