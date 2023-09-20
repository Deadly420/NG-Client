#pragma once

#include "../Module.h"
#include <set>

class NameTags : public Module {
public:
	std::set<std::string> nameTags;
	bool displayArmor = true;
	bool underline = true;
	float opacity = 0.2f;
	NameTags();
	~NameTags();

	bool* ingameNametagSetting = nullptr;
	bool lastSetting = true;
	bool gotPrevSetting = false;

	// Inherited via Module
	virtual const char* getModuleName() override;
	static void drawNameTags(Entity* ent, float textSize);
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
};
