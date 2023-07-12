#pragma once

#include "ICommand.h"
#include "../../Module/ModuleManager.h"
#include "../../Module/Render/Waypoints.h"

class WaypointCommand : public IMCCommand {
public:
	WaypointCommand();
	~WaypointCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
