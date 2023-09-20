#include "NoHurtcam.h"

NoHurtcam::~NoHurtcam() {}
NoHurtcam::NoHurtcam() : Module(0x0, Category::RENDER, "Disables rotation of the camera when hit.") {}
const char* NoHurtcam::getModuleName() {
	return "NoHurtcam";
}
