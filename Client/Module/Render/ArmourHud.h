#pragma once
#include "../../../Utils/DrawUtils.h"
#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class ArmourHud : public Module {
public:
	float armorX = 210.f;
	float armorY = 55.f;
	float scale = 1.f;
	float spacing = 16.f;

	ArmourHud() : Module(0x0, Category::RENDER, "Renders the armour that you are wearing") {
		registerFloatSetting("Spacing", &spacing, spacing, 0.1f, 16.f, "Spacing: Adjust spacing from 0.1 to 16");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.f, "Size: Control the size from 0.1 to 1");
		registerFloatSetting("Pos-X", &armorX, armorX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Adjust horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &armorY, armorY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Modify vertical position from 0 to the window height");
	};
	~ArmourHud(){};

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;

		if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			static float constexpr opacity = 0.25f;
			LocalPlayer* player = Game.getLocalPlayer();
			float yVal = armorY;
			float xVal = armorX;
			for (int i = 0; i < 4; i++) {
				ItemStack* stack = player->getArmor(i);
				if (stack->item != nullptr) {
					DrawUtils::drawItem(stack, Vec2(xVal, yVal), opacity, scale, stack->isEnchanted());
					xVal += (scale + spacing);
				}
			}
			PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
			ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->item != nullptr)
				DrawUtils::drawItem(item, Vec2(xVal, yVal), opacity, scale, item->isEnchanted());
		}
	}

	virtual const char* getModuleName() override {
		return "ArmourHud";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string((int)floorf((scale + 0.001f) * 100)) + "%";
	}
};