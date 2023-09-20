#include "NightMode.h"

NightMode::NightMode() : Module(0x0, Category::RENDER, "Darkens the environment.") {
	// registerFloatSetting("Modifier", &modifier, modifier, 0.1f, 1.0f, "Modifier: Adjust the modifier from 0.1 to 1.0");
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