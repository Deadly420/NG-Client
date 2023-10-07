#pragma once
#include "ICommand.h"

class PathCommand : public Command{
public:
	PathCommand();
	~PathCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};
