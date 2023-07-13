#pragma once
#include "../../../Client/Module/Module.h"
#include "../ModuleManager.h"
class ViewModel : public Module {
public:
	int delay = 0;
	bool test = true;
	bool Reset = false;
	bool doTranslate = true;
	bool doScale = true;
	bool doRotation = true;
	bool spin = true;
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

	ViewModel() : Module(0x0, Category::RENDER, "Custom item view model") {
		registerBoolSetting("Reset", &Reset, Reset);
		registerBoolSetting("Translate", &doTranslate, doTranslate);
		registerBoolSetting("Scale", &doScale, doScale);
		registerBoolSetting("Rotate", &doRotation, doRotation);
		registerBoolSetting("Spin", &spin, spin);
		mode.addEntry("Around Body", 1);
		mode.addEntry("Circle", 2);
		mode.addEntry("Vertical", 3);
		registerEnumSetting("Spin Mode", &mode, 0);

		registerFloatSetting("TranslateX", &xTrans, 0.f, -2.f, 2.f);
		registerFloatSetting("TranslateY", &yTrans, 0.f, -2.f, 2.f);
		registerFloatSetting("TranslateZ", &zTrans, 0.f, -2.f, 2.f);

		registerFloatSetting("ScaleX", &xMod, 1.f, -2.f, 2.f);
		registerFloatSetting("ScaleY", &yMod, 1.f, -2.f, 2.f);
		registerFloatSetting("ScaleZ", &zMod, 1.f, -2.f, 2.f);

		registerFloatSetting("RotateX", &xRotate, 1.f, -2.f, 2.f);
		registerFloatSetting("RotateY", &yRotate, 1.f, -2.f, 2.f);
		registerFloatSetting("RotateZ", &zRotate, 1.f, -2.f, 2.f);
		registerFloatSetting("RotatePos", &RotatePosition, 1.f, 0.01f, 6.4f);
	};
	~ViewModel(){};

	void onTick(GameMode* gm) {
		if (Game.getLocalPlayer() == nullptr)
			return;

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
			spin = false;
		}
	}

	virtual const char* getModuleName() override {
		return "ViewModel";
	}
};