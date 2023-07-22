#pragma once
#include "../Utils/DrawUtils.h"

class GuiUtils {
public:
	static void drawCrossLine(Vector2 pos, Mc_Color col, float lineWidth, float crossSize, bool secondCross);
	static void GuiUtils::drawUpArrow(Vector2 pos, Mc_Color col, float lineWidth, float arrowSize);
	static void GuiUtils::drawDownArrow(Vector2 pos, Mc_Color col, float lineWidth, float arrowSize);
};
