#pragma once
#include "ICommand.h"

class TestCommand : public Command {
public:
	TestCommand();
	~TestCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
