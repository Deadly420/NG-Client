#include "HideCommand.h"

HideCommand::HideCommand() : Command("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessage("%s[%sNG%s] %sHidden.", BOLD, AQUA, WHITE, GREEN);
	} else {
		clientMessage("%s[%sNG%s] %sMod is now visible.", BOLD, AQUA, WHITE, GREEN);
	}
	return true;
}
