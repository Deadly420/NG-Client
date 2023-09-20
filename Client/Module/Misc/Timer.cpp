#include "Timer.h"

Timer::Timer() : Module(0x0, Category::MISC, "Increase the ticks per second.") {
	registerIntSetting("TPS", &timer, timer, 0, 500, "TPS: Set the Ticks Per Second (TPS) value from 0 to 500");
}

Timer::~Timer() {
}

const char* Timer::getModuleName() {
	return ("Timer");
}

void Timer::onTick(GameMode* gm) {
	Game.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
}

void Timer::onDisable() {
	Game.getClientInstance()->minecraft->setTimerSpeed(20.f);
}