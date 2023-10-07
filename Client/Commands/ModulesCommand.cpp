#include "ModulesCommand.h"

#include <algorithm>
#include "../Manager/ModuleManager.h"

ModulesCommand::ModulesCommand() : Command("modules", "Lists all modules", "") {
	registerAlias("mods");
}

ModulesCommand::~ModulesCommand() {
}

bool ModulesCommand::execute(std::vector<std::string>* args) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* modules = moduleMgr->getModuleList();
	clientMessage("==========");
	clientMessage("Modules (%i):", modules->size());
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		clientMessage("%s %s- %s%s", mod->getModuleName(), GRAY, ITALIC, mod->getTooltip());
	}

	return true;
}