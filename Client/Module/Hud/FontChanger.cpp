#include "FontChanger.h"

FontChanger::FontChanger() : Module(0x0, Category::HUD, "Font Changer.") {
	Fonts.addEntry(EnumEntry("Notosans", 0)).addEntry(EnumEntry("Mojangles", 1));
	registerEnumSetting("Fonts", &Fonts, 0, "Fonts: Choose the font for your application.");
}

FontChanger::~FontChanger() {
}

const char* FontChanger::getModuleName() {
	return ("CustomFont");
}