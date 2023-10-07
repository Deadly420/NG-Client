#include "BruhCommand.h"

BruhCommand::BruhCommand() : Command("bruh", "bruh moment", "bruh") {
}

BruhCommand::~BruhCommand() {
}

bool BruhCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);

	clientMessage("bruh moment");
	return true;
}
