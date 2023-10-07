#pragma once
#include "ICommand.h"
#include <sstream>

class NameSpoofCommand : public Command {
public:
	NameSpoofCommand();
	~NameSpoofCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
