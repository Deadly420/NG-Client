#pragma once
#include "ICommand.h"
class GameModeCommand : public Command {
public:
	GameModeCommand();
	~GameModeCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
