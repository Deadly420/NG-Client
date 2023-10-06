#include "Watermark.h"

#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ColorUtil.h"
#include "../../Manager/ModuleManager.h"

Watermark::Watermark() : Module(0x0, Category::RENDER, "Show Watermark") {
	registerBoolSetting("ImGui", &ImGui, ImGui, "Renders With ImGui");
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f, "Adjust the watermark opacity");
}

Watermark::~Watermark() {}

const char* Watermark::getModuleName() {
	return "Watermark";
}

void Watermark::onImGuiRender() {
	if (ImGui && Game.isInGame()) {
		std::string watermarkText = "NG Client";

		int index = 1;
		int curIndex = -index * 90;
		auto color = ColorUtil::getRainbowColor(3.0f, 1.0f, 1, curIndex * 2);

		ImVec4 textColor = ImVec4(color.r, color.g, color.b, 1.0f);  // Red color, adjust as needed

		// Draw the watermark text directly
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(0, 0));
		ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowFontScale(2.0);
		// Set the text color and then display the text
		ImGui::TextColored(textColor, "%s", watermarkText.c_str());

		ImGui::End();
	}
}

void Watermark::onPostRender(MinecraftUIRenderContext * renderCtx) {
	if (!ImGui && Game.isInGame()) {
		int index = 1;
		int curIndex = -index * 90;
		auto color = ColorUtil::getRainbowColor(3.0f, 1.0f, 1, curIndex * 2);

		// Get the window size
		Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

		// Calculate text height
		const float textHeight = 1.22f * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();

		// Check if the local player is valid and can use move keys
		if (Game.isInGame() && Game.canUseMoveKeys()) {
			// Get the player's name
			std::string playername = Game.getLocalPlayer()->getNameTag()->getText();

			// Create the watermark text
			std::string watermarkText = "NG Client | " + playername;
			const float nameLength = DrawUtils::getTextWidth(&watermarkText, 0.8f);

			// Define watermark position and size
			const Vec2 watermarkPosition(windowSize.x / windowSize.x + 1.0f, windowSize.y / windowSize.y + 2.0f);
			const Vec4 watermarkBackgroundRect(windowSize.x / windowSize.x, windowSize.y / windowSize.y, nameLength + 4, 12);
			const Vec4 watermarkBarRect(windowSize.x / windowSize.x, windowSize.y / windowSize.y, nameLength + 4, 2);

			// Draw the watermark
			DrawUtils::drawText(watermarkPosition, &watermarkText, Mc_Color(color), 0.8f, true);
			DrawUtils::fillRectangle(watermarkBackgroundRect, Mc_Color(0, 0, 0), opacity);
			DrawUtils::fillRectangle(watermarkBarRect, Mc_Color(color), 1.f);
		}
	}
}