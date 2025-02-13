#pragma once
#include <vector>
#include <string>
#include "ItemDetails.h"

class FileBrowserData {
private:
	std::vector<ItemDetails> _items;
	bool _initialDisplay;
	std::filesystem::path _path;
	std::filesystem::path _oldPath;
	int _index = 0;
	int _oldIndex = 0;
	std::string _command;
	std::string _oldCommand;

	void updateToAbsolutePath();
	void loadItemsFromPath();
public:
	FileBrowserData()
		: _initialDisplay(true),
		_command(""), _oldCommand(""),
		_path("."), _oldPath(".") {
		updateToAbsolutePath();
		loadItemsFromPath();
	}
	int panelWidth = 40;
	int _rightPanelOffset = 5;
	int _topPanelHeight = 5;

	int GetIndex() const;
	int GetOldIndex() const;
	bool HasIndexChanged() const;
	void UpdateOldIndex();
	void IncrementIndex();
	void DecrementIndex();
	std::string GetPath() const;
	void ChangeDirectory(const std::string name);
	void ChangeDirectory();
	bool HasDirectoryChanged() const;
	void UpdateDirectory();
	bool ShowInitialDisplay() const;
	void SetInitialDisplay(bool value);
	const ItemDetails& GetItem() const;
	const ItemDetails& GetItem(const size_t index) const;
	const ItemDetails& GetItem(const std::string name) const;
	const std::vector<std::string> GetPossibleItems() const;
	const size_t GetItemsSize() const;
	std::string GetCommand() const;
	void SetCommand(std::string cmd);
	void ClearCommand();
	bool HasCommandChanged();
	void AppendLastLetter(const char& letter);
	void RemoveLastLetter();
};