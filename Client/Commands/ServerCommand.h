#pragma once
#include "ICommand.h"

class ServerCommand : public Command {
public:
	ServerCommand();
	~ServerCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
