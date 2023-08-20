#include "GuiUtils.h"

void GuiUtils::drawCrossLine(Vec2 pos, Mc_Color col, float lineWidth, float crossSize, bool secondCross) {
    crossSize /= 2;
    DrawUtils::setColor(col.r, col.g, col.b, col.a);
    
    Vec2 horizontalStart(pos.x - crossSize, pos.y);
    Vec2 horizontalEnd(pos.x + crossSize, pos.y);
    Vec2 verticalStart(pos.x, pos.y - crossSize);
    Vec2 verticalEnd(pos.x, pos.y + crossSize);
    
    DrawUtils::drawLine(horizontalStart, horizontalEnd, lineWidth);
    
    if (secondCross) {
        DrawUtils::drawLine(verticalStart, verticalEnd, lineWidth);
    }
}

void GuiUtils::drawArrow(Vec2 pos, Mc_Color col, float lineWidth, float arrowSize, bool isUpArrow) {
	// Calculate the height of the arrow
	float arrowHeight = arrowSize * 2;

	// Set the color for the arrow
	DrawUtils::setColor(col.r, col.g, col.b, col.a);

	// Calculate the arrow points
	Vec2 p1 = isUpArrow ? Vec2(pos.x, pos.y - arrowHeight) : Vec2(pos.x, pos.y + arrowHeight);
	Vec2 p2(pos.x - arrowSize, pos.y);
	Vec2 p3(pos.x + arrowSize, pos.y);

	// Draw the arrow triangle
	if (isUpArrow) {
		DrawUtils::drawTriangle(p1, p2, p3);
	} else {
		DrawUtils::drawTriangle(p1, p3, p2);
	}
}

// For up arrow:
// drawArrow(position, color, line_width, arrow_size, true);
// For down arrow:
// drawArrow(position, color, line_width, arrow_size, false);
