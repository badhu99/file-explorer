#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Explorer.h"
#include "ItemDetails.h"

class Display {
private:
	std::vector<ItemDetails> _items;
	int panelWidth = 40;
	int _rightPanelOffset = 5;
	int _topPanelHeight = 3;

	void displayLeftPanel(int selectedIndex) const;
	void displayRightPanel(const ItemDetails& selectedItem) const;
	void displayTopPanel(const std::string& path, const std::string& commands) const;

	void clearRightPanel() const;

	void displayLeftItem(const ItemDetails& item) const;
	void displayCommand(const std::string& command) const;
public:
	explicit Display(std::vector<ItemDetails> items) : _items(items) {}
	Display() : _items(std::vector<ItemDetails>()) {};

	void display(int selectedIndex, const std::string& currentPath, const std::string& command) const;
	void moveCursor(int index, int oldIndex) const;
	void updateCommandsDisplay(const std::string& command) const;
	void setItems(std::vector<ItemDetails> items);

	void clearFullDisplay() {
		system("cls");  // Clear screen (Windows)
	}
};

#endif // DISPLAY_H