#include "FileBrowserActionHandler.h"
#include "Helper.h"

void FileBrowserActionHandler::HandleInput(const char& key)
{
	switch (key) {
	case 72:
		handleUpArrow();
		break;
	case 80:
		handleDownArrow();
		break;
	case 75:
		handleLeftArrow();
		break;
	case 77:
		handleRightArrow();
		break;
	case 8:
		handleBackspace();
		break;
	case 9:
		handleTab();
		break;
	case 13:
		handleEnter();
		break;
	default:
		handleDefault(key);
		break;
	}
}

void FileBrowserActionHandler::ShowInitialDisplay()
{
	_data.SetInitialDisplay(true);
}

void FileBrowserActionHandler::handleUpArrow()
{
	_data.DecrementIndex();
}

void FileBrowserActionHandler::handleDownArrow()
{
	_data.IncrementIndex();
}

void FileBrowserActionHandler::handleLeftArrow()
{
	_data.ChangeDirectory("..");
}

void FileBrowserActionHandler::handleRightArrow()
{
	auto item = _data.GetItem();
	if (item.isDirectory)
		_data.ChangeDirectory(item.name);
}

void FileBrowserActionHandler::handleEnter()
{
	std::string command = _data.GetCommand();
	const auto commands = Helper::splitString(command, ' ');

	if (commands.empty()) {
		_data.ChangeDirectory();
	}

	if (commands.size() == 1) {
		const auto item = _data.GetItem(command);
		if (item.isDirectory)
			_data.ChangeDirectory(item.name);
	}
	_data.ClearCommand();
}

void FileBrowserActionHandler::handleTab()
{
	auto possibleFileNames = _data.GetPossibleItems();
	std::string command = _data.GetCommand();

	if (possibleFileNames.empty())
		return;

	if (possibleFileNames.size() == 1) {
		command = possibleFileNames[0];
		_data.SetCommand(command);
	}

	_data.SetCommand(Helper::findLongestPrefix(possibleFileNames, command));
}

void FileBrowserActionHandler::handleBackspace()
{
	_data.RemoveLastLetter();
}

void FileBrowserActionHandler::handleDefault(const char& key)
{
	if (std::isalnum(static_cast<unsigned char>(key))) {
		_data.AppendLastLetter(key);
	}
}



