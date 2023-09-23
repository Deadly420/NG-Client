// MSVC doesn't like pragma once in pch (I think)
#ifndef PCH_H
#define PCH_H

// Windows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Standard library
#include <unordered_map>
#include <filesystem>
#include <algorithm>
#include <optional>
#include <iostream>
#include <cstdarg>
#include <sstream>
#include <fstream>
#include <Psapi.h>
#include <vector>
#include <string>
#include <chrono>
#include <map>

// Memory
#include "Memory/MinHook.h"
#include "Memory/SlimMem.h"

#include "include/imgui/imgui_impl_win32.h"
#include "include/imgui/imgui_impl_dx11.h"
#include "include/imgui/imgui_impl_dx12.h"
#include "include/kiero/kiero.h"

// include
#include "include/WinHttpClient.h"
#include "include/StringProcess.h"
#include "include/RegExp.h"
#include "include/atlrx.h"

// Utils
#include "Utils/VoxelIntersector.h"
#include "Utils/ChakraHelper.h"
#include "Utils/TextFormat.h"
#include "Utils/DllHelper.h"
#include "Utils/Logging.h"
#include "Utils/Json.hpp"
#include "Utils/Base64.h"
#include "Utils/HMath.h"
#endif