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

// Libraries
#include "Memory/MinHook.h"
#include "Memory/SlimMem.h"
#include "Utils/Json.hpp"

#endif