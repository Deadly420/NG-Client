#pragma once
#include "ICommand.h"
class PlayerTeleportCommand : public Command {
public:
	PlayerTeleportCommand();
	~PlayerTeleportCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
