#pragma once

#include "../../Memory/GameData.h"

#include "../Command/Commands/BindCommand.h"
#include "../Command/Commands/BruhCommand.h"
#include "../Command/Commands/CoordsCommand.h"
#include "../Command/Commands/DamageCommand.h"
#include "../Command/Commands/DupeCommand.h"
#include "../Command/Commands/EjectCommand.h"
#include "../Command/Commands/EnchantCommand.h"
#include "../Command/Commands/FriendListCommand.h"
#include "../Command/Commands/GameModeCommand.h"
#include "../Command/Commands/GiveCommand.h"
#include "../Command/Commands/HelpCommand.h"
#include "../Command/Commands/HideCommand.h"
#include "../Command/Commands/ICommand.h"
#include "../Command/Commands/ModulesCommand.h"
#include "../Command/Commands/PanicCommand.h"
#include "../Command/Commands/PlayerTeleportCommand.h"
#include "../Command/Commands/RelativeTeleportCommand.h"
#include "../Command/Commands/SayCommand.h"
#include "../Command/Commands/ServerCommand.h"
#include "../Command/Commands/SpammerCommand.h"
#include "../Command/Commands/TeleportCommand.h"
#include "../Command/Commands/ToggleCommand.h"
#include "../Command/Commands/TopCommand.h"
#include "../Command/Commands/UnbindCommand.h"
#include "../Command/Commands/setoffhandCommand.h"
#include "../Command/Commands/CommandBlockExploitCommand.h"
#include "../Command/Commands/ConfigCommand.h"
#include "../Command/Commands/NameSpoofCommand.h"
#include "../Command/Commands/SetPrefixCommand.h"
#include "../Command/Commands/NbtCommand.h"
#include "../Command/Commands/WaypointCommand.h"
#include "../Command/Commands/XpCommand.h"
#include "../Command/Commands/PathCommand.h"
#include "../Command/Commands/SetLoreCommand.h"

#ifdef _DEBUG
#include "../Command/Commands/TestCommand.h"
#endif

#include <algorithm>
#include <string>
#include <vector>

class CommandMgr {
private:
	GameData* gameData;
	std::vector<IMCCommand*> commandList;

public:
	CommandMgr(GameData* gm);
	~CommandMgr();

	char prefix = '.';

	void initCommands();
	void disable();
	std::vector<IMCCommand*>* getCommandList();

	void execute(char* message);
};

extern CommandMgr* cmdMgr;
