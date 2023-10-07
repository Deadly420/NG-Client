#pragma once
#include "ICommand.h"
class EnchantCommand : public Command {
private:
	std::map<std::string, int> enchantMap;

public:
	EnchantCommand();
	~EnchantCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
