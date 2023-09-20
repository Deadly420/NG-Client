#include "Radar.h"
#include "../../../Utils/ColorUtil.h"
#include <array>

float rcolors[4];
int size = 100;
float pixelSize = 2.5f;
float cent = size / 2.f;
float pxSize = pixelSize / 2.f;
float topPad = -1;
float zoom = 1;
float pxOpacity = 1;
bool grid = true;
// didn't bother puting this onto the header file and making it non-static...
// it's the only one that could be. since everything else is accessed at renderEntity()
float bgOpacity = 0.2f;

Radar::Radar() : Module(0x0, Category::RENDER, "Radar") {
	registerBoolSetting("Show Grid", &grid, grid, "Toggle to show/hide the grid");
	registerIntSetting("Size", &size, size, 50, 200, "Adjust the size of the grid (50 to 200)");
	registerFloatSetting("Pixel Size", &pixelSize, pixelSize, 2, 4, "Pixel Size: Adjust pixel size from 2 to 4");
	registerFloatSetting("Zoom", &zoom, zoom, 1.0f / 4.0f, 4.0f, "Zoom: Set zoom level from 0.25x to 4x");
	registerFloatSetting("Background Opacity", &bgOpacity, bgOpacity, 0.1f, 1.0f, "Background Opacity: Modify background opacity from 0.1 to 1.0");
	registerFloatSetting("Pixel Opacity", &pxOpacity, pxOpacity, 0.1f, 1.0f, "Pixel Opacity: Adjust pixel opacity from 0.1 to 1.0");
}

const char* Radar::getModuleName() {
	return "Radar";
}

float effectiveZoom = 1;
float angle = 0;
float c, s;
Vec3 playerPos;

void recalculateScale() {
	effectiveZoom = zoom * (size / 100.f);
	cent = size / 2.f;
	pxSize = pixelSize / 2.f * effectiveZoom;
	topPad = Game.getGuiData()->heightGame / 2.f;
	
}

void renderEntity(Entity* currentEntity, bool isRegularEntity) {
	LocalPlayer* player = Game.getLocalPlayer();
	if (currentEntity == nullptr)
		return;

	if (currentEntity == player)  // Skip Local player
		return;

	if (!player->canAttack(currentEntity, false))
		return;

	if (!currentEntity->isAlive())
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	Vec3* start = currentEntity->getPosOld();
	Vec3* end = currentEntity->getPos();

	Vec3 lerped = start->lerp(end, DrawUtils::getLerpTime());
	
	const auto delta = lerped.sub(playerPos);
	const float dist = delta.magnitudexz();
	
	const Vec2 relPos = Vec2(
		cent - ((delta.x * c) - (delta.z * s)),
		topPad - ((delta.x * s) + (delta.z * c))
	);
	if (relPos.x > 0 && relPos.x < size && relPos.y > topPad - cent && relPos.y < topPad + cent) {
		DrawUtils::fillRectangle(Vec4(relPos.x - pxSize, relPos.y - pxSize, relPos.x + pxSize, relPos.y + pxSize), Mc_Color(rcolors[0], rcolors[1], rcolors[2]), pxOpacity);
	}
}

void Radar::onPreRender(MinecraftUIRenderContext* renderCtx) {
	if (Game.isInGame() && Game.canUseMoveKeys()) {
		LocalPlayer* player = Game.getLocalPlayer();

		if (player == nullptr) return;

		int index = 0;
		index++;
		int curIndex = -index * 90;
		auto color = ColorUtil::getRainbowColor(3.f, 1.f, 1, curIndex * 2);
		recalculateScale();

		DrawUtils::fillRectangle(Vec4(0, topPad - cent, (float)size, topPad + cent), Mc_Color(1, 1, 1), bgOpacity);

		auto pPos = Game.getClientInstance()->levelRenderer->getOrigin();
		playerPos = pPos;

		angle = (180.0f - player->getActorHeadRotationComponent()->rot.y) + 180.0f;
		if (angle < 0) angle += 360;
		angle *= RAD_DEG;

		s = sin(angle) * effectiveZoom;
		c = cos(angle) * effectiveZoom;

		auto computePos = [=](Vec2 pos) {
			auto delta = pos.sub(pPos.x, pPos.z);
			return Vec2(
				cent - ((delta.x * c) - (delta.y * s)),
				topPad - ((delta.x * s) + (delta.y * c)));
		};

		int chunkX = int(floor(pPos.x)) & ~(15);
		int chunkZ = int(floor(pPos.z)) & ~(15);
		// Draw grid
		DrawUtils::drawRectangle(Vec4(2, topPad - cent, (float)size, topPad + cent), Mc_Color(color), bgOpacity);
		if (grid) {
			// we start at the player pos, and clip the grid lines to the view rectangle until the lines are no longer inside, then we repeat the process in the opposite direction, then we do the same for the other axis

			struct FiniteLine {
				Vec2 a, b;

				// copied straight from wikipedia line-line intersections
				bool intersectionPointWithInfOther(Vec2 oa, Vec2 ob, Vec2& out) {
					float den = (a.x - b.x) * (oa.y - ob.y) - (a.y - b.y) * (oa.x - ob.x);
					if (den == 0)  // lines are parallel
						return false;

					float t = ((a.x - oa.x) * (oa.y - ob.y) - (a.y - oa.y) * (oa.x - ob.x)) / den;
					if (t >= 0 && t <= 1) {
						out = {a.x + t * (b.x - a.x),
							   a.y + t * (b.y - a.y)};
						return true;
					}
					return false;
				}
			};

			std::array<Vec2, 4> clipRectPoints = {Vec2{0.f, topPad - cent}, Vec2{(float)size, topPad - cent}, Vec2{(float)size, topPad + cent}, Vec2{0.f, topPad + cent}};
			std::array<FiniteLine, 4> clipRectLines;
			auto last = clipRectPoints[3];

			for (int i = 0; i < 4; i++) {
				auto cur = clipRectPoints[i];

				clipRectLines[i] = {last, cur};
				last = cur;
			}

			std::vector<FiniteLine> lines;

			auto computeRectIntersections = [&](Vec2 p1, Vec2 p2) {
				Vec2 a, b;
				bool hadIntersection = false;
				for (int i = 0; i < (hadIntersection ? 4 : 3); i++) {
					auto& line = clipRectLines[i];
					bool didIntersect = line.intersectionPointWithInfOther(p1, p2, hadIntersection ? b : a);
					if (didIntersect) {
						if (hadIntersection) {
							lines.push_back({a, b});
							return true;
						}
						hadIntersection = true;
					}
				}
				return false;
			};

			// x axis
			for (int gridX = chunkX; true; gridX += 16) {
				Vec2 p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
				if (!computeRectIntersections(p1, p2))
					break;
			}
			for (int gridX = chunkX - 16; true; gridX -= 16) {
				Vec2 p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
				if (!computeRectIntersections(p1, p2))
					break;
			}

			// z axis
			for (int gridZ = chunkZ; true; gridZ += 16) {
				Vec2 p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
				if (!computeRectIntersections(p1, p2))
					break;
			}
			for (int gridZ = chunkZ - 16; true; gridZ -= 16) {
				Vec2 p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
				if (!computeRectIntersections(p1, p2))
					break;
			}

			DrawUtils::setColor(0.7f, 0.7f, 0.7f, 0.1f);
			// draw all lines
			for (auto line : lines) {
				DrawUtils::drawLine(line.a, line.b, 0.25f);
			}
		}

		// Draw the chunk the player is in
		if (grid) {
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, 0.6f);
			std::array<Vec2, 4> rect = {computePos({chunkX, chunkZ}), computePos({chunkX + 16, chunkZ}), computePos({chunkX + 16, chunkZ + 16}), computePos({chunkX, chunkZ + 16})};
			auto last = rect[3];

			for (int i = 0; i < 4; i++) {
				auto cur = rect[i];

				DrawUtils::drawLine(last, cur, 0.25f);
				last = cur;
			}
		}

		Game.forEachEntity(renderEntity);

		const float pxSize = pixelSize * 0.75f * effectiveZoom;
		DrawUtils::setColor(1, 1, 1, pxOpacity);
		Vec2 center(cent, topPad);
		DrawUtils::drawTriangle(center.add(-pxSize * 0.9f, pxSize * 2.f), center.add(pxSize * 0.9f, pxSize * 2.f), center);
	}
}
