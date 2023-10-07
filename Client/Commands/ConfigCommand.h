#pragma once
#include "ICommand.h"
#include "../Manager/ConfigManager.h"

class ConfigCommand : public Command {
public:
	ConfigCommand();
	~ConfigCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};