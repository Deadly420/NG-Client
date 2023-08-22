#include "Watermark.h"

#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ColorUtil.h"
#include "../ModuleManager.h"

Watermark::Watermark() : Module(0x0, Category::RENDER, "Show Watermark") {
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

Watermark::~Watermark() {
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}

void Watermark::onPostRender(MinecraftUIRenderContext* renderCtx) {
	int index = 1;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.0f, 1.0f, 1, curIndex * 2);

	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	//
	static const float textHeight = (1.22f) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
	//
	if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		auto player = Game.getLocalPlayer();
		std::string playername = player->getNameTag()->getText();

		std::string name = "NG Client | " + playername;
		float nameLength = DrawUtils::getTextWidth(&name, 0.8f);

		if (rgb) {
			DrawUtils::drawTextShadow(Vec2(windowSize.x / windowSize.x + 1.0f, windowSize.y / windowSize.y + 2.0f), &name, Mc_Color(color), 0.8f, true);

			DrawUtils::fillRectangle(Vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, + nameLength + 4, 12), Mc_Color(0, 0, 0), opacity);
			DrawUtils::fillRectangle(Vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, + nameLength + 4, 2), Mc_Color(color), 1.f);
		} else {
			DrawUtils::drawText(Vec2(windowSize.x / windowSize.x + 1.0f, windowSize.y / windowSize.y + 2.0f), &name, Mc_Color(color), 0.8f);
			DrawUtils::drawText(Vec2(windowSize.x / windowSize.x + 1.0f, windowSize.y / windowSize.y + 1.5f), &name, Mc_Color(255, 255, 255), 0.8f);

			DrawUtils::fillRectangle(Vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, + nameLength + 4, 12), Mc_Color(0, 0, 0), opacity);
			DrawUtils::fillRectangle(Vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, + nameLength + 4, 2), Mc_Color(color), 1.f);
		}
	}
}
