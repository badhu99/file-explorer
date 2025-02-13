#pragma once
#include "SettingsDisplay.h"
class SettingsManager
{
private:
	SettingsDisplay _display;

public:
	SettingsManager() = default;

	/// <summary>
	/// Handles input actions and returns bool if needs to leave screen.
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool HandleActions(const char& key) const;

	void Display();
};

