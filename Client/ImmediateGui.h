#pragma once

#include <map>

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "../Utils/DrawUtils.h"

class ComponentInfo {
public:
	ComponentInfo(int id);
	virtual ~ComponentInfo(){};

protected:
	unsigned int id;
};

class ButtonInfo : public ComponentInfo {
private:
	Vector2 pos;
	Vector2 size;
	bool centered;
	float padding = 3.f;
	bool canClickB = false;

public:
	ButtonInfo(int id, Vector2 pos, bool centered = false);
	virtual ~ButtonInfo(){};

	void calculateSize(const char*);
	bool isInSelectableSurface(Vector2 mouse);
	Vector4 getSelectableSurface();
	void draw(Vector2 mousePos, const char* label);
	bool canClick() { return canClickB; };
	void updatePos(Vector2 pos) { pos = pos; }
	
};

class ImmediateGui {
private:
	Vector2 mousePos;
	std::map<unsigned int, std::shared_ptr<ComponentInfo>> components;

public:
	void startFrame();
	bool Button(const char* label, Vector2 pos, bool centered = false);
};

extern ImmediateGui NG_Gui;