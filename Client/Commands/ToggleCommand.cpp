#include "ToggleCommand.h"

#include "../Manager/ModuleManager.h"

ToggleCommand::ToggleCommand() : Command("toggle", "Toggles a module", "<module>") {
	registerAlias("t");
}

ToggleCommand::~ToggleCommand() {
}

bool ToggleCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);
	std::string moduleName = args->at(1);

	assertTrue(moduleName.size() > 0);

	auto modOpt = moduleMgr->getModuleByName(moduleName);
	if (!modOpt.has_value()) {
		clientMessage("%sCould not find Module with name: %s", RED, moduleName.c_str());
		return true;
	}

	auto mod = modOpt.value();
	if (mod->isFlashMode()) {
		clientMessage("%sModule cannot be toggled!", RED);
	} else {
		mod->toggle();
		clientMessage("%s%s is now %s", GREEN, mod->getModuleName(), mod->isEnabled() ? "enabled" : "disabled");
	}

	return true;
}