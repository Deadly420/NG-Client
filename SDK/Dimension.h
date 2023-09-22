#pragma once

#include "BlockLegacy.h"
#include "../Utils/HMath.h"

class Entity;
class HashedString;
class Packet;
class Player;
class Weather;

class Dimension {
public:
	BUILD_ACCESS(this, TextHolder, dimensionName, 0x20);
	BUILD_ACCESS(this, int16_t, minHeight, 0xC8);
	BUILD_ACCESS(this, int16_t, maxHeight, 0xCA);
	//BUILD_ACCESS(this, class BrightnessRamp*, brightnessRamp, 0x128);
	BUILD_ACCESS(this, int, dimensionId, 0x160);
	BUILD_ACCESS(this, bool, hasCeiling, 0x165);
	BUILD_ACCESS(this, bool, hasSkylight, 0x167);
	BUILD_ACCESS(this, Weather *, weather, 0x1A8);
	//BUILD_ACCESS(this, __int64, seasons, 0x1B0);

private:
	virtual void unknown1(); // 1

public:
	virtual int getDimensionId(void); // 2
	virtual void sendPacketForPosition(Vec3i const &, Packet const &, Player const *); // 3
	virtual void flushLevelChunkGarbageCollector(void); // 4
	virtual void init(void); // 5
	virtual void tick(void); // 6
	virtual void tickRedstone(void); // 7

private:
	virtual void unknown2(); // 8
	virtual void unknown3(); // 9
	virtual void unknown4(); // 10
	virtual void unknown5(); // 11
	virtual void unknown6(); // 12

public:
	virtual float getBrightnessDependentFogColor(__int64 const &, float); // 13

private:
	virtual void unknown7(); // 14
	virtual void unknown8(); // 15

public:
	virtual int getCloudHeight(void); // 16
	virtual int getDefaultBiome(void); // 17

private:
	virtual void unknown9(); // 18
	virtual void unknown10(); // 19

public:
	virtual int getSize(__int64); // 20

private:
	virtual void unknown11(); // 21
	virtual void unknown12(); // 22

public:
	virtual int getClearColorScale(void); // 23

private:
	virtual void unknown13(); // 24
public:
	virtual bool isDay(void); // 25
	virtual float getTimeOfDay(int, float); // 26
	virtual float getSunIntensity(float, Vec3 const &, float); // 27

private:
	virtual void unknown14(); // 28
	virtual void unknown15(); // 29

public:
	virtual void sendBroadcast(Packet const &, Player *); // 30
	virtual bool is2DPositionRelevantForPlayer(Vec3i const &, Player &); // 31
	virtual bool isActorRelevantForPlayer(Player &, Entity const &); // 32
	virtual int getLightTextureImageBuilder(void); // 33
	virtual int getBrightnessRamp(void); // 34
	virtual void startLeaveGame(void); // 35
	virtual void _createChunkBuildOrderPolicy(void); // 36

private:
	virtual void unknown16(); // 37
	virtual void unknown17(); // 38
};

class Weather {
public:
	BUILD_ACCESS(this, float, rainVar1, 0x34);
	BUILD_ACCESS(this, float, rainLevel, 0x38);
	BUILD_ACCESS(this, float, lightningVar1, 0x40);
	BUILD_ACCESS(this, float, lightningLevel, 0x44);
	BUILD_ACCESS(this, float, fogLevel, 0x4C);

	float getRainLevel(float a1) {
		return (rainLevel - rainVar1) * a1 + rainVar1;
	}

	float getLightningLevel(float a1) {
		return (lightningLevel - lightningVar1) * a1 + lightningVar1;
	}

	bool isRaining() {
		return rainLevel > 0.2f;
	}

	bool isLightning() {
		return lightningLevel * rainLevel > 0.89999998f;
	}

	bool isRainingAt(BlockSource* source, Vec3i pos) {
		using isRainingAt = void(__thiscall *)(Weather *, BlockSource *, Vec3i *);
		static isRainingAt isRainingAtFunc = reinterpret_cast<isRainingAt>(FindSignature("48 89 5C 24 ? 57 48 83 EC 20 49 8B D8 48 8B FA E8 ? ? ? ? 84 C0 74 2E 48 8B D3 48 8B CF E8 ? ? ? ? 4C 8B C3 48 8B D7 48 8B C8 E8 ? ? ? ? 0F 2F 05 ? ? ? ? 0F 97"));
		isRainingAtFunc(this, source, &Vec3i(pos));
	}

	bool isSnowingAt(BlockSource* source, Vec3i pos) {
		using isSnowingAt = void(__thiscall *)(Weather *, BlockSource *, Vec3i *);
		static isSnowingAt isSnowingAtFunc = reinterpret_cast<isSnowingAt>(FindSignature("48 89 5C 24 ? 57 48 83 EC 20 49 8B D8 48 8B FA E8 ? ? ? ? 84 C0 74 2E 48 8B D3 48 8B CF E8 ? ? ? ? 4C 8B C3 48 8B D7 48 8B C8 E8 ? ? ? ? 0F 2F 05 ? ? ? ? 0F 96"));
		isSnowingAtFunc(this, source, &Vec3i(pos));
	}

	// Removed Vtable because it's filled with unknown shit pointing to nowhere
};