#include "SettingsActionHandler.h"

bool SettingsActionHandler::HandleInput(const char& key)
{
	switch (key) {
	case 27:  // Escape key
		return true;
	}
}
