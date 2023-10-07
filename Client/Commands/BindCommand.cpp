#include "BindCommand.h"

#include "../Manager/ModuleManager.h"
BindCommand::BindCommand() : Command("bind", "Binds modules to specific keys", "<module> <key>") {
	registerAlias("b");
}
BindCommand::~BindCommand() {
}

bool BindCommand::execute(std::vector<std::string>* args) {
	if (args->size() < 2) {
		clientMessage("%sAt least two arguments are required.", RED);
		return true;
	}

	std::string moduleName = args->at(1);
	if (moduleName.empty()) {
		clientMessage("%sModule name cannot be empty.", RED);
		return true;
	}

	auto modOpt = moduleMgr->getModuleByName(moduleName);
	if (!modOpt.has_value()) {
		clientMessage("%sCould not find module with name: %s", RED, moduleName.c_str());
		return true;
	}
	auto mod = modOpt.value();

	if (args->size() >= 3) {
		std::string key = args->at(2);
		if (key.empty()) {
			clientMessage("%sKey cannot be empty.", RED);
			return true;
		}

		if (key == "none") {
			mod->setKeybind(0x0);
			clientMessage("%sSuccessfully unbound %s!", GREEN, mod->getModuleName());
			return true;
		}

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		// Check if key is a valid key name
		bool foundKey = false;
		for (int i = 0; i < 190; i++) {
			const char* haystack = KeyNames[i];
			std::string haystackLowercase = haystack;
			std::transform(haystackLowercase.begin(), haystackLowercase.end(), haystackLowercase.begin(), ::tolower);

			if (haystackLowercase == key) {
				mod->setKeybind(i);
				clientMessage("%sThe keybind of %s is now '%s'", GREEN, mod->getModuleName(), haystack);
				foundKey = true;
				break;
			}
		}

		if (!foundKey) {
			clientMessage("%sInvalid key!", RED);
		}
		return true;
	} else {
		clientMessage("%s%s is currently bound to %s", RED, mod->getModuleName(), Utils::getKeybindName(mod->getKeybind()));
		return true;
	}
}