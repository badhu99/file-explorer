#include "FileBrowserData.h"
#include "Helper.h"

void FileBrowserData::ChangeDirectory(const std::string name)
{
	this->updateToAbsolutePath();
	_path = std::filesystem::weakly_canonical(_path / name);
	loadItemsFromPath();

	_oldIndex = 0;
	_index = 0;
	_command.clear();
	_oldCommand.clear();
}

void FileBrowserData::ChangeDirectory()
{
	auto item = GetItem();
	ChangeDirectory(item.name);
}

int FileBrowserData::GetIndex() const
{
	return _index;
}

int FileBrowserData::GetOldIndex() const
{
	return _oldIndex;
}

bool FileBrowserData::HasIndexChanged() const
{
	return _oldIndex != _index;
}

void FileBrowserData::UpdateOldIndex()
{
	_oldIndex = _index;
}

void FileBrowserData::IncrementIndex()
{
	if (_index < static_cast<int>(_items.size()) - 1) {
		_index++;
	}
}

void FileBrowserData::DecrementIndex()
{
	if (_index > 0) {
		_index--;
	}
}

std::string FileBrowserData::GetPath() const
{
	return _path.string();
}

std::string FileBrowserData::GetCommand() const
{
	return _command;
}

void FileBrowserData::SetCommand(std::string cmd)
{
	_command = cmd;
}

void FileBrowserData::ClearCommand()
{
	_command.clear();
}

bool FileBrowserData::HasDirectoryChanged() const
{
	return _oldPath != _path;
}

void FileBrowserData::UpdateDirectory()
{
	_oldPath = _path;
}

bool FileBrowserData::ShowInitialDisplay() const
{
	return _initialDisplay;
}

void FileBrowserData::SetInitialDisplay(bool value)
{
	_initialDisplay = value;
}

const ItemDetails& FileBrowserData::GetItem() const
{
	return _items[_index];
}

const ItemDetails& FileBrowserData::GetItem(const size_t index) const
{
	return _items[index];
}

const ItemDetails& FileBrowserData::GetItem(const std::string name) const
{
	const ItemDetails* returnItem = nullptr;
	for (const auto& item : _items) {
		if (item.name == name) {
			returnItem = &item;
			break;
		}
	}
	if (returnItem != nullptr)
		return *returnItem;

	return GetItem();
}

const std::vector<std::string> FileBrowserData::GetPossibleItems() const
{
	auto possibleFileNames = std::vector<std::string>();
	for (const auto& item : _items) {
		if (Helper::startsWithIgnoreCase(item.name, _command))
			possibleFileNames.push_back(item.name);
	}

	return possibleFileNames;
}

const size_t FileBrowserData::GetItemsSize() const
{
	return _items.size();
}

bool FileBrowserData::HasCommandChanged()
{
	bool hasCommandChanged = _command != _oldCommand;
	if (hasCommandChanged) {
		_oldCommand = _command;
	}
	return hasCommandChanged;
}

void FileBrowserData::AppendLastLetter(const char& letter)
{
	_command.push_back(letter);
}

void FileBrowserData::RemoveLastLetter()
{
	if (!_command.empty())
		_command.pop_back();
}

void FileBrowserData::updateToAbsolutePath()
{
	if (_path.is_relative()) {
		_path = std::filesystem::absolute(_path);
	}
}

void FileBrowserData::loadItemsFromPath() {
	_items.clear();
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		auto details = ItemDetails{ entry };
		_items.push_back(details);
	}
}