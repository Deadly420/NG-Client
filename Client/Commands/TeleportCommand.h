#pragma once
#include "ICommand.h"
class TeleportCommand : public Command {
public:
	TeleportCommand();
	~TeleportCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
