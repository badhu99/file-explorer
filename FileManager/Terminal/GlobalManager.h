#pragma once
#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include "SettingsHandler.h"
#include "../Settings/SettingsManager.h"
#include "GlobalDisplayManager.h"
#include "GlobalActionHandler.h"

class GlobalManager {
private:
    SettingsHandler _settingsHandler;

    GlobalDisplayManager _displayManager;
    GlobalActionHandler _actionHandler;

    void handleInput();
    char getKey();
public:
    explicit GlobalManager(const std::string& path, FileBrowserData& managerFB)
        : _settingsHandler(), _displayManager(managerFB), _actionHandler(managerFB) {

        try {
            _settingsHandler.load();
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading settings: " << e.what() << std::endl;
        }
    };

    void run();
};

#endif // GLOBALMANAGER_H