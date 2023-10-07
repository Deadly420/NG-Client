#pragma once
#include "ICommand.h"
class HelpCommand : public Command {
public:
	HelpCommand();
	~HelpCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
