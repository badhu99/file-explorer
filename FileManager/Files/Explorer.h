#pragma once
#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>
#include <vector>
#include <filesystem>
#include "ItemDetails.h"

class Explorer {
private:
	std::vector<ItemDetails> items;
	int _selectedIndex;
	int _oldIndex;
	std::filesystem::path _path;
	std::filesystem::path _oldPath;
	std::string _command;
	std::string _oldCommand;

	std::vector<ItemDetails> getCurrentItems() const {
		return std::vector<ItemDetails>();
	}

	void changeDirectory(const std::string& name);
	void updateToAbsolutePath();

	ItemDetails* findItem(const std::string& name);
	ItemDetails* findItem(int index);

	void HandleTab();
	void HandleEnter();
public:
	explicit Explorer(const std::string& path) :
		_selectedIndex(0), _oldIndex(0),
		_path(path), _oldPath(path),
		_command(""), _oldCommand(_command) {
		this->updateToAbsolutePath();
		loadItemsFromPath();
	}

	void loadItemsFromPath();
	void handleInput(const char& key);


	const std::string& getSelectedItem() const {
		return items[_selectedIndex].name;
	}
	const std::vector<ItemDetails>& getItems() const {
		return items;
	}

	int getSelectedIndex() const {
		return _selectedIndex;
	}

	int getOldIndex() const {
		return this->_oldIndex;
	}

	bool hasIndexChanged() const {
		return _oldIndex != _selectedIndex;
	}

	void updateOldIndex() {
		_oldIndex = _selectedIndex;
	}

	std::string getCurrentPath() const {
		return this->_path.string();
	}

	bool hasDirectoryChanged() {
		bool hasDirectoryChanged = this->_oldPath != this->_path;
		this->_oldPath = this->_path;
		return hasDirectoryChanged;
	}

	std::string getCommand() const {
		return _command;
	}

	bool hasCommandChanged() {
		bool hasCommandChanged = this->_command != this->_oldCommand;
		this->_oldCommand = this->_command;
		return hasCommandChanged;
	}
};

#endif // EXPLORER_H