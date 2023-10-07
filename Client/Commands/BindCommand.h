#pragma once
#include <map>

#include "ICommand.h"

class BindCommand : public Command {
public:
	BindCommand();
	~BindCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
