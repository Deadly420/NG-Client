#pragma once

#include <d2d1_1.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dwrite_1.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <initguid.h>

#include "../Utils/Logging.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_dx11.h"
#include "../include/imgui/imgui_impl_dx12.h"
#include "../include/imgui/imgui_impl_win32.h"
#include "../Client/Manager/ModuleManager.h"
#include "../include/kiero/kiero.h"
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

// windows related includes
#include <windows.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_4.h>

// standard includes
#include <stdio.h>
#include <thread>

class DXHook {
public:
	static void InitImGui();
};