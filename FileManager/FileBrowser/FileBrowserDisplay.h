#pragma once
#include "FileBrowserData.h"

class FileBrowserDisplay
{
private:
	FileBrowserData& _data;

	void displayLeftPanel(int selectedIndex) const;
	void displayRightPanel(const ItemDetails& selectedItem) const;
	void displayTopPanel(const std::string& path, const std::string& commands) const;

	void clearRightPanel(const ItemDetails& item) const;

	void displayLeftItem(const ItemDetails& item) const;
	void displayCommand(const std::string& command) const;

	void displayScreen() const;

	void moveCursor(int index, int oldIndex) const;
public:
	explicit FileBrowserDisplay(FileBrowserData& manager) : _data(manager) {};

	void Display();
	void updateRightPanel(size_t index) const;
	void updateCommandsDisplay(const std::string& command) const;
	void setItems(std::vector<ItemDetails> items);

	void clearFullDisplay() const {
		system("cls");  // Clear screen (Windows)
	}
};

