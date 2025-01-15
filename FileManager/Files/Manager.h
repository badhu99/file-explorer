#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "Explorer.h"

class Manager {
private:
    Explorer explorer;

public:
    Manager(const std::string& path = ".");
    void run();
};

#endif // MANAGER_H