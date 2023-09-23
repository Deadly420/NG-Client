#include "Logger.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include "Utils.h"

#include <sstream>
#include <windows.storage.h>
#include <wrl.h>

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

char logPath[200];
bool initializedLogger = false;
bool loggerActive = true;
CRITICAL_SECTION loggerLock;
std::mutex vecMutex;
std::mutex injMutex;
std::vector<TextForPrint> stringPrintVector = std::vector<TextForPrint>();
std::vector<std::shared_ptr<TextForPrintBig>> stringSendToInjector;

bool Logger::isActive() {
	return loggerActive && initializedLogger;
}

std::wstring Logger::GetRoamingFolderPath() {
	ComPtr<IApplicationDataStatics> appDataStatics;
	auto hr = RoGetActivationFactory(HStringReference(L"Windows.Storage.ApplicationData").Get(), __uuidof(appDataStatics), &appDataStatics);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve application data statics");

	ComPtr<IApplicationData> appData;
	hr = appDataStatics->get_Current(&appData);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve current application data");

	ComPtr<IStorageFolder> roamingFolder;
	hr = appData->get_RoamingFolder(&roamingFolder);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder");

	ComPtr<IStorageItem> folderItem;
	hr = roamingFolder.As(&folderItem);
	if (FAILED(hr)) throw std::runtime_error("Failed to cast roaming folder to IStorageItem");

	HString roamingPathHString;
	hr = folderItem->get_Path(roamingPathHString.GetAddressOf());
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder path");

	uint32_t pathLength;
	auto roamingPathCStr = roamingPathHString.GetRawBuffer(&pathLength);
	return std::wstring(roamingPathCStr, pathLength);
}

void Logger::WriteLogs(volatile char* fmt, ...) {
	if (!loggerActive)
		return;
	FILE* pFile;

	if (!initializedLogger) {
		initializedLogger = true;
		InitializeCriticalSection(&loggerLock);
		EnterCriticalSection(&loggerLock);


		std::wstring roam = GetRoamingFolderPath();
		sprintf_s(logPath, 200, "%S\\NG\\logs.txt", roam.c_str());

		try {
			remove(logPath);
		} catch (std::exception e) {
		}

	} else
		EnterCriticalSection(&loggerLock);

	pFile = _fsopen(logPath, "a", _SH_DENYWR);  // Open File with DENY_WRITE so other programs can only read stuff from log
	if (pFile != nullptr) {
		std::stringstream ssTime;
		Utils::ApplySystemTime(&ssTime);

		char logMessage[500];
		char timeStamp[20];
		sprintf_s(timeStamp, 20, "%s", ssTime.str().c_str());

		va_list arg;
		va_start(arg, fmt);
		int numCharacters = vsprintf_s(logMessage, 300, const_cast<const char*>(fmt), arg);
		va_end(arg);
		fprintf(pFile, "%s%s", timeStamp, logMessage);
		fprintf(pFile, "\n");

		fclose(pFile);

		if (numCharacters < 100) {
			TextForPrint textForPrint;
			strcpy_s(textForPrint.text, 100, logMessage);
			strcpy_s(textForPrint.time, 20, timeStamp);
			auto lock = Logger::GetTextToPrintLock();
			stringPrintVector.push_back(textForPrint);
		}
	}
	LeaveCriticalSection(&loggerLock);
}

std::vector<TextForPrint>* Logger::GetTextToPrint() {
	return &stringPrintVector;
}

std::vector<std::shared_ptr<TextForPrintBig>>* Logger::GetTextToSend() {
	return &stringSendToInjector;
}

std::lock_guard<std::mutex> Logger::GetTextToPrintLock() {
	return std::lock_guard<std::mutex>(vecMutex);
}

void Logger::Disable() {
	loggerActive = false;
#ifdef _DEBUG
	EnterCriticalSection(&loggerLock);
	auto lock = Logger::GetTextToPrintLock();
	LeaveCriticalSection(&loggerLock);
	Sleep(50);

	DeleteCriticalSection(&loggerLock);
#endif
}
