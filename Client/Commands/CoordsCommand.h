#pragma once
#include "ICommand.h"
class CoordsCommand : public Command {
public:
	CoordsCommand();
	~CoordsCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
