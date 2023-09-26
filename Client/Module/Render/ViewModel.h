#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class ViewModel : public Module {
public:
	int delay = 0;
	bool test = true;
	bool Reset = false;
	bool doTranslate = true;
	bool doScale = true;
	SettingEnum mode = this;

	float xMod = 1.f;
	float yMod = 1.f;
	float zMod = 1.f;

	float xTrans = 0.f;
	float yTrans = 0.f;
	float zTrans = 0.f;

	float xRotate = 0.01f;
	float yRotate = 0.01f;
	float zRotate = 0.01f;
	float RotatePosition = 0.f;

	bool shouldBlock = false;
	bool isAttacking = false;
	bool SlowSwing = false;
	int SwingSpeed = 20;

	ViewModel() : Module(0x0, Category::RENDER, "Custom item view model") {
		registerBoolSetting("Slow Swing", &SlowSwing, SlowSwing, "Slow Swing: Enable slow swinging");
		registerIntSetting("Swing Speed", &SwingSpeed, SwingSpeed, 0, 50, "Swing Speed: Adjust the swing speed from 0 to 50");

		registerEnumSetting("Mode", &mode, 1, "Mode: Select the desired mode");
		mode.addEntry("None", 0);
		mode.addEntry("1.7", 1);
		mode.addEntry("Spin", 2);

		registerBoolSetting("Reset", &Reset, Reset, "Reset: Reset the setting to its default value");
		registerBoolSetting("Translate", &doTranslate, doTranslate, "Translate: Enable translation");
		registerBoolSetting("Scale", &doScale, doScale, "Scale: Enable scaling");

		registerFloatSetting("TranslateX", &xTrans, 0.f, -2.f, 2.f, "TranslateX: Translate along the X-axis from -2.0 to 2.0");
		registerFloatSetting("TranslateY", &yTrans, 0.f, -2.f, 2.f, "Translate along the Y-axis");
		registerFloatSetting("TranslateZ", &zTrans, 0.f, -2.f, 2.f, "Translate along the Z-axis");

		registerFloatSetting("ScaleX", &xMod, 1.f, -2.f, 2.f, "Scale along the X-axis");
		registerFloatSetting("ScaleY", &yMod, 1.f, -2.f, 2.f, "Scale along the Y-axis");
		registerFloatSetting("ScaleZ", &zMod, 1.f, -2.f, 2.f, "Scale along the Z-axis");

		registerFloatSetting("RotateX", &xRotate, 1.f, -2.f, 2.f, "Rotate around the X-axis");
		registerFloatSetting("RotateY", &yRotate, 1.f, -2.f, 2.f, "Rotate around the Y-axis");
		registerFloatSetting("RotateZ", &zRotate, 1.f, -2.f, 2.f, "Rotate around the Z-axis");
		registerFloatSetting("RotatePos", &RotatePosition, 1.f, 0.01f, 6.4f, "Rotate position");

	};
	~ViewModel(){};

	void onTick(GameMode* gm) {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;

		auto slot = player->getSupplies()->inventory->getItemStack(player->getSupplies()->selectedHotbarSlot);
		shouldBlock = slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && Game.isRightClickDown() || slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon();
		isAttacking = Game.isLeftClickDown();

		if (Reset) {
			xTrans = 0.f;
			yTrans = 0.f;
			zTrans = 0.f;

			xMod = 1.f;
			yMod = 1.f;
			zMod = 1.f;

			xRotate = 0.01f;
			yRotate = 0.01f;
			zRotate = 0.01f;
			RotatePosition = 0.f;

			Reset = false;
		}
	}

	virtual const char* getModuleName() override {
		return "ViewModel";
	}

	std::string getModSettings() {
		return mode.GetSelectedEntry().GetName();
	}
};