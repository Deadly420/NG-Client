#include "D2DHooks.h"
#include "../Utils/D2DUtils.h"

typedef HRESULT(__thiscall* present_t)(IDXGISwapChain3*, UINT, UINT);
present_t original_present;

typedef HRESULT(__thiscall* resize_buffers_t)(IDXGISwapChain3*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
resize_buffers_t original_resize_buffers;
ID3D11Device* device;

HRESULT PresentD3D(IDXGISwapChain3* swap_chain, UINT sync_interval, UINT flags) {
	static bool once = false;
	if (!once) {
		ID3D12Device* bad_device;
		if (SUCCEEDED(swap_chain->GetDevice(IID_PPV_ARGS(&bad_device)))) {
			dynamic_cast<ID3D12Device5*>(bad_device)->RemoveDevice();
			return original_present(swap_chain, sync_interval, flags);
		}
		once = true;
	}

	if (FAILED(swap_chain->GetDevice(IID_PPV_ARGS(&device))))
		return original_present(swap_chain, sync_interval, flags);

	// the game is now using D3D11
	D2DUI::initRendering(swap_chain);
	D2DUI::beginRender();

	D2DUI::drawRectFilled(Vec2(100, 100), Vec2(100, 100), D2D1::ColorF(D2D1::ColorF::Red));
	D2DUI::drawRect(Vec2(100, 100), Vec2(100, 100), D2D1::ColorF(D2D1::ColorF::Black), 5.0f);

	D2DUI::drawLine(Vec2(100, 100), Vec2(200, 200), D2D1::ColorF(D2D1::ColorF::Black), 5.0f);

	D2DUI::setFont(L"Arial");
	D2DUI::drawText(L"Greetings planet - Floppy", Vec2(100, 100), D2D1::ColorF(D2D1::ColorF::White), false, 20.0f);

	D2DUI::endRender();

	return original_present(swap_chain, sync_interval, flags);
}

HRESULT ResizeBuffersD3D(IDXGISwapChain3* swap_chain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swap_chain_flags) {
	D2DUI::deinitRender();

	return original_resize_buffers(swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
}

void D2DHooks::InitD2D() {
	// the game prefers using D3D12 over D3D11, so we'll try to hook in that same order
	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		// Present and ResizeBuffers live at indexes 140 and 145 respectively
		kiero::bind(140, (void**)&original_present, PresentD3D);
		kiero::bind(145, (void**)&original_resize_buffers, ResizeBuffersD3D);
		Log("Hooked D3D12.");
		return;
	}

	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		// indexes are 8 and 13 for D3D11 instead
		kiero::bind(8, (void**)&original_present, PresentD3D);
		kiero::bind(13, (void**)&original_resize_buffers, ResizeBuffersD3D);
		Log("Hooked D3D11.");
		return;
	}

	// something weird happened
	Log("Failed to hook.");
}