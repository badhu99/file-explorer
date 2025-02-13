#pragma once
#include "FileBrowserData.h"

class FileBrowserActionHandler
{
private:
	FileBrowserData& _data;
	void handleUpArrow();
	void handleDownArrow();
	void handleLeftArrow();
	void handleRightArrow();
	void handleEnter();
	void handleTab();
	void handleBackspace();
	void handleDefault(const char& key);

public:
	explicit FileBrowserActionHandler(FileBrowserData& data) : _data(data) {};

	void HandleInput(const char& key);
	void ShowInitialDisplay();
};

