#include "GlobalDisplayManager.h"

void GlobalDisplayManager::Display(DisplayScreens screen)
{
	switch (screen) {
	case DisplayScreens::Settings:
		_displaySettings.Display();
		break;
	case DisplayScreens::FileExplorer:
		_displayFileBrowser.Display();
		break;
	}
}

void GlobalDisplayManager::ClearScreen() const
{
	system("cls");  // Clear screen (Windows)
}
