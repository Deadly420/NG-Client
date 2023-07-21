#pragma once
#include "../Utils/DrawUtils.h"

class GuiUtils {
public:
	static void drawCrossLine(Vec2 pos, Mc_Color col, float lineWidth, float crossSize, bool secondCross);
	static void GuiUtils::drawUpArrow(Vec2 pos, Mc_Color col, float lineWidth, float arrowSize);
	static void GuiUtils::drawDownArrow(Vec2 pos, Mc_Color col, float lineWidth, float arrowSize);
};
