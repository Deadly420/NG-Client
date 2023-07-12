#pragma once
#include "../Module.h"
class EntitySpider : public Module {
public:
	float speed = 0.6f;
	bool dontOvershoot = true;

	EntitySpider();
	~EntitySpider();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
};