#include "HelpCommand.h"

#include "../Manager/CommandManager.h"

HelpCommand::HelpCommand() : Command("help", "Lists all commands", "") {
	registerAlias("h");
}

HelpCommand::~HelpCommand() {
}

bool HelpCommand::execute(std::vector<std::string>* args) {
	clientMessage("==========");
	std::vector<Command*>* commandList = cmdMgr->getCommandList();

	for (auto it = commandList->begin(); it != commandList->end(); ++it) {
		Command* command = *it;
		clientMessage("%s%s - %s%s", command->getCommand(), GRAY, ITALIC, command->getDescription());
	}

	return true;
}
