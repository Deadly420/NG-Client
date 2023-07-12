#pragma once
#include "../../../Client/Module/Module.h"
class EntityJesus : public Module {
private:
	bool wasInWater = false;
	float upness = 0.01f;

public:
	EntityJesus();
	~EntityJesus();
	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onLevelRender() override;
};