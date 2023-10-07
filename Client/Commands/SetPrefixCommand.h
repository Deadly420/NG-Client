#pragma once
#include "../Manager/CommandManager.h"

#include "ICommand.h"
class SetPrefixCommand : public Command {
public:
	SetPrefixCommand();
	~SetPrefixCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};