#pragma once
#include "ICommand.h"

class DupeCommand : public Command {
public:
	DupeCommand();
	~DupeCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
