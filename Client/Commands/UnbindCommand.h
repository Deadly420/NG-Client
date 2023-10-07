#pragma once
#include <map>

#include "ICommand.h"

class UnbindCommand : public Command {
public:
	UnbindCommand();
	~UnbindCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
