#include "UnbindCommand.h"

#include "../Manager/ModuleManager.h"

UnbindCommand::UnbindCommand() : Command("unbind", "unbind modules", "<module | all>") {
}

UnbindCommand::~UnbindCommand() {
}

bool UnbindCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);
	std::string moduleName = args->at(1);

	assertTrue(moduleName.size() > 0);

	if (moduleName == "all") {
		if (args->size() >= 3 && args->at(2) == "force") {
			auto lock = moduleMgr->lockModuleList();
			std::vector<std::shared_ptr<Module>>* modules = moduleMgr->getModuleList();
			for (auto it = modules->begin(); it != modules->end(); ++it) {
				auto mod = *it;
				mod->setKeybind(0x0);
			}
			clientMessage("%sUnbound all modules!", YELLOW);
		} else {
			clientMessage("%sAre you sure? This will unbind %sALL%s%s modules!", RED, BOLD, RESET, RED);
			clientMessage("%sUse %s.unbind all force%s to unbind all modules", RED, WHITE, RED);
		}
		return true;
	}

	auto modOpt = moduleMgr->getModuleByName(moduleName);
	if (!modOpt.has_value()) {
		clientMessage("%sCould not find module with name: %s", RED, moduleName.c_str());
		return true;
	}

	auto mod = modOpt.value();
	mod->setKeybind(0x0);
	clientMessage("%sSuccessfully unbound %s!", GREEN, mod->getModuleName());
	return true;
}