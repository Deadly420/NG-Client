#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../../Manager/ModuleManager.h"

NameTags::NameTags() : Module(0x0, Category::RENDER, "Shows better nametags.") {
	registerBoolSetting("Underline", &underline, underline, "Underline: Enable or disable text underlining");
	registerBoolSetting("Armor", &displayArmor, displayArmor, "Armor: Show or hide armor information");
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f, "Opacity: Adjust the opacity level from 0.0 to 1.0");
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	return ("NameTags");
}

void drawNameTags(Entity* ent, bool) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();

	if (ent != localPlayer) {
		if (!ent->isAlive())
			return;
		if (ent->getNameTag()->getTextLength() < 1)
			return;
		if (Target::isValidTarget(ent) && nameTagsMod != nullptr) {
			nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
			float dist = ent->getPos()->dist(*Game.getLocalPlayer()->getPos());
			NameTags::drawNameTags(ent, fmax(0.6f, 3.f / dist));
			DrawUtils::flush();
		}
	}
}

void NameTags::drawNameTags(Entity* ent, float textSize) {
	Vec2 textPos;
	Vec4 rectPos;
	std::string text = ent->getNameTag()->getText();
	text = Utils::sanitize(text);

	float textWidth = DrawUtils::getTextWidth(&text, textSize);
	float textHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * textSize;

	if (Game.isInGame()) {
		ent->getRenderPositionComponent()->renderPos.add(0, 1.f, 0);
		textPos.y -= textHeight;
		textPos.x -= textWidth / 2.f;
		rectPos.x = textPos.x - 1.f * textSize;
		rectPos.y = textPos.y - 1.f * textSize;
		rectPos.z = textPos.x + textWidth + 1.f * textSize;
		rectPos.w = textPos.y + textHeight + 2.f * textSize;
		Vec4 subRectPos = rectPos;
		subRectPos.y = subRectPos.w - 1.f * textSize;
		static auto nametagsMod = moduleMgr->getModule<NameTags>();
		DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), nametagsMod->opacity);
		if (nametagsMod->underline) {
			DrawUtils::fillRectangle(subRectPos, Mc_Color(0, 246, 255), 0.9f);
		}
		DrawUtils::drawText(textPos, &text, Mc_Color(255, 255, 255), textSize);
	}
}

void NameTags::onPreRender(MinecraftUIRenderContext* renderCtx) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr || !GameData::canUseMoveKeys()) return;

	if (ingameNametagSetting)
		if (!gotPrevSetting) {
			lastSetting = *ingameNametagSetting;
			gotPrevSetting = true;
			*ingameNametagSetting = false;
		} else
			*ingameNametagSetting = false;  //disable other ppl's nametags

	Game.forEachEntity(drawNameTags);
}

void NameTags::onDisable() {
	if (ingameNametagSetting && gotPrevSetting) {
		*ingameNametagSetting = lastSetting;
		gotPrevSetting = false;
	}
}