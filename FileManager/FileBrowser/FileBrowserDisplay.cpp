#include "FileBrowserDisplay.h"

void FileBrowserDisplay::displayLeftPanel(int selectedIndex) const {
	for (size_t i = 0; i < _data.GetItemsSize(); ++i) {
		std::cout << "\033[" << i + _data._topPanelHeight << ";1H"; // Move cursor to the correct line below the top panel
		if (i == selectedIndex) {
			std::cout << "* ";
		}
		else {
			std::cout << "  ";
		}
		displayLeftItem(_data.GetItem(i));
		std::cout << std::endl;
	}
}

void FileBrowserDisplay::displayTopPanel(const std::string& path, const std::string& command) const {
	std::cout << "\033[1;1H"; // Move cursor to the top-left corner
	std::cout << std::left << path << std::endl;
	displayCommand(command);
	std::cout << std::string(80, '-') << std::endl; // Separator line
}

void FileBrowserDisplay::displayCommand(const std::string& command) const {
	std::cout << std::left << "$ " << command << std::endl;
}

void FileBrowserDisplay::displayScreen() const
{
	displayTopPanel(_data.GetPath(), _data.GetCommand());
	displayLeftPanel(_data.GetIndex());
	displayRightPanel(_data.GetItem());
}

void FileBrowserDisplay::displayRightPanel(const ItemDetails& selectedItem) const {
	int startCol = _data.panelWidth + _data._rightPanelOffset; // Starting column for the right panel

	for (size_t i = 0; i < selectedItem.data.size(); ++i) {
		const auto& itemData = selectedItem.data[i];
		std::cout << "\033[" << _data._topPanelHeight + i << ";" << startCol << "H";
		std::cout << itemData << std::endl;
	}
}

void FileBrowserDisplay::clearRightPanel(const ItemDetails& item) const {
	int startCol = _data.panelWidth + _data._rightPanelOffset;

	for (auto i = 0; i < item.data.size(); i++) {
		auto itemData = item.data[i];
		auto charLength = itemData.displayName.length();
		std::cout << "\033[" << _data._topPanelHeight + i << ";" << startCol + charLength << "H"; // Adjusted to start clearing below the top panel
		std::cout << std::string(30, ' ');
	}
}

void FileBrowserDisplay::Display()
{
	if (_data.ShowInitialDisplay()) {
		clearFullDisplay();
		displayScreen();
		_data.SetInitialDisplay(false);
	}
	else if (_data.HasIndexChanged()) {
		auto index = _data.GetIndex();
		moveCursor(index, _data.GetOldIndex());
		updateRightPanel(index);
		_data.UpdateOldIndex();
	}

	if (_data.HasDirectoryChanged()) {
		clearFullDisplay();
		displayScreen();
		_data.UpdateDirectory();
	}

	if (_data.HasCommandChanged()) {
		updateCommandsDisplay(_data.GetCommand());
	}
}

void FileBrowserDisplay::moveCursor(int index, int oldIndex) const {
	if (oldIndex >= 0 && oldIndex < static_cast<int>(_data.GetItemsSize())) {
		std::cout << "\033[" << oldIndex + _data._topPanelHeight << ";1H  "; // Adjusted to start below the top panel
		this->displayLeftItem(_data.GetItem(oldIndex));
	}

	if (index >= 0 && index < static_cast<int>(_data.GetItemsSize())) {
		std::cout << "\033[" << index + _data._topPanelHeight << ";1H* "; // Adjusted to start below the top panel
		this->displayLeftItem(_data.GetItem(index));
	}
}

void FileBrowserDisplay::updateRightPanel(size_t index) const {
	if (index >= 0 && index < static_cast<int>(_data.GetItemsSize())) {
		clearRightPanel(_data.GetItem(index));
		displayRightPanel(_data.GetItem(index));
	}
}

void FileBrowserDisplay::updateCommandsDisplay(const std::string& command) const {

	std::cout << "\033[2;1H"; // Move cursor to the commands line
	std::cout << std::string(80, ' '); // Clear the commands line
	std::cout << "\033[2;1H"; // Move cursor back to the commands line
	this->displayCommand(command);
}

void FileBrowserDisplay::displayLeftItem(const ItemDetails& item) const {
	std::string displayName = item.name;
	if (item.isDirectory) {
		displayName += "/";
	}
	std::cout << std::left << std::setw(_data.panelWidth - 2) << displayName;
}

void FileBrowserDisplay::setItems(std::vector<ItemDetails> items) {
	//_data._items = items;

}