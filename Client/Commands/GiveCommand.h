#pragma once
#include "ICommand.h"
class GiveCommand : public Command {
public:
	GiveCommand();
	~GiveCommand();

	// Inherited via Command
	virtual bool execute(std::vector<std::string> *args) override;

private:
	bool giveItem(uint8_t count, int itemId, uint8_t itemData, std::string &tag);
	bool giveItem(uint8_t count, TextHolder &text, uint8_t itemData, std::string &tag);
};
