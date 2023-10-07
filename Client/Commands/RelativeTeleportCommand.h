#pragma once
#include "ICommand.h"
class RelativeTeleportCommand : public Command {
public:
	RelativeTeleportCommand();
	~RelativeTeleportCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
