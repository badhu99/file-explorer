#include "Display.h"
#include <iostream>
#include <iomanip>
#include "ItemDetails.h"

void Display::display(int selectedIndex, const std::string& currentPath, const std::string& command) const {
	displayTopPanel(currentPath, command);
	displayLeftPanel(selectedIndex);
	displayRightPanel(this->_items[selectedIndex]);
}

void Display::displayTopPanel(const std::string& path, const std::string& command) const {
	std::cout << "\033[1;1H"; // Move cursor to the top-left corner
	std::cout << std::left << path << std::endl;
	displayCommand(command);
	std::cout << std::string(80, '-') << std::endl; // Separator line
}

void Display::displayLeftPanel(int selectedIndex) const {
	for (size_t i = 0; i < _items.size(); ++i) {
		std::cout << "\033[" << i + _topPanelHeight << ";1H"; // Move cursor to the correct line below the top panel
		if (i == selectedIndex) {
			std::cout << "* ";
		}
		else {
			std::cout << "  ";
		}
		displayLeftItem(_items[i]);
		std::cout << std::endl;
	}
}

void Display::displayRightPanel(const ItemDetails& selectedItem) const {
	int startCol = this->panelWidth + this->_rightPanelOffset; // Starting column for the right panel

	for (size_t i = 0; i < selectedItem.data.size(); ++i) {
		const auto& itemData = selectedItem.data[i];
		std::cout << "\033[" << _topPanelHeight + i << ";" << startCol << "H";
		std::cout << itemData << std::endl;
	}
}

void Display::clearRightPanel(const ItemDetails& item) const {
	int startCol = this->panelWidth + this->_rightPanelOffset;

	for (auto i = 0; i < item.data.size(); i++) {
		auto itemData = item.data[i];
		auto charLength = itemData.displayName.length();
		std::cout << "\033[" << _topPanelHeight + i << ";" << startCol + charLength << "H"; // Adjusted to start clearing below the top panel
		std::cout << std::string(30, ' ');
	}
}

void Display::moveCursor(int index, int oldIndex) const {
	if (oldIndex >= 0 && oldIndex < static_cast<int>(_items.size())) {
		std::cout << "\033[" << oldIndex + _topPanelHeight << ";1H  "; // Adjusted to start below the top panel
		this->displayLeftItem(_items[oldIndex]);
	}

	if (index >= 0 && index < static_cast<int>(_items.size())) {
		std::cout << "\033[" << index + _topPanelHeight << ";1H* "; // Adjusted to start below the top panel
		this->displayLeftItem(_items[index]);
	}
}

void Display::updateRightPanel(int index) const {
	if (index >= 0 && index < static_cast<int>(_items.size())) {
		clearRightPanel(_items[index]);
		displayRightPanel(_items[index]);
	}
}

void Display::updateCommandsDisplay(const std::string& command) const {

	std::cout << "\033[2;1H"; // Move cursor to the commands line
	std::cout << std::string(80, ' '); // Clear the commands line
	std::cout << "\033[2;1H"; // Move cursor back to the commands line
	this->displayCommand(command);
}

void Display::displayLeftItem(const ItemDetails& item) const {
	std::string displayName = item.name;
	if (item.isDirectory) {
		displayName += "/";
	}
	std::cout << std::left << std::setw(this->panelWidth - 2) << displayName;
}

void Display::displayCommand(const std::string& command) const {
	std::cout << std::left << "$ " << command << std::endl;
}
void Display::setItems(std::vector<ItemDetails> items) {
	_items = items;
}
