#pragma once
#include "ICommand.h"
class DamageCommand : public Command {
public:
	DamageCommand();
	~DamageCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
