#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"
#include "Module.h"

#include "Movement/FollowPathModule.h"
#include "Player/InventoryCleaner.h"
#include "Player/StackableItem.h"
#include "Movement/InventoryMove.h"
#include "Misc/AntiImmobile.h"
#include "Misc/EditionFaker.h"
#include "Player/ChestStealer.h"
#include "Render/MinecraftRGB.h"
#include "Misc/OffhandAllow.h"
#include "Hud/FontChanger.h"
#include "Render/VanillaPlus.h"
#include "Render/TimeChanger.h"
#include "Combat/CrystalAura.h"
#include "Hud/ClickGuiMod.h"
#include "Combat/AutoClicker.h"
#include "Combat/TriggerBot.h"
#include "Render/RainbowSky.h"
#include "Movement/NoSlowDown.h"
#include "World/InstaBreak.h"
#include "Player/BlockReach.h"
#include "Render/FullBright.h"
#include "Movement/FastLadder.h"
#include "Render/StorageESP.h"
#include "Movement/AutoSprint.h"
#include "Movement/AutoGapple.h"
#include "Render/ViewModel.h"
#include "Hud/Arraylist.h"
#include "Hud/ToggleSounds.h"
#include "Render/Waypoints.h"
#include "Render/NoHurtcam.h"
#include "Render/NightMode.h"
#include "Player/NoFriends.h"
#include "Render/HudModule.h"
#include "Player/ChestAura.h"
#include "Combat/BowAimbot.h"
#include "Combat/AutoTotem.h"
#include "Misc/Criticals.h"
#include "Movement/AutoSneak.h"
#include "Player/AutoArmor.h"
#include "Movement/FastStop.h"
#include "Render/Freelook.h"
#include "World/Scaffold.h"
#include "Misc/NoPacket.h"
#include "Movement/Velocity.h"
#include "Render/NameTags.h"
#include "Player/MidClick.h"
#include "Combat/Killaura.h"
#include "Movement/HighJump.h"
#include "Misc/Teleport.h"
#include "Movement/AntiVoid.h"
#include "Render/Compass.h"
#include "Render/NoSwing.h"
#include "Misc/Spammer.h"
#include "Misc/Freecam.h"
#include "Misc/Crasher.h"
#include "Misc/Breaker.h"
#include "Player/AntiBot.h"
#include "Movement/AirSwim.h"
#include "Movement/AirJump.h"
#include "Movement/Spider.h"
#include "Render/Tracer.h"
#include "Player/NoFall.h"
#include "Combat/Hitbox.h"
#include "Combat/Aimbot.h"
#include "Movement/Twerk.h"
#include "Render/Radar.h"
#include "Combat/Teams.h"
#include "World/Tower.h"
#include "Misc/Timer.h"
#include "Movement/Speed.h"
#include "Combat/Reach.h"
#include "Movement/Phase.h"
#include "World/Nuker.h"
#include "Movement/NoWeb.h"
#include "Movement/Jesus.h"
#include "Movement/Glide.h"
#include "Misc/Blink.h"
#include "Render/Zoom.h"
#include "Render/Xray.h"
#include "Movement/Step.h"
#include "Misc/Derp.h"
#include "Movement/Bhop.h"
#include "Player/Nbt.h"
#include "Movement/Fly.h"
#include "Render/ESP.h"

#include "Entity/EntityLongJump.h"
#include "Entity/EntitySpider.h"
#include "Entity/EntityJesus.h"
#include "Entity/EntitySpeed.h"
#include "Entity/EntityBhop.h"
#include "Entity/EntityFly.h"

#ifdef _DEBUG
#include "World/PacketLogger.h"
#include "Misc/TestModule.h"
#endif


class ModuleManager {
private:
	GameData* gameData;
	std::vector<std::shared_ptr<Module>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;

public:
	~ModuleManager();
	ModuleManager(GameData* gameData);
	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(GameMode* gameMode);
	void onAttack(Entity* attackedEnt);
	void onWorldTick(GameMode* gameMode);
	void onKeyUpdate(int key, bool isDown);
	void onKey(int key, bool isDown, bool& shouldCancel);
	void onPreRender(MinecraftUIRenderContext* renderCtx);
	void onPostRender(MinecraftUIRenderContext* renderCtx);
	void onLevelRender();
	void onMove(MoveInputHandler* handler);
	void onPlayerTick(Player* player);
	void onSendPacket(Packet*);
	void onSendClientPacket(Packet*);
	void onBaseTick(Entity*);

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(moduleListMutex); }
	
	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<Module>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	/*
	 *	Use as follows: 
	 *		Module* mod = moduleMgr.getModule<NoKnockBack>(); 
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !	
	 */
	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())){
				
				return pRet;
			}
		}
		return nullptr;
	};

	// Dont Use this functions unless you absolutely need to. The function above this one works in 99% of cases
	std::optional<std::shared_ptr<Module>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
		
		auto lock = lockModuleList();
		for (std::vector<std::shared_ptr<Module>>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
			std::shared_ptr<Module> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<Module>>(mod);
		}
		return std::optional<std::shared_ptr<Module>>();
	}
};

extern ModuleManager* moduleMgr;
