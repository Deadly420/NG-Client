#pragma once
#include "ICommand.h"
class TopCommand : public Command {
public:
	TopCommand();
	~TopCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};