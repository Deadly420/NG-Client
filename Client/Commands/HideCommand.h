#pragma once
#include "ICommand.h"
class HideCommand : public Command {
public:
	HideCommand();
	~HideCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
