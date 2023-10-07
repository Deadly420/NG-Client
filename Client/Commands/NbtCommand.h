#pragma once
#include "ICommand.h"

class NbtCommand : public Command {
public:
	NbtCommand();
	~NbtCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
	const char* getUsage(const char* alias) override;
};
