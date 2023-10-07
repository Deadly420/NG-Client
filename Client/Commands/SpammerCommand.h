#pragma once
#include "ICommand.h"
#include <sstream>

class SpammerCommand : public Command {
public:
	SpammerCommand();
	~SpammerCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
