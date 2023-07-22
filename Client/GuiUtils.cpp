#include "GuiUtils.h"

void GuiUtils::drawCrossLine(Vector2 pos, Mc_Color col, float lineWidth, float crossSize, bool secondCross) {
	crossSize /= 2;
	DrawUtils::setColor(col.r, col.g, col.b, col.a);
	//float MidX = (pos.z + pos.x) / 2;
	//float MidY = (pos.y + pos.w) / 2;
	DrawUtils::drawLine(Vector2(pos.x - crossSize, pos.y), Vector2(pos.x + crossSize, pos.y), lineWidth);
	if (secondCross)
		DrawUtils::drawLine(Vector2(pos.x, pos.y - crossSize), Vector2(pos.x, pos.y + crossSize), lineWidth);
}

void GuiUtils::drawUpArrow(Vector2 pos, Mc_Color col, float lineWidth, float arrowSize) {
	// Calculate the height of the arrow
	float arrowHeight = arrowSize * 2;

	// Set the color for the arrow
	DrawUtils::setColor(col.r, col.g, col.b, col.a);

	// Calculate the arrow points
	Vector2 p1(pos.x, pos.y - arrowHeight);
	Vector2 p2(pos.x - arrowSize, pos.y);
	Vector2 p3(pos.x + arrowSize, pos.y);

	// Draw the arrow lines
	DrawUtils::drawLine(p1, p2, lineWidth);
	DrawUtils::drawLine(p1, p3, lineWidth);

	DrawUtils::drawLine(p2, p3, lineWidth);
}

void GuiUtils::drawDownArrow(Vector2 pos, Mc_Color col, float lineWidth, float arrowSize) {
    // Calculate the height of the arrow
    float arrowHeight = arrowSize * 2;

    // Set the color for the arrow
    DrawUtils::setColor(col.r, col.g, col.b, col.a);

    // Calculate the arrow points
    Vector2 p1(pos.x, pos.y + arrowHeight);
    Vector2 p2(pos.x - arrowSize, pos.y);
    Vector2 p3(pos.x + arrowSize, pos.y);

    // Draw the arrow lines
    DrawUtils::drawLine(p1, p2, lineWidth);
    DrawUtils::drawLine(p1, p3, lineWidth);

    DrawUtils::drawLine(p2, p3, lineWidth);
}