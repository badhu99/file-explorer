#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "Explorer.h"
#include "Display.h"

class Manager {
private:
    Explorer explorer;
    Display _display;

    void InitialDisplay();
    void handleInput();
public:
    explicit Manager(const std::string& path = ".");
    void run();
};

#endif // MANAGER_H