#include "ESP.h"

#include "../../../Utils/Target.h"
#include "../../Manager/FriendsManager.h"

ESP::ESP() : Module(0x0, Category::RENDER, "Makes it easier to find entities around you") {
	registerBoolSetting("Rainbow", &doRainbow, doRainbow, "Rainbow: Enable or disable rainbow effect.");
	registerBoolSetting("Mob ESP", &isMobEsp, isMobEsp, "Mob ESP: Enable or disable mob ESP.");
	// registerBoolSetting("Item ESP", &item, item, "Item ESP: Enable or disable item ESP.");

	registerEnumSetting("Mode", &mode, 0, "Mode: Select the desired mode");
	mode.addEntry("2D", 0);
	mode.addEntry("3D", 1);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return "ESP";
}

std::string ESP::getModSettings() {
	return mode.GetSelectedEntry().GetName();
}

static float rcolors[4];
std::vector<Vec3i> lastPos;
void ESP::onEnable() {
	lastPos.clear();
}
void doRenderStuff(Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();
	LocalPlayer* localPlayer = Game.getLocalPlayer();

	if (Target::isValidTarget(ent)) {
		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1);
		else
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, 1);
	} else if (espMod->isMobEsp) {

		if (ent->getNameTag()->getTextLength() <= 1 && ent->isPlayer())
			return;

		if (ent->isInvisible() || !localPlayer->canAttack(ent, false))
			return;

		if (ent == Game.getLocalPlayer())
			return;

		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1);
		else
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, 1);
	} else {
		return;
	}

	if (Game.canUseMoveKeys() && Game.isInGame()) {
		if (espMod->mode.selected == 0)
			DrawUtils::drawZephyr(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()) * 3.f)));
		else if (espMod->mode.selected == 1)
			DrawUtils::drawBetterESP(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
		else
			DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
	}
}

void ESP::onPreRender(MinecraftUIRenderContext* renderCtx) {
	if (Game.canUseMoveKeys() && Game.isInGame() && Game.getLocalPlayer() != nullptr) {
		for (auto pos : lastPos) {
			DrawUtils::drawBox(pos.toFloatVector(), pos.add(1, 1, 1).toFloatVector(), 1, false);
		}
		LocalPlayer* localPlayer = Game.getLocalPlayer();

		if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
			// Rainbow colors
			{
				if (rcolors[3] < 1) {
					rcolors[0] = 0.2f;
					rcolors[1] = 0.2f;
					rcolors[2] = 1.f;
					rcolors[3] = 1;
				}

				Utils::ApplyRainbow(rcolors, 0.0015f);
			}

			Game.forEachEntity(doRenderStuff);
		}
	}
}