#include "PanicCommand.h"

#include "../Manager/ModuleManager.h"

PanicCommand::PanicCommand() : Command("panic", "Disables all Modules", "") {
}

PanicCommand::~PanicCommand() {
}

bool PanicCommand::execute(std::vector<std::string>* args) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* modules = moduleMgr->getModuleList();

	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		mod->setEnabled(false);
	}

	clientMessage("%sDisabled all Modules!", YELLOW);
	return true;
}