// MSVC doesn't like pragma once in pch (I think)
#ifndef PCH_H
#define PCH_H

// Windows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Standard library
#include <Psapi.h>

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Memory
#include "Memory/MinHook.h"
#include "Memory/SlimMem.h"

// Utils
#include "Utils/Base64.h"
#include "Utils/ChakraHelper.h"
#include "Utils/DllHelper.h"
#include "Utils/HMath.h"
#include "Utils/Json.hpp"
#include "Utils/Logger.h"
#include "Utils/TextFormat.h"
#include "Utils/VoxelIntersector.h"
#endif