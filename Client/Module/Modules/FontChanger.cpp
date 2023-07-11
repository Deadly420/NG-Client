#include "FontChanger.h"

FontChanger::FontChanger() : Module(0, Category::HUD, "Font Changer.") {
	Fonts.addEntry(EnumEntry("Notosans", 0)).addEntry(EnumEntry("Mojangles", 1));
	registerEnumSetting("Fonts", &Fonts, 0);
}

FontChanger::~FontChanger() {
}

const char* FontChanger::getModuleName() {
	return ("CustomFont");
}