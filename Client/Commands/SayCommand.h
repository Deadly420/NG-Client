#pragma once
#include "ICommand.h"
#include <sstream>
class SayCommand : public Command {
public:
	SayCommand();
	~SayCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override;
};
