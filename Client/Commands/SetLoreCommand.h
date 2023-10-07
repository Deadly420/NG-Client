#pragma once

#include "ICommand.h"

class SetLoreCommand : public Command {
public:
	SetLoreCommand();
	~SetLoreCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
