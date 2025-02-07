#include "Display.h"
#include <iostream>
#include <iomanip>
#include "ItemDetails.h"

void Display::display(int selectedIndex, const std::string& currentPath, const std::string& command) const {
	this->displayTopPanel(currentPath, command);
	this->displayLeftPanel(selectedIndex);
	this->displayRightPanel(this->_items[selectedIndex]);
}

void Display::displayTopPanel(const std::string& path, const std::string& command) const {
	std::cout << "\033[1;1H"; // Move cursor to the top-left corner
	std::cout << std::left << path << std::endl;
	displayCommand(command);
	std::cout << std::string(80, '-') << std::endl; // Separator line
}

void Display::displayLeftPanel(int selectedIndex) const {
	for (size_t i = 0; i < _items.size(); ++i) {
		std::cout << "\033[" << i + 3 << ";1H"; // Move cursor to the correct line below the top panel
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
	int topOffset = this->_topPanelHeight;
	int startCol = this->panelWidth + this->_rightPanelOffset; // Starting column for the right panel

	std::cout << "\033[" << (topOffset) << ";" << startCol << "H";
	std::cout << std::left << "Name: " << selectedItem.name;
	std::cout << std::endl;

	std::cout << "\033[" << (topOffset + 1) << ";" << startCol << "H";
	std::cout << std::left << "Size: " << selectedItem.size;
	std::cout << std::endl;

	std::cout << "\033[" << (topOffset + 2) << ";" << startCol << "H";
	std::cout << std::left << "Created: " << selectedItem.created;
	std::cout << std::endl;

	std::cout << "\033[" << (topOffset + 3) << ";" << startCol << "H";
	std::cout << std::left << "Modified: " << selectedItem.modified;
	std::cout << std::endl;


	std::cout << "\033[" << (topOffset + 4) << ";" << startCol << "H";
	std::cout << std::left << "Accessed: " << selectedItem.accessed;
	std::cout << std::endl;
}

void Display::clearRightPanel() const {
	for (size_t i = 0; i < _items.size(); ++i) {
		std::cout << "\033[" << i + 3 << ";" << this->panelWidth + 5 << "H"; // Adjusted to start clearing below the top panel
		std::cout << std::string(30, ' '); // Clear the line
	}
}

void Display::moveCursor(int index, int oldIndex) const {
	if (oldIndex >= 0 && oldIndex < static_cast<int>(_items.size())) {
		std::cout << "\033[" << oldIndex + 3 << ";1H  "; // Adjusted to start below the top panel
		this->displayLeftItem(_items[oldIndex]);
	}

	if (index >= 0 && index < static_cast<int>(_items.size())) {
		std::cout << "\033[" << index + 3 << ";1H* "; // Adjusted to start below the top panel
		this->displayLeftItem(_items[index]);
	}

	clearRightPanel();
	if (index >= 0 && index < static_cast<int>(_items.size())) {
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
