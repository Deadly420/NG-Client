#pragma once
#include "ICommand.h"
class BruhCommand : public Command {
public:
	BruhCommand();
	~BruhCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
