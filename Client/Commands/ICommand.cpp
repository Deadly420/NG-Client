#include "ICommand.h"
#include <cstdarg>
#include <string>
#include <vector>

Command::Command(const char* command, const char* description, const char* usage) {
	_command = command;
	_description = description;
	_usage = usage;
	registerAlias(command);
}

Command::~Command() {
}

void Command::clientMessage(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	Game.getGuiData()->displayClientMessageVA(fmt, arg);
	va_end(arg);
}

void Command::registerAlias(const char* str) {
	std::string ss = str;
	std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	aliasList.push_back(ss);
}
