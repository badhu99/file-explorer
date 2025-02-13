#include "SettingsManager.h"

bool SettingsManager::HandleActions(const char& key) const
{
	switch (key) {
	case 27:  // Escape key
		return true; // Indicate to leave settings screen.
	default:
		return false;
	}
}

void SettingsManager::Display()
{
	_display.Display();
}
