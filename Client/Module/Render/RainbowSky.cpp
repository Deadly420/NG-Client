#include "RainbowSky.h"

float RainbowSky::red{0};
float RainbowSky::green{0};
float RainbowSky::blue{0};
bool RainbowSky::custom{false};

RainbowSky::RainbowSky() : Module(0x0, Category::RENDER, "Chages the colour of the sky") {
	registerFloatSetting("Red", &red, red, 0, 1, "Red: Adjust the red component from 0 to 1");
	registerFloatSetting("Green", &green, green, 0, 1, "Green: Adjust the green component from 0 to 1");
	registerFloatSetting("Blue", &blue, blue, 0, 1, "Blue: Adjust the blue component from 0 to 1");
	registerBoolSetting("Rainbow", &custom, custom);
	registerFloatSetting("intensity", &intensity, intensity, 0.01f, 0.1f, "Intensity: Set the intensity from 0.01 to 0.1");
}

RainbowSky::~RainbowSky() {
}

const char* RainbowSky::getModuleName() {
	return ("CustomSky");
}