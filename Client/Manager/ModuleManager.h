#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"
#include "../Module/Module.h"

// World
#include "../Module/World/InstaBreak.h"
#include "../Module/World/Scaffold.h"
#include "../Module/World/Disabler.h"
#include "../Module/World/Tower.h"
#include "../Module/World/Nuker.h"

// Hud
#include "../Module/Hud/ToggleSounds.h"
#include "../Module/Hud/FontChanger.h"
#include "../Module/Hud/ClickGuiMod.h"
#include "../Module/Hud/Arraylist.h"
#include "../Module/Hud/Newui.h"

// Combat
#include "../Module/Combat/CrystalAura.h"
#include "../Module/Combat/AutoClicker.h"
#include "../Module/Combat/TriggerBot.h"
#include "../Module/Combat/BowAimbot.h"
#include "../Module/Combat/AutoTotem.h"
#include "../Module/Combat/Killaura.h"
#include "../Module/Combat/AutoPot.h"
#include "../Module/Combat/FastUse.h"
#include "../Module/Combat/Hitbox.h"
#include "../Module/Combat/Aimbot.h"
#include "../Module/Combat/Teams.h"
#include "../Module/Combat/Reach.h"

// Player
#include "../Module/Player/InventoryCleaner.h"
#include "../Module/Player/StackableItem.h"
#include "../Module/Player/ChestStealer.h"
#include "../Module/Player/BlockReach.h"
#include "../Module/Player/NoFriends.h"
#include "../Module/Player/ChestAura.h"
#include "../Module/Player/AutoArmor.h"
#include "../Module/Player/MidClick.h"
#include "../Module/Player/AntiBot.h"
#include "../Module/Player/NoFall.h"
#include "../Module/Player/XP.h"

// Miscellaneous
#include "../Module/Misc/AntiImmobile.h"
#include "../Module/Misc/EditionFaker.h"
#include "../Module/Misc/OffhandAllow.h"
#include "../Module/Misc/Criticals.h"
#include "../Module/Misc/NoPacket.h"
#include "../Module/Misc/Teleport.h"
#include "../Module/Misc/Spammer.h"
#include "../Module/Misc/Freecam.h"
#include "../Module/Misc/Crasher.h"
#include "../Module/Misc/Breaker.h"
#include "../Module/Misc/Timer.h"
#include "../Module/Misc/Blink.h"
#include "../Module/Misc/Derp.h"

// Movement
#include "../Module/Movement/FollowPathModule.h"
#include "../Module/Movement/InventoryMove.h"
#include "../Module/Movement/NoSlowDown.h"
#include "../Module/Movement/FastLadder.h"
#include "../Module/Movement/AutoSprint.h"
#include "../Module/Movement/AutoGapple.h"
#include "../Module/Movement/AutoSneak.h"
#include "../Module/Movement/FastStop.h"
#include "../Module/Movement/Velocity.h"
#include "../Module/Movement/HighJump.h"
#include "../Module/Movement/AntiVoid.h"
#include "../Module/Movement/BoatFly.h"
#include "../Module/Movement/AirSwim.h"
#include "../Module/Movement/AirJump.h"
#include "../Module/Movement/Spider.h"
#include "../Module/Movement/Twerk.h"
#include "../Module/Movement/Speed.h"
#include "../Module/Movement/Phase.h"
#include "../Module/Movement/NoWeb.h"
#include "../Module/Movement/Jesus.h"
#include "../Module/Movement/Glide.h"
#include "../Module/Movement/Step.h"
#include "../Module/Movement/Bhop.h"
#include "../Module/Movement/Fly.h"

// Render
#include "../Module/Render/MinecraftRGB.h"
#include "../Module/Render/VanillaPlus.h"
#include "../Module/Render/TimeChanger.h"
#include "../Module/Render/RainbowSky.h"
#include "../Module/Render/FullBright.h"
#include "../Module/Render/StorageESP.h"
#include "../Module/Render/KeyStrokes.h"
#include "../Module/Render/ServerInfo.h"
#include "../Module/Render/TargetHUD.h"
#include "../Module/Render/ViewModel.h"
#include "../Module/Render/Waypoints.h"
#include "../Module/Render/NoHurtcam.h"
#include "../Module/Render/ArmourHud.h"
#include "../Module/Render/NightMode.h"
#include "../Module/Render/Watermark.h"
#include "../Module/Render/Freelook.h"
#include "../Module/Render/NameTags.h"
#include "../Module/Render/Compass.h"
#include "../Module/Render/NoSwing.h"
#include "../Module/Render/Tracer.h"
#include "../Module/Render/Radar.h"
#include "../Module/Render/Trail.h"
#include "../Module/Render/Zoom.h"
#include "../Module/Render/Xray.h"
#include "../Module/Render/ESP.h"
#include "../Module/Render/FPS.h"
#include "../Module/Render/CPS.h"
#include "../Module/Render/BPS.h"

// Entity
#include "../Module/Entity/EntityLongJump.h"
#include "../Module/Entity/EntitySpider.h"
#include "../Module/Entity/EntityJesus.h"
#include "../Module/Entity/EntitySpeed.h"
#include "../Module/Entity/EntityBhop.h"
#include "../Module/Entity/EntityFly.h"

#ifdef _DEBUG
#include "../Module/World/PacketLogger.h"
#include "../Module/Misc/TestModule.h"
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
	void onImGuiRender();
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
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())) {
				return pRet;
			}
		}
		return nullptr;
	};

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
