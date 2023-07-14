#pragma once
#include "../Module.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

class Aimbot : public Module {
public:
	float range = 4.f;
	bool vertical = true;
	bool sword = false;
	bool click = false;
	float horizontalspeed = 50.f;
	float verticalspeed = 50.f;
	float verticalrange = 40.f;
	float horizontalrange = 60.f;
	bool lock = false;

	std::vector<Entity*> targetList;

	Aimbot() : Module(0x0, Category::COMBAT, "Automatically aims at the nearest entity") {
		registerFloatSetting("range", &range, range, 3.f, 8.f);
		registerBoolSetting("Require click", &click, click);
		registerBoolSetting("only swords/axes", &sword, sword);
		registerBoolSetting("vertical", &vertical, vertical);
		registerFloatSetting("horizontal speed", &horizontalspeed, horizontalspeed, 10.f, 90.f);
		registerFloatSetting("vertical speed", &verticalspeed, verticalspeed, 10.f, 90.f);
		registerFloatSetting("horizontal range", &horizontalrange, horizontalrange, 20.f, 180.f);
		registerFloatSetting("vertical range", &verticalrange, verticalrange, 20.f, 180.f);
		registerBoolSetting("aimlock", &lock, lock);
	}
	~Aimbot(){};
	struct CompareTargetEnArray {
		bool operator()(Entity* lhs, Entity* rhs) {
			LocalPlayer* localPlayer = Game.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	// Inherited via Module
	virtual const char* getModuleName() override { return "Aimbot"; }
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
			Vec2 appl = angle.sub(localPlayer->viewAngles).normAngles();
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