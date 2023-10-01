#pragma once

#include <Windows.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dwrite_1.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <initguid.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

class D2DUI {
public:
	static void initRendering(IDXGISwapChain3* swap_chain);
	static void deinitRender();

	static void beginRender();
	static void endRender();

	static void drawRect(Vec2 pos, Vec2 size, D2D1::ColorF color, float thickness = 1.0f);
	static void drawRectFilled(Vec2 pos, Vec2 size, D2D1::ColorF color);
	static void drawLine(Vec2 start, Vec2 end, D2D1::ColorF color, float thickness = 1.0f);

	static void setFont(const wchar_t* font_name);
	static void drawText(const wchar_t* text, Vec2 pos, D2D1::ColorF color, bool shadow = false, float size = 12.0f);
	static float getTextWidth(const wchar_t* text, float size = 12.0f);
	static float getTextHeight(const wchar_t* text, float size = 12.0f);
	static DWRITE_TEXT_METRICS get_metrics(const wchar_t* text, float size);
};