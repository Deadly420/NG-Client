#include "Watermark.h"

#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ColorUtil.h"
#include "../ModuleManager.h"

Watermark::Watermark() : Module(0x0, Category::RENDER, "Show Watermark") {
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f, "Adjust the watermark opacity");
}

Watermark::~Watermark() {
}

const char* Watermark::getModuleName() {
	return "Watermark";
}

void Watermark::onPostRender(MinecraftUIRenderContext* renderCtx) {
	int index = 1;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.0f, 1.0f, 1, curIndex * 2);

	// Get the window size
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

	// Calculate text height
	const float textHeight = 1.22f * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();

	// Check if the local player is valid and can use move keys
	if (auto player = Game.getLocalPlayer(); player != nullptr && Game.isInGame() || Game.canUseMoveKeys) {
		// Get the player's name
		std::string playername = player->getNameTag()->getText();

		// Create the watermark text
		std::string watermarkText = "NG Client | " + playername;
		const float nameLength = DrawUtils::getTextWidth(&watermarkText, 0.8f);

		// Define watermark position and size
		const Vec2 watermarkPosition(windowSize.x / windowSize.x + 1.0f, windowSize.y / windowSize.y + 2.0f);
		const Vec4 watermarkBackgroundRect(windowSize.x / windowSize.x, windowSize.y / windowSize.y, nameLength + 4, 12);
		const Vec4 watermarkBarRect(windowSize.x / windowSize.x, windowSize.y / windowSize.y, nameLength + 4, 2);

		// Draw the watermark
		DrawUtils::drawTextShadow(watermarkPosition, &watermarkText, Mc_Color(color), 0.8f, true);
		DrawUtils::fillRectangle(watermarkBackgroundRect, Mc_Color(0, 0, 0), opacity);
		DrawUtils::fillRectangle(watermarkBarRect, Mc_Color(color), 1.f);
	}
}