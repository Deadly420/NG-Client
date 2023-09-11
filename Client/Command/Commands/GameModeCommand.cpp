#include "GameModeCommand.h"

GameModeCommand::GameModeCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GameModeCommand::~GameModeCommand() {
}

bool GameModeCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);

	int gamemode = assertInt(args->at(1));

	if (gamemode >= 0 && gamemode <= 6) {
		Game.getLocalPlayer()->setPlayerGameType(static_cast<GameType>(gamemode));
		clientMessageF("%s[%sNG%s] %sGameMode changed!", BOLD, AQUA, WHITE, GREEN);
	} else {
		clientMessageF("%s[%sNG%s] %sInvalid GameMode!", BOLD, AQUA, WHITE, RED);
	}

	return true;
}
