#include "GlobalActionHandler.h"

DisplayScreens* GlobalActionHandler::navigateToSettings()
{
	// togle
	_actionsFB.ShowInitialDisplay();
	static DisplayScreens newScreen = DisplayScreens::Settings;
	return &newScreen;
}

DisplayScreens* GlobalActionHandler::HandleInput(const char& key)
{
	if (key == 59 && _screen != DisplayScreens::Settings) {
		return navigateToSettings();
	}
	else {
		switch (_screen) {
		case DisplayScreens::Settings:
			if (auto navigateAwayFromSettings = _managerSettings.HandleActions(key)) {
				static DisplayScreens newScreen = DisplayScreens::FileExplorer;
				return &newScreen;
			}

			break;
		case DisplayScreens::FileExplorer:
			_actionsFB.HandleInput(key);
			break;
		}
	}

	return nullptr;
}
