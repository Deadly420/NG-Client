#pragma once
#include "../Module.h"
class AntiBot : public Module {
private:
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;
	bool playerCheck = true;

public:
	AntiBot::AntiBot() : Module(0, Category::PLAYER, "filter bots and non player char") {
		registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck, "Hitbox Check: Enable or disable hitbox checking");
		registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck, "Invisible Check: Enable or disable invisible entity checking");
		registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck, "EntityID Check: Enable or disable entity ID checking");
		registerBoolSetting("Other Check", &otherCheck, otherCheck, "Other Check: Enable or disable other checks");
		registerBoolSetting("Extra Check", &extraCheck, extraCheck, "Extra Check: Enable or disable extra checks");
		registerBoolSetting("Player Check", &playerCheck, playerCheck, "Player Check: Enable or disable player checking");
	}
	~AntiBot(){};

	inline bool isHitboxCheckEnabled() {
		return hitboxCheck && this->isEnabled();
	}
	inline bool isNameCheckEnabled() {
		return false;
	}
	inline bool isInvisibleCheckEnabled() {
		return invisibleCheck && this->isEnabled();
	}
	inline bool isEntityIdCheckEnabled() {
		return entityIdCheck && this->isEnabled();
	}
	inline bool isOtherCheckEnabled() {
		return otherCheck && this->isEnabled();
	}
	inline bool isExtraCheckEnabled() {
		return this->extraCheck && this->isEnabled();
	}
	inline bool isPlayerCheckEnabled() {
		return playerCheck && isEnabled();
	}

	virtual const char* getModuleName() override {
		return "AntiBot";
	}
};