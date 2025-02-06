#include "Manager.h"

#include <conio.h>  // for _getch() on Windows
#include <iostream>
#include <iomanip>  // for std::setw
#include <vector>


#include "Display.h"

Manager::Manager(const std::string& path)
    : explorer(path), _display() {}


void Manager::run() {
    this->InitialDisplay();

    try
    {
        while (true) {
            if (this->explorer.hasIndexChanged()) {
                _display.moveCursor(explorer.getSelectedIndex(), explorer.getOldIndex());
                explorer.updateOldIndex();
            }

            if (this->explorer.hasDirectoryChanged()) {
                InitialDisplay();
                this->explorer.updateOldDirectoryPath();
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
    int selectedIndex = explorer.getSelectedIndex();
    const auto& items = explorer.getItems();
    this->_display.setItems(items);
    system("cls");  // Clear screen (Windows)
    _display.display(selectedIndex);
}

void Manager::handleInput()
{
    char key = _getch();  // Get key press (Windows)
    if (key == 3) {  // Ctrl+C
        throw std::runtime_error("Termination requested by user.");
    }
    else {
        this->explorer.handleInput(key);
    }
}
