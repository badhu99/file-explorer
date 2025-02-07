#include "Explorer.h"
#include <filesystem>
#include "ItemDetails.h"
#include "Helper.h"

void Explorer::changeDirectory(const std::string& name)
{
	this->updateToAbsolutePath();
	_path = std::filesystem::weakly_canonical(_path / name);
	this->loadItemsFromPath();

	this->_oldIndex = 0;
	this->_selectedIndex = 0;
	this->_command.clear();
	this->_oldCommand.clear();
}

void Explorer::updateToAbsolutePath()
{
	if (_path.is_relative()) {
		_path = std::filesystem::absolute(_path);
	}
}

ItemDetails* Explorer::findItem(const std::string& name)
{
	for (auto& item : items) {
		if (item.name == name) {
			return &item;
		}
	}
	return nullptr;
}

ItemDetails* Explorer::findItem(int index)
{
	if (index >= 0 && index < static_cast<int>(items.size()))
		return &items[index];

	return nullptr;
}
void Explorer::loadItemsFromPath() {
	items.clear();
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		auto details = ItemDetails{ entry };
		items.push_back(details);
	}
}

void Explorer::handleInput(const char& key) {
	switch (key) {
	case 72:  // Up arrow
		if (_selectedIndex > 0) {
			_selectedIndex--;
		}
		break;
	case 80:  // Down arrow
		if (_selectedIndex < static_cast<int>(items.size()) - 1) {
			_selectedIndex++;
		}
		break;
	case 75:  // Left arrow
		this->changeDirectory("..");
		break;
	case 77:  // Right arrow
	{
		auto item = items[this->getSelectedIndex()];
		if (item.isDirectory) {
			this->changeDirectory(item.name);
		}
		break;
	}
	case 8:  // Backspace
		if (!_command.empty()) {
			_command.pop_back();
		}
		break;
	case 9:  // Tab
		this->HandleTab();
		break;
	case 13:
		HandleEnter();
		break;
	default:
		if (std::isalpha(static_cast<unsigned char>(key))) {
			this->_command.push_back(key);
		}
		break;
	}
}

void Explorer::HandleTab() {
	auto possibleFileNames = std::vector<std::string>();
	for (const auto& item : items) {
		if (Helper::startsWithIgnoreCase(item.name, _command)) {
			possibleFileNames.push_back(item.name);
		}
	}

	if (possibleFileNames.empty())
		return;

	if (possibleFileNames.size() == 1)
		this->_command = possibleFileNames[0];

	this->_command = Helper::findLongestPrefix(possibleFileNames, _command);
}

void Explorer::HandleEnter() {
	auto commands = Helper::splitString(_command, ' ');
	ItemDetails* item = nullptr;

	if (commands.size() == 0) {
		item = findItem(_selectedIndex);
	}

	if (commands.size() == 1) {
		item = findItem(_command);
	}

	if (item != nullptr && item->isDirectory) {
		changeDirectory(item->name);
	}
	else {
		_command.clear();
	}
}
