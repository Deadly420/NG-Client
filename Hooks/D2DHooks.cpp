#include "D2DHooks.h"
#include "../Utils/D2DUtils.h"

typedef HRESULT(__thiscall* present_t)(IDXGISwapChain3*, UINT, UINT);
present_t original_present;

typedef HRESULT(__thiscall* resize_buffers_t)(IDXGISwapChain3*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
resize_buffers_t original_resize_buffers;

typedef HRESULT(__thiscall* draw_indexed_t)(ID3D11DeviceContext*, UINT, UINT, INT);
draw_indexed_t original_draw_indexed;

ID3D11Device* device;

HRESULT PresentD3D(IDXGISwapChain3* swap_chain, UINT sync_interval, UINT flags) {
	static bool once = false;
	if (!once) {
		ID3D12Device* bad_device;
		if (SUCCEEDED(swap_chain->GetDevice(IID_PPV_ARGS(&bad_device)))) {
			static_cast<ID3D12Device5*>(bad_device)->RemoveDevice();
			return original_present(swap_chain, sync_interval, flags);
		}
		once = true;
	}

	if (FAILED(swap_chain->GetDevice(IID_PPV_ARGS(&device))))
		return original_present(swap_chain, sync_interval, flags);

	// the game is now using D3D11
	D2DUI::initRendering(swap_chain);
	D2DUI::beginRender();

	// D2DUI::setFont(L"Comic Sans MS");
	// D2DUI::drawText(L"Fuck this shit - NRG", Vec2(100, 100), D2D1::ColorF(D2D1::ColorF::White), true, 20.0f);

	D2DUI::endRender();

	return original_present(swap_chain, sync_interval, flags);
}

HRESULT ResizeBuffersD3D(IDXGISwapChain3* swap_chain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swap_chain_flags) {
	D2DUI::deinitRender();

	return original_resize_buffers(swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
}

// Hook the DrawIndexed Function
HRESULT DrawIndexedD3D11(ID3D11DeviceContext* Context, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
	ID3D11Buffer* vertBuffer;
	UINT vertBufferOffset;
	UINT stride;

	Context->IAGetVertexBuffers(0, 1, &vertBuffer, &stride, &vertBufferOffset);
	if (stride == 24) {
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ID3D11DepthStencilState* depthStencil;
		UINT stencilRef;

		// get info about current depth stencil
		Context->OMGetDepthStencilState(&depthStencil, &stencilRef);
		depthStencil->GetDesc(&depthStencilDesc);
		depthStencilDesc.DepthEnable = false;  // disable depth to ignore all other geometry

		// create a new depth stencil based on current drawn one but with the depth disabled as mentioned before
		device->CreateDepthStencilState(&depthStencilDesc, &depthStencil);
		Context->OMSetDepthStencilState(depthStencil, stencilRef);

		// call original function
		original_draw_indexed(Context, IndexCount, StartIndexLocation, BaseVertexLocation);

		// release memory
		depthStencil->Release();

		return 0;
	}

	return original_draw_indexed(Context, IndexCount, StartIndexLocation, BaseVertexLocation);
}

void D2DHooks::InitD2D() {
	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		kiero::bind(140, (void**)&original_present, PresentD3D);
		kiero::bind(145, (void**)&original_resize_buffers, ResizeBuffersD3D);
	} else if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		kiero::bind(8, (void**)&original_present, PresentD3D);
		kiero::bind(13, (void**)&original_resize_buffers, ResizeBuffersD3D);
		kiero::bind(73, (void**)&original_draw_indexed, DrawIndexedD3D11);
	} else {
		Log("Failed to initialize hook for D2D");
	}
}