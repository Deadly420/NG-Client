#pragma once
#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class Desync : public Module {
public:
	SettingEnum DelayMode = SettingEnum(this);
	Desync();
	~Desync();

	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	std::vector<InventoryTransactionPacket*> InventoryPacketHolder;
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
	inline std::vector<InventoryTransactionPacket*>* getInventoryPacketHolder() { return &InventoryPacketHolder; };
	bool desync = false;
	bool doDesync = false;
	int desyncMs = 550;
	int desyncPacket = 50;
	bool resetDesyncSetting = false;
	__int64 desyncLastMS;

	// Inherited via Module
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};