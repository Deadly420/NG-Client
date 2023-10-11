#include "EditionFaker.h"

EditionFaker::EditionFaker() : Module(0x0, Category::MISC, "Fakes your device.") {
	registerEnumSetting("Edition", &edition, 1, "Select the game edition to use.");
	edition.addEntry("Unknown", 0);
	edition.addEntry("Android", 1);
	edition.addEntry("iOS", 2);
	edition.addEntry("macOS", 3);  // OS_X
	edition.addEntry("FireOS", 4);
	edition.addEntry("GearVR", 5);
	edition.addEntry("Hololens", 6);
	edition.addEntry("Win10", 7);  // Windows 10 (PC)
	edition.addEntry("Win32", 8);  // Windows
	edition.addEntry("Linux", 9);  // Dedicated
	edition.addEntry("TvOS", 10);
	edition.addEntry("Playstation", 11);  // Orbis
	edition.addEntry("Nintendo Switch", 12);  // NX
	edition.addEntry("Xbox", 13);
	edition.addEntry("Windows Phone", 14);
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	return edition.GetSelectedEntry().GetValue();
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}

std::string EditionFaker::getModSettings() {
	return edition.GetSelectedEntry().GetName();
}