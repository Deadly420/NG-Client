#pragma once

#include <map>

#include "ICommand.h"

class SetOffhandCommand : public Command {
public:
	SetOffhandCommand();
	~SetOffhandCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
