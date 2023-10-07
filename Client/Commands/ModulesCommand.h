#pragma once
#include "ICommand.h"
class ModulesCommand : public Command {
public:
	ModulesCommand();
	~ModulesCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
