#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "Explorer.h"
#include "Display.h"
#include "SettingsHandler.h"

class Manager {
private:
    Explorer _explorer;
    Display _display;
    SettingsHandler _settingsHandler;

    void InitialDisplay();
    void handleInput();
public:
    explicit Manager(const std::string& path = ".");
    void run();
};

#endif // MANAGER_H