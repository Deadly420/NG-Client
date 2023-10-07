#pragma once

#include "ICommand.h"

class XpCommand : public Command {
public:
	XpCommand();
	~XpCommand();

	bool execute(std::vector<std::string>* args) override;
};
