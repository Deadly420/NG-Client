#include "KeyStrokes.h"

#include "../../../Utils/Logging.h"
#include "../../../Utils/ColorUtil.h"
#include "../../../Utils/DrawUtils.h"
#include "../../Manager/ModuleManager.h"

KeyStrokes::KeyStrokes() : Module(0x0, Category::RENDER, "Renders Keystrokes on your screen") {
	registerBoolSetting("Keystrokes RGB", &keybindsRGB, keybindsRGB, "Keystrokes RGB: Enable or disable RGB coloring for keystrokes");
	registerBoolSetting("Flip Keystrokes", &flip, flip, "Flip Keystrokes: Enable or disable flipping of keystrokes");
	registerFloatSetting("keystrokesX", &keystrokesX, keystrokesX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x, "keystrokesX: Set the horizontal position from 0 to the window width");
	registerFloatSetting("keystrokesY", &keystrokesY, keystrokesY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y, "keystrokesY: Set the vertical position from 0 to the window height");
	registerFloatSetting("Opacity", &opacity, opacity, 0.0f, 1.f, "Opacity: Adjust the opacity from 0.0 to 1.0");
}

KeyStrokes::~KeyStrokes() {
}

const char* KeyStrokes::getModuleName() {
	return ("Keystrokes");
}

void KeyStrokes::onPreRender(MinecraftUIRenderContext* renderCtx) {
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
		if (flip) {
			KeyStrokes::CPS(Vec2(4.f, windowSize.y - 90));
			KeyStrokes::drawRightMouseKeystroke(Vec2(37.f, windowSize.y - 77));
			KeyStrokes::drawLeftMouseKeystroke(Vec2(4.f, windowSize.y - 77));
			KeyStrokes::drawKeystroke(*input->spaceBarKey, Vec2(4.f, windowSize.y - 55));
			KeyStrokes::drawKeystroke(*input->rightKey, Vec2(48.f, windowSize.y - 37));
			KeyStrokes::drawKeystroke(*input->backKey, Vec2(26.f, windowSize.y - 37));
			KeyStrokes::drawKeystroke(*input->leftKey, Vec2(4.f, windowSize.y - 37));
			KeyStrokes::drawKeystroke(*input->forwardKey, Vec2(26.f, windowSize.y - 15));
		} else {
			KeyStrokes::drawKeystroke(*input->forwardKey, Vec2(26.f, windowSize.y - 94));
			KeyStrokes::drawKeystroke(*input->leftKey, Vec2(4.f, windowSize.y - 72));
			KeyStrokes::drawKeystroke(*input->backKey, Vec2(26.f, windowSize.y - 72));
			KeyStrokes::drawKeystroke(*input->rightKey, Vec2(48.f, windowSize.y - 72));
			KeyStrokes::drawKeystroke(*input->spaceBarKey, Vec2(4.f, windowSize.y - 50));
			KeyStrokes::drawLeftMouseKeystroke(Vec2(4.f, windowSize.y - 37));
			KeyStrokes::drawRightMouseKeystroke(Vec2(37.f, windowSize.y - 37));
			KeyStrokes::CPS(Vec2(4.f, windowSize.y - 15));
		}
	}
}

void KeyStrokes::drawKeystroke(char key, Vec2 pos) {
	// rainbow colors
	int index = 0;
	index++;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.f, 1.f, 1, curIndex * 2);

	static auto Key = moduleMgr->getModule<KeyStrokes>();
	std::string keyString = Utils::getKeybindName(key);
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	if (key == *input->spaceBarKey) {
		if (key == *input->spaceBarKey) keyString = "-";
		pos.x += Key->keystrokesX;
		pos.y -= Key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		Vec4 rectPos(
			pos.x,
			pos.y,
			pos.x + 64.f,
			pos.y + 15.f);
		Vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
			rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? Mc_Color(85, 85, 85) : Mc_Color(12, 12, 12), Key->opacity);
		if (Key->keybindsRGB) {
			DrawUtils::drawRectangle(rectPos, GameData::isKeyDown(key) ? Mc_Color() : Mc_Color(color), 1.f);
			DrawUtils::drawText(textPos, &keyString, Mc_Color(color), 1.f, 1.f);
		} else
			DrawUtils::drawText(textPos, &keyString, Mc_Color(0, 246, 255), 1.f, 1.f);
	} else {
		pos.x += Key->keystrokesX;
		pos.y -= Key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		Vec4 rectPos(
			pos.x,
			pos.y,
			pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f),
			pos.y + ((key == *input->spaceBarKey) ? 15.f : 20.f));
		Vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
			rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? Mc_Color(85, 85, 85) : Mc_Color(12, 12, 12), Key->opacity);
		if (Key->keybindsRGB) {
			DrawUtils::drawRectangle(rectPos, GameData::isKeyDown(key) ? Mc_Color() : Mc_Color(color), 1.f);
			DrawUtils::drawText(textPos, &keyString, Mc_Color(color), 1.f, 1.f);
		} else
			DrawUtils::drawText(textPos, &keyString, Mc_Color(0, 246, 255), 1.f, 1.f);
	}
}

void KeyStrokes::drawLeftMouseKeystroke(Vec2 pos) {
	// rainbow colors
	int index = 0;
	index++;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.f, 1.f, 1, curIndex * 2);

	static auto key = moduleMgr->getModule<KeyStrokes>();
	std::string keyString;
	keyString = "LMB";
	pos.x += key->keystrokesX;
	pos.y -= key->keystrokesY;
	pos.x -= 9.f;
	pos.y += 9.f;
	Vec4 rectPos(
		pos.x,
		pos.y + 4,
		pos.x + 31.f,
		pos.y + 20.f);
	DrawUtils::fillRectangle(rectPos, GameData::GameData::isLeftClickDown() ? Mc_Color(85, 85, 85) : Mc_Color(12, 12, 12), key->opacity);
	Vec2 textPos(
		(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
		rectPos.y + 8.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	if (key->keybindsRGB) {
		DrawUtils::drawRectangle(rectPos, GameData::GameData::isLeftClickDown() ? Mc_Color() : Mc_Color(color), 1.f);
		DrawUtils::drawText(textPos, &keyString, Mc_Color(color), 1.f, 1.f);
	} else
		DrawUtils::drawText(textPos, &keyString, Mc_Color(0, 246, 255), 1.f, 1.f);
}

void KeyStrokes::drawRightMouseKeystroke(Vec2 pos) {
	// rainbow colors
	int index = 0;
	index++;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.f, 1.f, 1, curIndex * 2);

	static auto key = moduleMgr->getModule<KeyStrokes>();
	std::string keyString;
	keyString = "RMB";
	pos.x += key->keystrokesX;
	pos.y -= key->keystrokesY;
	pos.x -= 9.f;
	pos.y += 9.f;
	Vec4 rectPos(
		pos.x,
		pos.y + 4,
		pos.x + 31.f,
		pos.y + 20.f);
	DrawUtils::fillRectangle(rectPos, GameData::GameData::isRightClickDown() ? Mc_Color(85, 85, 85) : Mc_Color(12, 12, 12), key->opacity);
	Vec2 textPos(
		(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
		rectPos.y + 8.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	if (key->keybindsRGB) {
		DrawUtils::drawRectangle(rectPos, GameData::GameData::isRightClickDown() ? Mc_Color() : Mc_Color(color), 1.f);
		DrawUtils::drawText(textPos, &keyString, Mc_Color(color), 1.f, 1.f);
	} else
		DrawUtils::drawText(textPos, &keyString, Mc_Color(0, 246, 255), 1.f, 1.f);
}

void KeyStrokes::CPS(Vec2 pos) {
	// rainbow colors
	int index = 0;
	index++;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(3.f, 1.f, 1, curIndex * 2);

	static auto key = moduleMgr->getModule<KeyStrokes>();
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	{
		std::string cpsText = "CPS: " + std::to_string(Game.getLeftCPS()) + " - " + std::to_string(Game.getRightCPS());
		pos.x += key->keystrokesX;
		pos.y -= key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		Vec4 rectPos(
			// box
			pos.x,
			pos.y,
			pos.x + 64.f,
			pos.y + 15.f);
		Vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&cpsText) / 2.f),
			rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, Game.getLeftCPS() || Game.getRightCPS() ? Mc_Color(12, 12, 12) : Mc_Color(12, 12, 12), key->opacity);
		if (key->keybindsRGB) {
			DrawUtils::drawRectangle(rectPos, Game.getLeftCPS() || Game.getRightCPS() ? Mc_Color(color) : Mc_Color(color), 1.f);
			DrawUtils::drawText(textPos, &cpsText, Mc_Color(color), 1.f, 1.f);
		} else
			DrawUtils::drawText(textPos, &cpsText, Mc_Color(0, 246, 255), 1.f, 1.f);
	}
}