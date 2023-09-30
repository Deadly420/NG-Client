#include "Tracer.h"

#include "../../../SDK/Camera.h"
#include "../../../Utils/DrawUtils.h"
#include "../../Manager/ModuleManager.h"

Tracer::Tracer() : Module(0x0, Category::RENDER, "Draws lines to ESP highlighted entities") {
	registerEnumSetting("Type", &type, 0, "Chamges the tpye form bottom to top");
	type.addEntry("Normal", 0);
	type.addEntry("Top", 1);
	type.addEntry("Bottom", 2);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";
}
std::string Tracer::getModSettings() {
	return type.GetSelectedEntry().GetName();
}

std::shared_ptr<glmatrixf> refdef2;
void Tracer::onPreRender(MinecraftUIRenderContext* renderCtx) {
	glmatrixf* badrefdef = Game.getClientInstance()->getRefDef();
	refdef2 = std::shared_ptr<glmatrixf>(badrefdef->correct());

	Game.forEachEntity([&](Entity* ent, bool valid) {
		if (ent != Game.getLocalPlayer() && Target::isValidTarget(ent) && Game.canUseMoveKeys() && Game.isInGame()) {
			Vec2 target;
			Vec2 screenSize{
				Game.getGuiData()->widthGame,
				Game.getGuiData()->heightGame};
			refdef2->OWorldToScreen(Game.getClientInstance()->levelRenderer->getOrigin(), ent->getRenderPositionComponent()->renderPos, target, Game.getClientInstance()->getFov(), screenSize);
			Vec2 Top{Game.getClientInstance()->getGuiData()->widthGame / 2, Game.getClientInstance()->getGuiData()->heightGame / Game.getClientInstance()->getGuiData()->heightGame};
			Vec2 mid{Game.getClientInstance()->getGuiData()->widthGame / 2, Game.getClientInstance()->getGuiData()->heightGame / 2};
			Vec2 Bottom{Game.getClientInstance()->getGuiData()->widthGame / 2, Game.getClientInstance()->getGuiData()->heightGame};
			if (target != Vec2(0, 0)) {
				DrawUtils::setColor(255, 255, 255, 1);
				if (type.selected == 0) {
					DrawUtils::drawLine(mid, target, 0.2f);
				} else if (type.selected == 1) {
					DrawUtils::drawLine(Top, target, 0.2f);
				} else {
					DrawUtils::drawLine(Bottom, target, 0.2f);
				}
			}
		}
	});
}