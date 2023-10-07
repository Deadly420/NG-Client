#pragma once

#include "ICommand.h"
#include "../Manager/ModuleManager.h"
#include "../Module/Render/Waypoints.h"

class WaypointCommand : public Command {
public:
	WaypointCommand();
	~WaypointCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
