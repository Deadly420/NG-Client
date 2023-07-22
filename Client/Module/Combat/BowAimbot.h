#pragma once
#include "../Module.h"
class BowAimbot : public Module {
public:
	BowAimbot();
	~BowAimbot();

	bool silent = true;
	bool predict = false;
	bool visualize = false;
	Vector2 angle;

	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onSendPacket(Packet* packet) override;
};