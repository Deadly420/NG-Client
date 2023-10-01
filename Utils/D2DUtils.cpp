#include "D2DUtils.h"

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