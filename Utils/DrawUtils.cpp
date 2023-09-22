#include "DrawUtils.h"

#include "../Client/Module/ModuleManager.h"
#include <Windows.h>
#include "../Utils/Logger.h"
#include <glm/ext/matrix_transform.hpp>

using tess_vertex_t = void(__fastcall*)(Tessellator* _this, float v1, float v2, float v3);
using meshHelper_renderImm_t = void(__fastcall*)(__int64, Tessellator* tessellator, MaterialPtr*);

MinecraftUIRenderContext* renderCtx;
GuiData* guiData;
__int64 screenContext2d;
__int64 game3dContext;
Tessellator* tessellator;
float* colorHolder;
std::shared_ptr<glmatrixf> refdef;
Vec2 fov;
Vec2 screenSize;
Vec3 origin;
float lerpT;
TexturePtr* texturePtr = nullptr;

static MaterialPtr* uiMaterial = nullptr;
static MaterialPtr* entityFlatStaticMaterial = nullptr;
static MaterialPtr* blendMaterial = nullptr;

bool DrawUtils::isLeftClickDown = false;
bool DrawUtils::isRightClickDown = false;
bool DrawUtils::shouldToggleLeftClick = false;
bool DrawUtils::shouldToggleRightClick = false;

tess_vertex_t tess_vertex;
meshHelper_renderImm_t meshHelper_renderImm;
// mce__VertexFormat__disableHalfFloats_t mce__VertexFormat__disableHalfFloats;
// Tessellator__initializeFormat_t Tessellator__initializeFormat;

bool hasInitializedSigs = false;
void initializeSigs() {
	tess_vertex = reinterpret_cast<tess_vertex_t>(FindSignature("40 57 48 81 EC ? ? ? ? ? ? 7C 24"));
	meshHelper_renderImm = reinterpret_cast<meshHelper_renderImm_t>(FindSignature("40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 49 8B F0"));
	// mce__VertexFormat__disableHalfFloats = reinterpret_cast<mce__VertexFormat__disableHalfFloats_t>(FindSignature("40 53 48 83 EC ?? 48 8B D9 C7 81 ?? ?? ?? ?? 00 00 00 00 C6 81 ?? ?? ?? ?? 00"));
	// Tessellator__initializeFormat = reinterpret_cast<Tessellator__initializeFormat_t>(FindSignature("48 89 74 24 ?? 57 48 83 EC 20 4C 8B 41 ?? 48 8B FA 4C 2B 41 ?? 48 8B F1 48 83 C1 08 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 49 F7 E8 48 D1 FA 48 8B C2 48 C1 E8 3F 48 03 D0 48 3B FA"));
	hasInitializedSigs = true;
}

ID3D11Device* device2 = nullptr;
IDXGISurface* back_buffer = nullptr;
ID2D1DeviceContext* context = nullptr;
ID2D1SolidColorBrush* brush = nullptr;
IDWriteFactory* write_factory = nullptr;
IDWriteTextFormat* text_format = nullptr;

wchar_t font[32] = L"Segoe UI";

bool initialized = false;

void D2DUI::initRendering(IDXGISwapChain3* swap_chain) {
	if (initialized) return;

	swap_chain->GetDevice(IID_PPV_ARGS(&device2));
	swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));

	const D2D1_CREATION_PROPERTIES properties = D2D1::CreationProperties(
		D2D1_THREADING_MODE_SINGLE_THREADED,
		D2D1_DEBUG_LEVEL_NONE,
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE);

	D2D1CreateDeviceContext(back_buffer, properties, &context);
	back_buffer->Release();

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&write_factory);

	initialized = true;
}

void D2DUI::deinitRender() {
	if (write_factory) write_factory->Release();
	if (context) context->Release();

	initialized = false;
}

void D2DUI::beginRender() {
	context->BeginDraw();
}

void D2DUI::endRender() {
	context->EndDraw();
}

void D2DUI::drawRect(Vec2 pos, Vec2 size, D2D1::ColorF color, float thickness) {
	context->CreateSolidColorBrush(color, &brush);
	context->DrawRectangle(D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y), brush, thickness);
	brush->Release();
}

void D2DUI::drawRectFilled(Vec2 pos, Vec2 size, D2D1::ColorF color) {
	context->CreateSolidColorBrush(color, &brush);
	context->FillRectangle(D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y), brush);
	brush->Release();
}

void D2DUI::drawLine(Vec2 start, Vec2 end, D2D1::ColorF color, float thickness) {
	context->CreateSolidColorBrush(color, &brush);
	context->DrawLine(D2D1::Point2F(start.x, start.y), D2D1::Point2F(end.x, end.y), brush, thickness);
	brush->Release();
}

void D2DUI::setFont(const wchar_t* font_name) {
	wcscpy_s(font, font_name);
}

void D2DUI::drawText(const wchar_t* text, Vec2 pos, D2D1::ColorF color, bool shadow, float size) {
	write_factory->CreateTextFormat(font, nullptr, DWRITE_FONT_WEIGHT_NORMAL,
									DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &text_format);
	text_format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

	if (shadow) {
		context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(0, 0, 0, 0.5f)), &brush);
		context->DrawTextA(text, wcslen(text), text_format,
						   D2D1::RectF(pos.x + 2, pos.y + 2, pos.x + 10000, pos.y + 10000), brush);
		brush->Release();
	}

	context->CreateSolidColorBrush(color, &brush);
	context->DrawTextA(text, wcslen(text), text_format,
					   D2D1::RectF(pos.x, pos.y, pos.x + 10000, pos.y + 10000), brush);

	brush->Release();
	text_format->Release();
}

// private function
DWRITE_TEXT_METRICS D2DUI::get_metrics(const wchar_t* text, float size) {
	write_factory->CreateTextFormat(font, nullptr, DWRITE_FONT_WEIGHT_NORMAL,
									DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &text_format);
	text_format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

	IDWriteTextLayout* layout;
	write_factory->CreateTextLayout(text, wcslen(text), text_format, 10000, 10000, &layout);

	DWRITE_TEXT_METRICS metrics{};
	layout->GetMetrics(&metrics);

	layout->Release();
	text_format->Release();

	return metrics;
}

float D2DUI::getTextWidth(const wchar_t* text, float size) {
	return get_metrics(text, size).width;
}

float D2DUI::getTextHeight(const wchar_t* text, float size) {
	return get_metrics(text, size).height;
}


void DrawUtils::setCtx(MinecraftUIRenderContext* ctx, GuiData* gui) {
	if (!hasInitializedSigs)
		initializeSigs();
	LARGE_INTEGER EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - Game.getLastUpdateTime();

	ElapsedMicroseconds.QuadPart *= 1000000;
	int ticksPerSecond = 20;
	if (Game.getClientInstance()->minecraft)
		if (Game.getClientInstance()->minecraft->timer != nullptr)
			ticksPerSecond = (int)*Game.getClientInstance()->minecraft->timer;
	if (ticksPerSecond < 1)
		ticksPerSecond = 1;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart / ticksPerSecond;
	lerpT = (ElapsedMicroseconds.QuadPart / 1000000.f);
	if (lerpT > 1)
		lerpT = 1;
	else if (lerpT < 0)
		lerpT = 0;

	guiData = gui;
	renderCtx = ctx;
	screenContext2d = reinterpret_cast<__int64*>(renderCtx)[2];

	tessellator = *reinterpret_cast<Tessellator**>(screenContext2d + 0xC0);
	colorHolder = *reinterpret_cast<float**>(screenContext2d + 0x30);

	glmatrixf* badrefdef = Game.getClientInstance()->getRefDef();

	refdef = std::shared_ptr<glmatrixf>(badrefdef->correct());
	fov = Game.getClientInstance()->getFov();
	screenSize.x = gui->widthGame;
	screenSize.y = gui->heightGame;
	if (Game.getClientInstance()->levelRenderer != nullptr)
		origin = Game.getClientInstance()->levelRenderer->getOrigin();

	if (uiMaterial == nullptr)
		uiMaterial = reinterpret_cast<MaterialPtr*>(mce::MaterialPtr::createMaterial(HashedString("ui_fill_color")));

	if (entityFlatStaticMaterial == nullptr)
		entityFlatStaticMaterial = reinterpret_cast<MaterialPtr*>(mce::MaterialPtr::createMaterial(HashedString("selection_overlay")));

	if (blendMaterial == nullptr)
		blendMaterial = reinterpret_cast<MaterialPtr*>(mce::MaterialPtr::createMaterial(HashedString("fullscreen_cube_overlay_blend")));
}

void DrawUtils::setColor(float r, float g, float b, float a) {
	colorHolder[0] = r;
	colorHolder[1] = g;
	colorHolder[2] = b;
	colorHolder[3] = a;
	*reinterpret_cast<uint8_t*>(colorHolder + 4) = 1;
}

Font* DrawUtils::getFont(Fonts font) {
	static auto fontChangerModule = moduleMgr->getModule<FontChanger>();

	if (fontChangerModule->isEnabled() && fontChangerModule->Fonts.selected == 1)
		return Game.getClientInstance()->minecraftGame->mcFont;
	else
		return Game.getClientInstance()->minecraftGame->getOldFont();

	switch (font) {
	case Fonts::SMOOTH:
		return Game.getClientInstance()->minecraftGame->getTheGoodFontThankYou();
		break;
	case Fonts::UNICOD:
		return Game.getClientInstance()->minecraftGame->getTheBetterFontYes();
		break;
	case Fonts::RUNE:
		return Game.getClientInstance()->_getRuneFont();
		break;
	case Fonts::MCFONT:
		return Game.getClientInstance()->minecraftGame->mcFont;
		break;
	default:
		return Game.getClientInstance()->_getFont();
		break;
	}
}

Tessellator* DrawUtils::get3dTessellator() {
	auto myTess = *reinterpret_cast<Tessellator**>(game3dContext + 0xC0);
	return myTess;
}

__int64 DrawUtils::getScreenContext() {
	return game3dContext == 0 ? screenContext2d : game3dContext;
}

MatrixStack* DrawUtils::getMatrixStack() {
	return reinterpret_cast<MatrixStack*>(*reinterpret_cast<__int64*>(DrawUtils::getScreenContext() + 0x18i64) + 0x30i64);
}

float DrawUtils::getTextWidth(std::string* textStr, float textSize, Fonts font) {
	TextHolder text(*textStr);

	Font* fontPtr = getFont(font);

	float ret = renderCtx->getLineLength(fontPtr, &text, textSize, false);

	return ret;
}

float DrawUtils::getFontHeight(float textSize, Fonts font) {
	Font* fontPtr = getFont(font);

	float ret = fontPtr->getLineHeight() * textSize;

	return ret;
}

void DrawUtils::flush() {
	renderCtx->flushText(0);
}

void DrawUtils::drawTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3) {
	DrawUtils::tess__begin(tessellator, 3, 3);

	tess_vertex(tessellator, p1.x, p1.y, 0);
	tess_vertex(tessellator, p2.x, p2.y, 0);
	tess_vertex(tessellator, p3.x, p3.y, 0);

	meshHelper_renderImm(screenContext2d, tessellator, uiMaterial);
}

void DrawUtils::drawQuad(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4) {
	DrawUtils::tess__begin(tessellator, 1, 4);

	tess_vertex(tessellator, p1.x, p1.y, 0);
	tess_vertex(tessellator, p2.x, p2.y, 0);
	tess_vertex(tessellator, p3.x, p3.y, 0);
	tess_vertex(tessellator, p4.x, p4.y, 0);

	meshHelper_renderImm(screenContext2d, tessellator, uiMaterial);
}

void DrawUtils::drawLine(const Vec2& start, const Vec2& end, float lineWidth) {
	float modX = 0 - (start.y - end.y);
	float modY = start.x - end.x;

	float len = sqrtf(modX * modX + modY * modY);

	modX /= len;
	modY /= len;
	modX *= lineWidth;
	modY *= lineWidth;

	DrawUtils::tess__begin(tessellator, 3, 6);

	tess_vertex(tessellator, start.x + modX, start.y + modY, 0);
	tess_vertex(tessellator, start.x - modX, start.y - modY, 0);
	tess_vertex(tessellator, end.x - modX, end.y - modY, 0);

	tess_vertex(tessellator, start.x + modX, start.y + modY, 0);
	tess_vertex(tessellator, end.x + modX, end.y + modY, 0);
	tess_vertex(tessellator, end.x - modX, end.y - modY, 0);

	meshHelper_renderImm(screenContext2d, tessellator, uiMaterial);
}

void DrawUtils::drawText(const Vec2& pos, std::string* textStr, const Mc_Color& color, float textSize, float alpha, Fonts font, bool drawShadow) {
	TextHolder text(*textStr);
	Font* fontPtr = getFont(font);
	static uintptr_t caretMeasureData = 0xFFFFFFFF;

	float posF[4];  // Vec4(startX, startY, endX, endY);
	posF[0] = pos.x;
	posF[1] = pos.x + 1000;
	posF[2] = pos.y - 1;
	posF[3] = pos.y + 1000;

	TextMeasureData textMeasure{};
	memset(&textMeasure, 0, sizeof(TextMeasureData));
	textMeasure.textSize = textSize;
	textMeasure.displayShadow = drawShadow;

	renderCtx->drawText(fontPtr, posF, &text, color.arr, alpha, 0, &textMeasure, &caretMeasureData);
}

void DrawUtils::drawBox(const Vec3& lower, const Vec3& upper, float lineWidth, bool fill, int mode) {
	// Calculate the dimensions of the box
	Vec3 diff = upper.sub(lower);

	// Create an array of vertices representing the corners of the box
	Vec3 vertices[8];
	vertices[0] = Vec3(lower.x, lower.y, lower.z);
	vertices[1] = Vec3(lower.x + diff.x, lower.y, lower.z);
	vertices[2] = Vec3(lower.x, lower.y + diff.y, lower.z);
	vertices[3] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z);
	vertices[4] = Vec3(lower.x, lower.y, lower.z + diff.z);
	vertices[5] = Vec3(lower.x + diff.x, lower.y, lower.z + diff.z);
	vertices[6] = Vec3(lower.x, lower.y + diff.y, lower.z + diff.z);
	vertices[7] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z + diff.z);

	if (fill) {
		// Convert the vertices to screen coordinates
		std::vector<Vec2> screenCords;
		for (int i = 0; i < 8; i++) {
			Vec2 screen;
			if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
				screenCords.push_back(screen);
			}
		}

		// Return if there are less than four points to draw quads with
		if (screenCords.size() < 8) return;

		// Define the indices of the vertices to use for each quad face
		std::vector<std::tuple<int, int, int, int>> faces = {
			{0, 1, 3, 2},  // Bottom face
			{4, 5, 7, 6},  // Top face
			{0, 1, 5, 4},  // Front face
			{2, 3, 7, 6},  // Back face
			{1, 3, 7, 5},  // Right face
			{0, 2, 6, 4}   // Left face
		};

		// Draw the quads to fill the box
		for (auto face : faces) {
			DrawUtils::drawQuad(screenCords[std::get<0>(face)], screenCords[std::get<1>(face)], screenCords[std::get<2>(face)], screenCords[std::get<3>(face)]);
			DrawUtils::drawQuad(screenCords[std::get<3>(face)], screenCords[std::get<2>(face)], screenCords[std::get<1>(face)], screenCords[std::get<0>(face)]);
		}
	}

	if (mode == 1 || mode == 2) {
		// Convert the vertices to screen coordinates
		std::vector<std::tuple<int, Vec2>> screenCords;
		for (int i = 0; i < 8; i++) {
			Vec2 screen;
			if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
				screenCords.emplace_back(mode == 2 ? (int)screenCords.size() : i, screen);
			}
		}

		// Return if there are less than two points to draw lines between
		if (screenCords.size() < 2) return;

		switch (mode) {
		case 1: {
			// Draw lines between all pairs of vertices
			for (auto it = screenCords.begin(); it != screenCords.end(); it++) {
				auto from = *it;
				auto fromOrig = vertices[std::get<0>(from)];

				for (auto to : screenCords) {
					auto toOrig = vertices[std::get<0>(to)];

					// Determine if the line should be drawn based on the relative positions of the vertices
					bool shouldDraw = false;
					// X direction
					shouldDraw |= fromOrig.y == toOrig.y && fromOrig.z == toOrig.z && fromOrig.x < toOrig.x;
					// Y direction
					shouldDraw |= fromOrig.x == toOrig.x && fromOrig.z == toOrig.z && fromOrig.y < toOrig.y;
					// Z direction
					shouldDraw |= fromOrig.x == toOrig.x && fromOrig.y == toOrig.y && fromOrig.z < toOrig.z;

					if (shouldDraw) DrawUtils::drawLine(std::get<1>(from), std::get<1>(to), lineWidth);
				}
			}
			return;
			break;
		}
		case 2: {
			// Find start vertex
			auto it = screenCords.begin();
			std::tuple<int, Vec2> start = *it;
			it++;
			for (; it != screenCords.end(); it++) {
				auto cur = *it;
				if (std::get<1>(cur).x < std::get<1>(start).x) {
					start = cur;
				}
			}

			// Follow outer line
			std::vector<int> indices;

			auto current = start;
			indices.push_back(std::get<0>(current));
			Vec2 lastDir(0, -1);
			do {
				float smallestAngle = PI * 2;
				Vec2 smallestDir;
				std::tuple<int, Vec2> smallestE;
				auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
				for (auto cur : screenCords) {
					if (std::get<0>(current) == std::get<0>(cur))
						continue;

					// angle between vecs
					Vec2 dir = Vec2(std::get<1>(cur)).sub(std::get<1>(current));
					float angle = atan2(dir.y, dir.x) - lastDirAtan2;
					if (angle > PI) {
						angle -= 2 * PI;
					} else if (angle <= -PI) {
						angle += 2 * PI;
					}
					if (angle >= 0 && angle < smallestAngle) {
						smallestAngle = angle;
						smallestDir = dir;
						smallestE = cur;
					}
				}
				indices.push_back(std::get<0>(smallestE));
				lastDir = smallestDir;
				current = smallestE;
			} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

			// draw

			Vec2 lastVertex;
			bool hasLastVertex = false;
			for (auto& indice : indices) {
				Vec2 curVertex = std::get<1>(screenCords[indice]);
				if (!hasLastVertex) {
					hasLastVertex = true;
					lastVertex = curVertex;
					continue;
				}

				drawLine(lastVertex, curVertex, lineWidth);
				lastVertex = curVertex;
			}
			return;
			break;
		}
		}
	}
}

void DrawUtils::drawBoxv2(const Vec3& lower, const Vec3& upper, float lineWidth, bool outline) {
	Vec3 vertices[4];
	vertices[0] = Vec3(lower.x, lower.y, lower.z);
	vertices[1] = Vec3(lower.x + (upper.x - lower.x), lower.y, lower.z);
	vertices[2] = Vec3(lower.x, lower.y, lower.z + (upper.z - lower.z));
	vertices[3] = Vec3(lower.x + (upper.x - lower.x), lower.y, lower.z + (upper.z - lower.z));

	// Convert to screen coord
	std::vector<std::tuple<int, Vec2>> screenCords;
	for (int i = 0; i < 4; i++) {
		Vec2 screen;
		if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
			screenCords.emplace_back((int)screenCords.size(), screen);
		}
	}
	if (screenCords.size() < 2)
		return;  // No lines possible

	// Find start vertex
	auto it = screenCords.begin();
	std::tuple<int, Vec2> start = *it;
	it++;
	for (; it != screenCords.end(); it++) {
		auto cur = *it;
		if (std::get<1>(cur).x < std::get<1>(start).x) {
			start = cur;
		}
	}

	// Follow the outer line
	std::vector<int> indices;

	auto current = start;
	indices.push_back(std::get<0>(current));
	Vec2 lastDir(0, -1);
	do {
		float smallestAngle = PI * 2;
		Vec2 smallestDir;
		std::tuple<int, Vec2> smallestE;
		auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
		for (auto cur : screenCords) {
			if (std::get<0>(current) == std::get<0>(cur))
				continue;

			// angle between vecs
			Vec2 dir = Vec2(std::get<1>(cur)).sub(std::get<1>(current));
			float angle = atan2(dir.y, dir.x) - lastDirAtan2;
			if (angle > PI) {
				angle -= 2 * PI;
			} else if (angle <= -PI) {
				angle += 2 * PI;
			}
			if (angle >= 0 && angle < smallestAngle) {
				smallestAngle = angle;
				smallestDir = dir;
				smallestE = cur;
			}
		}
		indices.push_back(std::get<0>(smallestE));
		lastDir = smallestDir;
		current = smallestE;
	} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

	// draw

	Vec2 lastVertex;
	bool hasLastVertex = false;
	for (auto& indice : indices) {
		Vec2 curVertex = std::get<1>(screenCords[indice]);
		if (!hasLastVertex) {
			hasLastVertex = true;
			lastVertex = curVertex;
			continue;
		}
		DrawUtils::drawLine(lastVertex, curVertex, lineWidth);
		lastVertex = curVertex;
	}
}

void DrawUtils::draw2DBox(const Vec3& lower, const Vec3& upper, float lineWidth, bool fill, bool corners) {
	if (Game.getLocalPlayer() == nullptr) return;
	Vec3 worldPoints[8];
	worldPoints[0] = Vec3(lower.x, lower.y, lower.z);
	worldPoints[1] = Vec3(lower.x, lower.y, upper.z);
	worldPoints[2] = Vec3(upper.x, lower.y, lower.z);
	worldPoints[3] = Vec3(upper.x, lower.y, upper.z);
	worldPoints[4] = Vec3(lower.x, upper.y, lower.z);
	worldPoints[5] = Vec3(lower.x, upper.y, upper.z);
	worldPoints[6] = Vec3(upper.x, upper.y, lower.z);
	worldPoints[7] = Vec3(upper.x, upper.y, upper.z);

	std::vector<Vec2> points;
	for (int i = 0; i < 8; i++) {
		Vec2 result;
		if (refdef->OWorldToScreen(origin, worldPoints[i], result, fov, screenSize))
			points.emplace_back(result);
	}
	if (points.size() < 1) return;

	Vec4 resultRect = {points[0].x, points[0].y, points[0].x, points[0].y};
	for (const auto& point : points) {
		if (point.x < resultRect.x) resultRect.x = point.x;
		if (point.y < resultRect.y) resultRect.y = point.y;
		if (point.x > resultRect.z) resultRect.z = point.x;
		if (point.y > resultRect.w) resultRect.w = point.y;
	}
	if (fill) DrawUtils::fillRectangle(Vec2(resultRect.x, resultRect.y), Vec2(resultRect.z, resultRect.w));
	if (!corners)
		DrawUtils::drawRectangle(Vec2(resultRect.x, resultRect.y), Vec2(resultRect.z, resultRect.w), lineWidth);
	else {
		float length = (resultRect.x - resultRect.z) / 4.f;

		// Top left
		DrawUtils::drawLine(Vec2(resultRect.x, resultRect.y), Vec2(resultRect.x - length, resultRect.y), lineWidth);
		DrawUtils::drawLine(Vec2(resultRect.x, resultRect.y), Vec2(resultRect.x, resultRect.y - length), lineWidth);

		// Top right
		DrawUtils::drawLine(Vec2(resultRect.z, resultRect.y), Vec2(resultRect.z + length, resultRect.y), lineWidth);
		DrawUtils::drawLine(Vec2(resultRect.z, resultRect.y), Vec2(resultRect.z, resultRect.y - length), lineWidth);

		// Bottom left
		DrawUtils::drawLine(Vec2(resultRect.x, resultRect.w), Vec2(resultRect.x - length, resultRect.w), lineWidth);
		DrawUtils::drawLine(Vec2(resultRect.x, resultRect.w), Vec2(resultRect.x, resultRect.w + length), lineWidth);

		// Bottom right
		DrawUtils::drawLine(Vec2(resultRect.z, resultRect.w), Vec2(resultRect.z + length, resultRect.w), lineWidth);
		DrawUtils::drawLine(Vec2(resultRect.z, resultRect.w), Vec2(resultRect.z, resultRect.w + length), lineWidth);
	}
}

void DrawUtils::drawEntityBox(Entity* ent, float lineWidth, bool fill) {
	Vec3 end = *ent->getPos();
	AABB render;
	if (ent->isPlayer()) {
		render = AABB(end, ent->aabb->width, ent->aabb->height, ent->aabb->height);
		render.upper.y += 0.2f;
		render.lower.y += 0.2f;
	} else
		render = AABB(end, ent->aabb->width, ent->aabb->height, 0);
	render.upper.y += 0.1f;

	float LineWidth = (float)fmax(0.5f, 1 / (float)fmax(1, (float)Game.getLocalPlayer()->getPos()->dist(end)));
	DrawUtils::drawBox(render.lower, render.upper, lineWidth == 0 ? LineWidth : lineWidth, fill);
}

void DrawUtils::drawBetterESP(Entity* ent, float lineWidth) {
	// Vec3* end = ent->getPos();
	//  Vec3 lerped = ent->getPosPrev()->lerp(ent->getPos(), getLerpTime());

	AABB render(ent->getRenderPositionComponent()->renderPos, ent->aabb->width, ent->aabb->height, ent->getRenderPositionComponent()->renderPos.y - ent->aabb->lower.y);
	render.upper.y += 0.1f;

	DrawUtils::drawBox(render.lower, render.upper, lineWidth);
}

void DrawUtils::draw2D(Entity* ent, float lineWidth) {
	if (Game.getLocalPlayer() == nullptr) return;
	Vec3 end = *ent->getPos();
	AABB render;
	if (ent->isPlayer()) {
		render = AABB(end, ent->aabb->width, ent->aabb->height, ent->aabb->height);
		render.upper.y += 0.2f;
		render.lower.y += 0.2f;
	} else
		render = AABB(end, ent->aabb->width, ent->aabb->height, 0);
	render.upper.y += 0.1f;

	Vec3 worldPoints[8];
	worldPoints[0] = Vec3(render.lower.x, render.lower.y, render.lower.z);
	worldPoints[1] = Vec3(render.lower.x, render.lower.y, render.upper.z);
	worldPoints[2] = Vec3(render.upper.x, render.lower.y, render.lower.z);
	worldPoints[3] = Vec3(render.upper.x, render.lower.y, render.upper.z);
	worldPoints[4] = Vec3(render.lower.x, render.upper.y, render.lower.z);
	worldPoints[5] = Vec3(render.lower.x, render.upper.y, render.upper.z);
	worldPoints[6] = Vec3(render.upper.x, render.upper.y, render.lower.z);
	worldPoints[7] = Vec3(render.upper.x, render.upper.y, render.upper.z);

	std::vector<Vec2> points;
	for (int i = 0; i < 8; i++) {
		Vec2 result;
		if (refdef->OWorldToScreen(origin, worldPoints[i], result, fov, screenSize))
			points.emplace_back(result);
	}
	if (points.size() < 1) return;

	Vec4 resultRect = {points[0].x, points[0].y, points[0].x, points[0].y};
	for (const auto& point : points) {
		if (point.x < resultRect.x) resultRect.x = point.x;
		if (point.y < resultRect.y) resultRect.y = point.y;
		if (point.x > resultRect.z) resultRect.z = point.x;
		if (point.y > resultRect.w) resultRect.w = point.y;
	}
	float LineWidth = (float)fmax(0.5f, 1 / (float)fmax(1, (float)Game.getLocalPlayer()->getPos()->dist(end)));
	DrawUtils::drawRectangle(Vec2(resultRect.x, resultRect.y), Vec2(resultRect.z, resultRect.w), lineWidth == 0 ? LineWidth : lineWidth);
}

void DrawUtils::drawZephyr(Entity* ent, float lineWidth) {
	// Vec3* end = ent->getPos();
	// Vec3 base = ent->getPosPrev()->lerp(ent->getPos(), getLerpTime());

	float ofs = (Game.getLocalPlayer()->getActorHeadRotationComponent()->rot.y + 90.f) * (PI / 180);

	Vec3 corners[4];
	Vec2 corners2d[4];

	corners[0] = Vec3(ent->getRenderPositionComponent()->renderPos.x - ent->aabb->width / 1.5f * -sin(ofs), ent->aabb->upper.y + (float)0.1, ent->getRenderPositionComponent()->renderPos.z - ent->aabb->width / 1.5f * cos(ofs));
	corners[1] = Vec3(ent->getRenderPositionComponent()->renderPos.x + ent->aabb->width / 1.5f * -sin(ofs), ent->aabb->upper.y + (float)0.1, ent->getRenderPositionComponent()->renderPos.z + ent->aabb->width / 1.5f * cos(ofs));
	corners[2] = Vec3(ent->getRenderPositionComponent()->renderPos.x - ent->aabb->width / 1.5f * -sin(ofs), ent->aabb->lower.y, ent->getRenderPositionComponent()->renderPos.z - ent->aabb->width / 1.5f * cos(ofs));
	corners[3] = Vec3(ent->getRenderPositionComponent()->renderPos.x + ent->aabb->width / 1.5f * -sin(ofs), ent->aabb->lower.y, ent->getRenderPositionComponent()->renderPos.z + ent->aabb->width / 1.5f * cos(ofs));

	if (refdef->OWorldToScreen(origin, corners[0], corners2d[0], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[1], corners2d[1], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[2], corners2d[2], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[3], corners2d[3], fov, screenSize)) {
		float length = (corners2d[1].x - corners2d[0].x) / 4.f;

		drawLine(corners2d[0], corners2d[1], lineWidth);
		drawLine(corners2d[0], corners2d[2], lineWidth);
		drawLine(corners2d[3], corners2d[1], lineWidth);
		drawLine(corners2d[3], corners2d[2], lineWidth);
	}
}


void DrawUtils::drawItem(ItemStack* item, const Vec2& itemPos, float opacity, float scale, bool isEnchanted) {
	__int64 scnCtx = reinterpret_cast<__int64*>(renderCtx)[2];
	auto* screenCtx = reinterpret_cast<ScreenContext*>(scnCtx);
	BaseActorRenderContext baseActorRenderCtx(screenCtx, Game.getClientInstance(), Game.getClientInstance()->minecraftGame);
	ItemRenderer* renderer = baseActorRenderCtx.itemRenderer;
	renderer->renderGuiItemNew(&baseActorRenderCtx, item, 0, itemPos.x, itemPos.y, opacity, scale, isEnchanted);
}

Vec2 DrawUtils::worldToScreen(const Vec3& world) {
	Vec2 ret{-1, -1};
	refdef->OWorldToScreen(origin, world, ret, fov, screenSize);
	return ret;
}
void DrawUtils::drawLine3d(const Vec3& start, const Vec3& end, bool onUi) {
	if (game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	auto myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 4, 2);

	auto start1 = start.sub(origin);
	auto end1 = end.sub(origin);

	tess_vertex(myTess, start1.x, start1.y, start1.z);
	tess_vertex(myTess, end1.x, end1.y, end1.z);

	meshHelper_renderImm(game3dContext, myTess, onUi ? uiMaterial : blendMaterial);
}
void DrawUtils::drawBox3d(const Vec3& lower, const Vec3& upper, float scale, bool onUi) {
	if (game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	Tessellator* myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 4, 12);

	Vec3 diff;
	diff.x = upper.x - lower.x;
	diff.y = upper.y - lower.y;
	diff.z = upper.z - lower.z;

	auto newLower = lower.sub(origin);

	Vec3 vertices[8];
	vertices[0] = Vec3(newLower.x, newLower.y, newLower.z);
	vertices[1] = Vec3(newLower.x + diff.x, newLower.y, newLower.z);
	vertices[2] = Vec3(newLower.x, newLower.y, newLower.z + diff.z);
	vertices[3] = Vec3(newLower.x + diff.x, newLower.y, newLower.z + diff.z);

	vertices[4] = Vec3(newLower.x, newLower.y + diff.y, newLower.z);
	vertices[5] = Vec3(newLower.x + diff.x, newLower.y + diff.y, newLower.z);
	vertices[6] = Vec3(newLower.x, newLower.y + diff.y, newLower.z + diff.z);
	vertices[7] = Vec3(newLower.x + diff.x, newLower.y + diff.y, newLower.z + diff.z);
	// Scale vertices using glm
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(scale), 0.f, glm::vec3(1.0f, 1.0f, 1.0f));
	Vec3 newLowerReal = newLower.add(0.5f, 0.5f, 0.5f);  // .add(0.4375f, 0.4375f, 0.4375f) is chest
	for (int i = 0; i < 8; i++) {
		glm::vec4 rotatedVertex = rotationMatrix * glm::vec4(vertices[i].x - newLowerReal.x, vertices[i].y - newLowerReal.y, vertices[i].z - newLowerReal.z, 0.0f);
		vertices[i] = Vec3{rotatedVertex.x + newLowerReal.x, rotatedVertex.y + newLowerReal.y, rotatedVertex.z + newLowerReal.z};
	}

#define line(m, n)                      \
	tess_vertex(myTess, m.x, m.y, m.z); \
	tess_vertex(myTess, n.x, n.y, n.z);

	// Top square
	line(vertices[4], vertices[5]);
	line(vertices[5], vertices[7]);
	line(vertices[7], vertices[6]);
	line(vertices[6], vertices[4]);

	// Bottom Square
	line(vertices[0], vertices[1]);
	line(vertices[1], vertices[3]);
	line(vertices[3], vertices[2]);
	line(vertices[2], vertices[0]);

	// Sides
	line(vertices[0], vertices[4]);
	line(vertices[1], vertices[5]);
	line(vertices[2], vertices[6]);
	line(vertices[3], vertices[7]);

#undef line

	meshHelper_renderImm(game3dContext, myTess, onUi ? uiMaterial : blendMaterial);
}

void DrawUtils::drawBox3dFilled(const Vec3& lower, const Vec3& upper, float scale, bool outline, bool onUi) {
	if (game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	Tessellator* myTess = DrawUtils::get3dTessellator();
	Vec3 diff = upper.sub(lower);
	Vec3 newLower = lower.sub(origin);
	Vec3 vertices[8] = {
		{newLower.x, newLower.y, newLower.z},
		{newLower.x + diff.x, newLower.y, newLower.z},
		{newLower.x, newLower.y, newLower.z + diff.z},
		{newLower.x + diff.x, newLower.y, newLower.z + diff.z},

		{newLower.x, newLower.y + diff.y, newLower.z},
		{newLower.x + diff.x, newLower.y + diff.y, newLower.z},
		{newLower.x, newLower.y + diff.y, newLower.z + diff.z},
		{newLower.x + diff.x, newLower.y + diff.y, newLower.z + diff.z}};
	// Scale vertices using glm
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(scale), 0.f, glm::vec3(1.0f, 1.0f, 1.0f));
	Vec3 newLowerReal = newLower.add(0.5f, 0.5f, 0.5f);  // .add(0.4375f, 0.4375f, 0.4375f) is chest
	for (int i = 0; i < 8; i++) {
		glm::vec4 rotatedVertex = rotationMatrix * glm::vec4(vertices[i].x - newLowerReal.x, vertices[i].y - newLowerReal.y, vertices[i].z - newLowerReal.z, 0.0f);
		vertices[i] = Vec3{rotatedVertex.x + newLowerReal.x, rotatedVertex.y + newLowerReal.y, rotatedVertex.z + newLowerReal.z};
	}

	DrawUtils::tess__begin(myTess, 1);
	static int v[48] = {5, 7, 6, 4, 4, 6, 7, 5, 1, 3, 2, 0, 0, 2, 3, 1, 4, 5, 1, 0, 0, 1, 5, 4, 6, 7, 3, 2, 2, 3, 7, 6, 4, 6, 2, 0, 0, 2, 6, 4, 5, 7, 3, 1, 1, 3, 7, 5};
	for (int i = 0; i < 48; i++) tess_vertex(myTess, vertices[v[i]].x, vertices[v[i]].y, vertices[v[i]].z);
	meshHelper_renderImm(game3dContext, myTess, onUi ? uiMaterial : blendMaterial);

	if (!outline) return;
	DrawUtils::tess__begin(myTess, 4, 12);
#define line(m, n)                      \
	tess_vertex(myTess, m.x, m.y, m.z); \
	tess_vertex(myTess, n.x, n.y, n.z);

	// Top square
	line(vertices[4], vertices[5]);
	line(vertices[5], vertices[7]);
	line(vertices[7], vertices[6]);
	line(vertices[6], vertices[4]);

	// Bottom Square
	line(vertices[0], vertices[1]);
	line(vertices[1], vertices[3]);
	line(vertices[3], vertices[2]);
	line(vertices[2], vertices[0]);

	// Sides
	line(vertices[0], vertices[4]);
	line(vertices[1], vertices[5]);
	line(vertices[2], vertices[6]);
	line(vertices[3], vertices[7]);

#undef line
	meshHelper_renderImm(game3dContext, myTess, onUi ? uiMaterial : blendMaterial);
}

void DrawUtils::drawCircle(Vec2 pos, Vec2 radius, Mc_Color color, double quality) {
	DrawUtils::setColor(color.r, color.g, color.b, color.a);
	DrawUtils::tess__begin(tessellator, 5);

	for (int i = 0; i <= 360 / quality; i++) {
		double x2 = sin(((i * quality * PI) / 180)) * radius.x;
		double y2 = cos(((i * quality * PI) / 180)) * radius.y;
		tess_vertex(tessellator, pos.x + x2, pos.y + y2, 0);
	}
	meshHelper_renderImm(screenContext2d, tessellator, uiMaterial);
}

void DrawUtils::drawCircleFilled(Vec2 pos, Vec2 radius, Mc_Color color, double quality) {
	float x;
	float y;
	DrawUtils::setColor(color.r, color.g, color.b, color.a);
	for (double i = 0; i <= 360;) {
		DrawUtils::tess__begin(tessellator, 3);
		x = radius.x * (float)cos(i);
		y = radius.y * (float)sin(i);
		tess_vertex(tessellator, x + pos.x, y + pos.y, 0);
		i = i + quality;
		x = radius.x * (float)cos(i);
		y = radius.y * (float)sin(i);
		tess_vertex(tessellator, x + pos.x, y + pos.y, 0);
		tess_vertex(tessellator, pos.x, pos.y, 0);
		i = i + quality;
	}

	meshHelper_renderImm(screenContext2d, tessellator, uiMaterial);
}

void DrawUtils::fillRectangle(const Vec4& pos, const Mc_Color& col, float alpha) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawQuad({pos.x, pos.w}, {pos.z, pos.w}, {pos.z, pos.y}, {pos.x, pos.y});
}

void DrawUtils::fillRectangle3(Vec4 pos, Mc_Color col) {
	DrawUtils::fillRectangle(pos, col, col.a);
}

void DrawUtils::drawBoxBottom(const Vec4& pos, const Mc_Color& col, float alpha, float thickness) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawLine({pos.z, pos.y}, {pos.x, pos.y}, thickness);
}

inline void DrawUtils::tess__begin(Tessellator* tess, int vertexFormat, int numVerticesReserved) {
	__int64 tessellator = reinterpret_cast<__int64>(tess);

	using tess_begin_t = void(__fastcall*)(Tessellator*, int, int);
	static tess_begin_t tess_begin = reinterpret_cast<tess_begin_t>(FindSignature("48 89 5C 24 ?? 55 48 83 EC ?? 80 B9 ?? ?? ?? ?? 00 45"));
	tess_begin(tess, vertexFormat, numVerticesReserved);
}
void DrawUtils::setGameRenderContext(std::int64_t ctx) {
	game3dContext = ctx;
	if (Game.getClientInstance()->levelRenderer != nullptr)
		origin = Game.getClientInstance()->levelRenderer->getOrigin();

	if (ctx) {
		LARGE_INTEGER EndingTime, ElapsedMicroseconds;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - Game.getLastUpdateTime();

		ElapsedMicroseconds.QuadPart *= 1000000;
		int ticksPerSecond = 20;
		if (Game.getClientInstance()->minecraft)
			ticksPerSecond = (int)*Game.getClientInstance()->minecraft->timer;
		ticksPerSecond = std::max(ticksPerSecond, 1);
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart / ticksPerSecond;
		lerpT = (ElapsedMicroseconds.QuadPart / 1000000.f);
		lerpT = std::clamp(lerpT, 0.0f, 1.0f);
	}
}
float DrawUtils::getLerpTime() {
	return lerpT;
}
Vec3 DrawUtils::getOrigin() {
	return origin;
}
void DrawUtils::drawLinestrip3d(const std::vector<Vec3>& points) {
	if (game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	auto myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 5, (int)points.size());

	/*
	 * 1: quads
	 * 2: triangle list
	 * 3: trianglestrip (6)
	 * 4: line list
	 * 5: line strip (7)
	 */

	for (const auto& p : points) {
		auto pD = p.sub(origin);
		tess_vertex(myTess, pD.x, pD.y, pD.z);
	}

	meshHelper_renderImm(game3dContext, myTess, entityFlatStaticMaterial);
}

Mc_Color Mc_Color::lerp(const Mc_Color& o, float t) const {
	return Mc_Color(Utils::lerp(r, o.r, t), Utils::lerp(g, o.g, t), Utils::lerp(b, o.b, t), Utils::lerp(a, o.a, t));
}

void DrawUtils::onMouseClickUpdate(int key, bool isDown) {
	if (Game.isInGame())
		switch (key) {
		case 1:  // Left Click
			isLeftClickDown = isDown;
			if (isDown)
				shouldToggleLeftClick = true;
			break;
		case 2:  // Right Click
			isRightClickDown = isDown;
			if (isDown)
				shouldToggleRightClick = true;
			break;
		}
}
