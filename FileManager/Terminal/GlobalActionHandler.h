#pragma once

#include "DisplayScreens.h"
#include "../FileBrowser/FileBrowserData.h"
#include "../Settings/SettingsManager.h"
#include "../FileBrowser/FileBrowserActionHandler.h"

class GlobalActionHandler
{
private:
	DisplayScreens _screen;
	DisplayScreens _screenPrevious;

	FileBrowserActionHandler _actionsFB;
	SettingsManager _managerSettings;

	void updateScren() {
		_screenPrevious = _screen;
	}

	DisplayScreens* navigateToSettings();

public:
	explicit GlobalActionHandler(FileBrowserData& managerFB) :
		_screen(DisplayScreens::Settings),
		_screenPrevious(DisplayScreens::FileExplorer),
		_actionsFB(managerFB),
		_managerSettings{} {};

	DisplayScreens GetScreen() const {
		return _screen;
	}

	bool HasScreenChanged() {
		auto hasScreenChanged = _screenPrevious != _screen;
		if (hasScreenChanged)
			updateScren();

		return hasScreenChanged;
	}

	void UpdateScreen(DisplayScreens newScreen) {
		_screen = newScreen;
	}

	DisplayScreens* HandleInput(const char& key);
};
