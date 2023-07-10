#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("%s[%sNG%s] %sHidden.", BOLD, AQUA, WHITE, GREEN);
	} else {
		clientMessageF("%s[%sNG%s] %sMod is now visible.", BOLD, AQUA, WHITE, GREEN);
	}
	return true;
}
