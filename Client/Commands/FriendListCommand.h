#pragma once
#include "ICommand.h"
class FriendListCommand : public Command {
public:
	FriendListCommand();
	~FriendListCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
