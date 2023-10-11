#pragma once

#include "../../Manager/ModuleManager.h"
#include "../Module.h"
//
class Regen : public Module {
private:
	struct redstone {
		Vec3i blockPos;
		int destroyTicks = 0;
	};
	std::vector<redstone> multiRedstone;
	bool includePos(Vec3i pos);
	bool selectPickaxe();
	bool hasPickaxe();
	float animYaw = 0.f;
	Vec3i blockPos;
	Vec3 tempblockPos;

	float range = 4.5f;
	int delay = 13;
	float animYawB;
	float animPitchB;
	bool smooth = false;

	int tick = 0;
	int slot = 0;
	bool rot = false;
	bool firstbreak = false;
	bool continuemine = false;
	int rottime = 0;
	Vec3 OldBlockPos;

	float openAnim = 1.f;
	int openTime = 0;
	int openTimeOffset = 0;

public:
	int enabledticks;
	bool hasDestroyed = false;
	bool destroy = false;
	int blocksBroke = 0;
	bool swing = false;
	bool rotation = false;
	bool render = false;
	bool isregen = false;
	bool canattack = true;
	bool showrotation = false;

	SettingEnum mode = SettingEnum(this);

	virtual void onPostRender(MinecraftUIRenderContext* renderCtx);
	virtual void onSendPacket(Packet* packet) override;
	virtual void onPlayerTick(Player* player);
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	Regen();
};