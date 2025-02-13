#pragma once
#ifndef GLOBALDISPLAYMANAGER_H
#define GLOBALDISPLAYMANAGER_H

#include "../Settings/SettingsDisplay.h"
#include "DisplayScreens.h"
#include "../FileBrowser/FileBrowserDisplay.h"

class GlobalDisplayManager
{
private:
	SettingsDisplay _displaySettings;
	FileBrowserDisplay _displayFileBrowser;

public:
	explicit GlobalDisplayManager(FileBrowserData& managerFB) : _displaySettings(), _displayFileBrowser(managerFB) {};

	void Display(DisplayScreens screen);
	void ClearScreen() const;
};

#endif // GLOBALDISPLAYMANAGER_H