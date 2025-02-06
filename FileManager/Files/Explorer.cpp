#include "Explorer.h"
#include <filesystem>


void Explorer::updateCurrentPath(const std::string& path)
{
}

std::vector<Explorer::Item> Explorer::getCurrentItems() const
{
	return std::vector<Item>();
}

void Explorer::changeDirectory(const std::string& name)
{
	if (_path.is_relative()) {
		_path = std::filesystem::absolute(_path);
	}

	_path = std::filesystem::weakly_canonical(_path / name);
	this->loadItemsFromPath();
	this->_oldIndex = 0;
	this->_selectedIndex = 0;
}

Explorer::Explorer(const std::string& path)
	: _selectedIndex(0), _oldIndex(0),
	_path(path), _oldPath(path) {
	loadItemsFromPath();
}

void Explorer::loadItemsFromPath() {
	items.clear();
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		items.push_back({ entry.path().filename().string(), entry.is_directory() });
	}
	//for (const auto& fileItem : )
}

void Explorer::handleInput(char key) {
	switch (key) {
	default:
		break;
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
		auto item = items[this->getSelectedIndex()];
		if (item.isDirectory) {
			this->changeDirectory(item.name);
		}
		break;
	}
}

int Explorer::getSelectedIndex() const {
	return _selectedIndex;
}

int Explorer::getOldIndex() const
{
	return this->_oldIndex;
}

const std::string& Explorer::getSelectedItem() const {
	return items[_selectedIndex].name;
}

const std::vector<Explorer::Item>& Explorer::getItems() const {
	return items;
}

bool Explorer::hasIndexChanged() const
{
	return this->_oldIndex != this->_selectedIndex;
}

void Explorer::updateOldIndex()
{
	this->_oldIndex = this->_selectedIndex;
}

bool Explorer::hasDirectoryChanged() const
{
	return this->_oldPath != this->_path;
}

void Explorer::updateOldDirectoryPath()
{
	this->_oldPath = this->_path;
}
