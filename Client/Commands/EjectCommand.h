#pragma once
#include "ICommand.h"
class EjectCommand : public Command {
public:
	EjectCommand();
	~EjectCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
