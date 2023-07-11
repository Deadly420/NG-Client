#include "NightMode.h"

NightMode::NightMode() : Module(0, Category::RENDER, "Darkens the environment.") {
	//registerFloatSetting("modifier", &modifier, modifier, 0.1f, 1.f);
}

NightMode::~NightMode() {
}

const char* NightMode::getModuleName() {
	return "NightMode";
}

void NightMode::onEnable() {
	static auto rainbowSkyMod = moduleMgr->getModule<RainbowSky>();
	if (rainbowSkyMod->isEnabled())
		rainbowSkyMod->setEnabled(false);
}