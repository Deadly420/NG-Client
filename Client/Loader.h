#pragma once

#include "../Utils/Logging.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "../Memory/GameData.h"
#include "../Hooks/Hooks.h"
#include "../Hooks/ImGuiHooks.h"
#include "../Hooks/D2DHooks.h"
#include "../Memory/MinHook.h"
#include "../SDK/ChestBlockActor.h"
#include "../SDK/ClientInstance.h"
#include "../SDK/ClientInstanceScreenModel.h"
#include "../SDK/Entity.h"
#include "../SDK/GameMode.h"
#include "../SDK/Packet.h"
#include "../Utils/HMath.h"
#include "../Utils/Target.h"
#include "../Utils/TextFormat.h"
#include "../Utils/Utils.h"
#include "../include/WinHttpClient.h"
#include "Manager/CommandMgr.h"
#include "Manager/ConfigManager.h"
#include "Menu/ClickGui.h"
#include "Manager/ModuleManager.h"
#include "ImmediateGui.h"

class Loader {
public:
	static bool isRunning;
};