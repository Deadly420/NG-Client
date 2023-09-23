#pragma once

#include <mutex>
#include <vector>
#include <memory>

#ifdef _DEBUG
#include <ios>
#include <iosfwd>
#include <iostream>
#endif

#include "xorstr.h"
#include <string>

#pragma comment(lib, "runtimeobject")

#ifndef Log
#define Log(x, ...) Logger::WriteLogs(XorString(x), __VA_ARGS__)
#endif

struct TextForPrint {
	char time[20];
	char text[100];
};

struct TextForPrintBig {
	char time[20];
	char text[2900];
};

class Logger {

public:
	static bool isActive();
	static std::wstring GetRoamingFolderPath();
	static void WriteLogs(volatile char* fmt, ...);
	static std::vector<TextForPrint>* GetTextToPrint();
	static std::vector<std::shared_ptr<TextForPrintBig>>* GetTextToSend();
	static std::lock_guard<std::mutex> GetTextToPrintLock();
	//static std::vector<TextForPrint*> stringPrintVector;
	static void Disable();
};
