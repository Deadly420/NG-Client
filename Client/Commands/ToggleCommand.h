#pragma once
#include "ICommand.h"
class ToggleCommand : public Command {
public:
	ToggleCommand();
	~ToggleCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
