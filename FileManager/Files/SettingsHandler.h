#pragma once
#include <string>
#include <filesystem>

#include "SettingsModel.h"
#include "pugixml.hpp"

class SettingsHandler {
private:
	SettingsModel _settings;
	std::string _settingsName = "settings.xml";
	std::filesystem::path _filePath;

public:
	SettingsHandler() :_settings(), _filePath() {
		_filePath = std::filesystem::current_path() / _settingsName;
	};
	void load();
	void save(const std::string& filePath);
	SettingsModel getSettings() const;
	void setSettings(const SettingsModel& settings);
};

