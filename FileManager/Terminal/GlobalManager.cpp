#include "GlobalManager.h"
#include <string>


#include <conio.h>  // for _getch() on Windows
#include <iostream>
#include <iomanip>  // for std::setw
#include <vector>

void GlobalManager::run() {
	try
	{
		while (true) {
			if (_actionHandler.HasScreenChanged()) {
				_displayManager.ClearScreen();
			}
			auto screen = _actionHandler.GetScreen();
			_displayManager.Display(screen);

			handleInput();
		}
	}
	catch (const std::runtime_error&)
	{
		return;
	}
}

void GlobalManager::handleInput()
{
	auto key = getKey();
	if (key == 3) {  // Ctrl+C
		throw std::runtime_error("Termination requested by user.");
	}
	auto screen = _actionHandler.HandleInput(key);
	if (screen != nullptr) {
		_actionHandler.UpdateScreen(*screen);
	}

}

char GlobalManager::getKey() {
	return _getch();
}
