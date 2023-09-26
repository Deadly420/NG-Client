#pragma once
#include "../Module.h"
#include "../../../Utils/Target.h"
#include "../../Manager/ModuleManager.h"

class Aimbot : public Module {
private:
	bool vertical = true;
	bool sword = false;
	bool click = false;
	float horizontalspeed = 50.f;
	float verticalspeed = 50.f;
	float verticalrange = 40.f;
	float horizontalrange = 60.f;
	bool lock = false;

public:
	float range = 4.f;
	bool mobs = false;

	std::vector<Entity*> targetList;

	Aimbot() : Module(0x0, Category::COMBAT, "Automatically aims at the nearest entity") {
		registerFloatSetting("Range", &range, range, 3.f, 8.f, "Range: Define a range from 3.0 to 8.0");

		// Registering Boolean Settings
		registerBoolSetting("Mobs", &mobs, mobs, "Toggle rendering mobs");
		registerBoolSetting("Require click", &click, click, "Toggle requirement for clicking");
		registerBoolSetting("Only swords/axes", &sword, sword, "Toggle only swords and axes");
		registerBoolSetting("Vertical", &vertical, vertical, "Toggle vertical mode");
		registerBoolSetting("Aimlock", &lock, lock, "Toggle aimlock");

		// Registering More Float Settings
		registerFloatSetting("Horizontal Speed", &horizontalspeed, horizontalspeed, 10.f, 90.f, "Horizontal Speed: Set speed between 10 and 90");
		registerFloatSetting("Vertical Speed", &verticalspeed, verticalspeed, 10.f, 90.f, "Vertical Speed: Adjust speed from 10 to 90");
		registerFloatSetting("Horizontal Range", &horizontalrange, horizontalrange, 20.f, 180.f, "Horizontal Range: Specify a range between 20 and 180");
		registerFloatSetting("Vertical Range", &verticalrange, verticalrange, 20.f, 180.f, "Vertical Range: Define a range from 20 to 180");
	}
	~Aimbot(){};
	struct CompareTargetEnArray {
		bool operator()(Entity* lhs, Entity* rhs) {
			LocalPlayer* localPlayer = Game.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	// Inherited via Module
	virtual const char* getModuleName() override { return "Aim-bot"; }
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		if (!localPlayer) return;

		std::vector<Entity*> allEntities;
		Game.forEachEntity([&](Entity* e, bool) -> void {
			allEntities.push_back(e);
		});

		Vec3 origin = Game.getClientInstance()->levelRenderer->getOrigin();

		// Loop through all our players and retrieve their information
		targetList.clear();
		for (size_t i = 0; i < allEntities.size(); i++) {
			Entity* currentEntity = allEntities.at(i);

			if (!Target::isValidTarget(currentEntity))
				continue;

			float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

			if (dist < range)
				targetList.push_back(currentEntity);
		}

		if (targetList.size() > 0) {
			std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
			Vec2 angle = origin.CalcAngle(*targetList[0]->getPos());
			Vec2 appl = angle.sub(localPlayer->getActorHeadRotationComponent()->rot).normAngles();
			appl.x = -appl.x;
			if ((appl.x < verticalrange && appl.x > -verticalrange) && (appl.y < horizontalrange && appl.y > -horizontalrange) && GameData::canUseMoveKeys()) {
				PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
				ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
				if (sword && !(item->getItem()->isWeapon()))
					return;

				if (click && !Game.isLeftClickDown())
					return;

				if (!lock) {
					appl.x /= (100.f - verticalspeed);
					appl.y /= (100.f - horizontalspeed);
					if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
					if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
				}
				if (!vertical)
					appl.x = 0;
				localPlayer->applyTurnDelta(&appl);
			}
		}
	}
};