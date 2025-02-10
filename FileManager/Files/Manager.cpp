#pragma once

#include "Manager.h"

#include <conio.h>  // for _getch() on Windows
#include <iostream>
#include <iomanip>  // for std::setw
#include <vector>


#include "Display.h"

Manager::Manager(const std::string& path)
	: _explorer(path), _display(), _settingsHandler() {

	try {
		_settingsHandler.load();
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading settings: " << e.what() << std::endl;
	}
}

void Manager::run() {
	this->InitialDisplay();

	try
	{
		while (true) {
			switch (_explorer.getCurrentScreen()) {
			case DisplayScreens::FileExplorer: {
				if (_explorer.hasIndexChanged()) {
					_display.moveCursor(_explorer.getSelectedIndex(), _explorer.getOldIndex());
					_display.updateRightPanel(_explorer.getSelectedIndex());
					_explorer.updateOldIndex();
				}

				if (_explorer.hasDirectoryChanged() || _explorer.hasScreenChanged()) {
					_explorer.resetScreenChange();
					InitialDisplay();
				}

				if (_explorer.hasCommandChanged()) {
					this->_display.updateCommandsDisplay(_explorer.getCommand());
				}
				break;
			}
			case DisplayScreens::Settings: {
				_display.clearFullDisplay();
				_display.displaySettings();
				break;
			}
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
		switch (_explorer.getCurrentScreen()) {
		case DisplayScreens::FileExplorer: {
			_explorer.handleInput(key);
			break;
		}
		case DisplayScreens::Settings: {
			_explorer.HandleSettingsInput(key);
			break;
		}
		}

	}
}
