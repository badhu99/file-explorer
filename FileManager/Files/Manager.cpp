#include "Manager.h"

#include <conio.h>  // for _getch() on Windows
#include <iostream>
#include <iomanip>  // for std::setw
#include <vector>


#include "Display.h"

Manager::Manager(const std::string& path)
    : _explorer(path), _display() {}


void Manager::run() {
    this->InitialDisplay();

    try
    {
        while (true) {
            if (_explorer.hasIndexChanged()) {
                _display.moveCursor(_explorer.getSelectedIndex(), _explorer.getOldIndex());
                _explorer.updateOldIndex();
            }

            if (_explorer.hasDirectoryChanged()) {
                InitialDisplay();
            }

            if (_explorer.hasCommandChanged()) {
                this->_display.updateCommandsDisplay(_explorer.getCommand());
            }

            this->handleInput();
        }
    }
    catch (const std::runtime_error&)
    {
        return;
    }
}

void Manager::InitialDisplay()
{
    int index = _explorer.getSelectedIndex();
    auto path = _explorer.getCurrentPath();
    auto command = _explorer.getCommand();

    this->_display.setItems(_explorer.getItems());
    _display.clearFullDisplay();
    _display.display(index, path, command);
}

void Manager::handleInput()
{
    char key = _getch();  // Get key press (Windows)
    if (key == 3) {  // Ctrl+C
        throw std::runtime_error("Termination requested by user.");
    }
    else {
        _explorer.handleInput(key);
    }
}
