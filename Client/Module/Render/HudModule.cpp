#include "HudModule.h"
#include "../ModuleManager.h"

#include "../../../Utils/DrawUtils.h"

HudModule::HudModule() : Module(0x0, Category::RENDER, "Displays things like the ArrayList/TabGUI.") {
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerBoolSetting("Coordinates", &coordinates, coordinates);
	registerBoolSetting("Show Keybinds", &keybinds, keybinds);
	registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor);
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("Show FPS", &fps, fps);
	registerBoolSetting("Show CPS", &cps, cps);
	registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("HUD");
}

void HudModule::onPostRender(MinecraftUIRenderContext* renderCtx) {
	Vector2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = 0.f;
	
	{  // FPS
		if (!(Game.getLocalPlayer() == nullptr || !fps)) {
			std::string fpsText = "FPS: " + std::to_string(Game.getFPS());
			Vector4 rectPos = Vector4(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			Vector2 textPos = Vector2(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::drawText(textPos, &fpsText, Mc_Color(200, 200, 200), scale);

			startY += f;
		}
	}
	
	{  // CPS
		if (!(Game.getLocalPlayer() == nullptr || !cps)) {
			std::string cpsText = "CPS: " + std::to_string(Game.getLeftCPS()) + " - " + std::to_string(Game.getRightCPS());
			Vector4 rectPos = Vector4(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			Vector2 textPos = Vector2(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::drawText(textPos, &cpsText, Mc_Color(200, 200, 200), scale);

			startY += f;
		}
	}
	
	{  // Coordinates
		if (!(Game.getLocalPlayer() == nullptr || !coordinates)) {
			Vector3* pos = Game.getLocalPlayer()->getPos();
			std::string coords = std::string("X: ") + std::to_string((int)floorf(pos->x)) + std::string("\nY: ") + std::to_string((int)floorf(pos->y)) + std::string("\nZ: ") + std::to_string((int)floorf(pos->z));
			
			Vector4 rectPos = Vector4(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			Vector2 textPos = Vector2(rectPos.x + 1.5f, rectPos.y + 1.f);
			
			DrawUtils::drawText(textPos, &coords, Mc_Color(200, 200, 200), scale);
		}
	}
	
	{  // ArmorHUD
		
		if (!(Game.getLocalPlayer() == nullptr || !displayArmor || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.25f;
			static float constexpr spacing = scale + 15.f;
			LocalPlayer* player = Game.getLocalPlayer();
			float x = windowSize.x / 2.f + 5.f;
			float y = windowSize.y - 57.5f;
			for (int i = 0; i < 4; i++) {
				ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, Vector2(x, y), opacity, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
			ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->isValid())
				DrawUtils::drawItem(item, Vector2(x, y), opacity, scale, item->isEnchanted());
		}
	}
}