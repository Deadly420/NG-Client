#pragma once
#include "ICommand.h"
class PanicCommand : public Command {
public:
	PanicCommand();
	~PanicCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
