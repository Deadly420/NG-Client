#include "ClickGuiMod.h"
#include "../../Menu/ClickGui.h"

ClickGuiMod::ClickGuiMod() : Module(VK_TAB, Category::HUD, "The clickgui - toggle everything just by clicking on it!") {
	registerEnumSetting("Mode", &mode, 0, "Mode: Select the mode (New or Old).");
	mode.addEntry("New", 0);
	mode.addEntry("Old", 1);

	registerBoolSetting("Reset On Inject", &resetOnInject, resetOnInject, "Reset On Inject: Enable or disable resetting on injection");
	registerBoolSetting("Reset On Open", &resetOnOpen, resetOnOpen, "Reset On Open: Enable or disable resetting on opening");
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips, "Show's This");
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	return ("ClickGui");
}

void ClickGuiMod::onEnable() {
	static auto imgui = moduleMgr->getModule<NewUI>();
	imgui->setEnabled(false);
	Game.getClientInstance()->releaseMouse();
	if (resetOnOpen) {
		resetStartPos = true;
	}
}

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	Game.getClientInstance()->grabMouse();
	Opacity = 0;
}

void ClickGuiMod::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys())
		Game.getClientInstance()->releaseMouse();
}
void ClickGuiMod::onLoadConfig(void* conf) {
	Module::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
}
void ClickGuiMod::onSaveConfig(void* conf) {
	Module::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
}
