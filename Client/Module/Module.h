#pragma once

#include "../../Memory/GameData.h"
#include "../Manager/FriendsManager.h"
#include "../../Utils/keys.h"

class Module;

enum class Category {
	COMBAT = 0,
	RENDER = 1,
	MOVEMENT = 2,
	PLAYER = 3,
	ENTITY = 4,
	MISC = 5,
	WORLD = 6,
	HUD = 7
};

struct EnumEntry {
private:
	/*const */ std::string name;
	/*const */ unsigned char val;

public:
	/// <summary>Use this however you want</summary>
	void* ptr = nullptr;
	EnumEntry(const std::string _name, const unsigned char value);
	std::string GetName();
	unsigned char GetValue();
};

struct AddResult;

class SettingEnum {
private:
	Module* owner = nullptr;

public:
	std::vector<EnumEntry> Entrys;
	int selected = -1;

	SettingEnum(std::vector<EnumEntry> entr, Module* mod = nullptr);
	SettingEnum(Module* mod = nullptr);
	//SettingEnum();
	SettingEnum& addEntry(EnumEntry entr);
	SettingEnum& addEntry(const char* name, int value);
	EnumEntry& GetEntry(int ind);
	EnumEntry& GetSelectedEntry();
	int getSelectedValue();
	int GetCount();
};

enum class ValueType {
	FLOAT,
	DOUBLE,
	INT64,
	INT,
	BOOL,
	TEXT,
	ENUM
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		bool _bool;
		std::string* text;
		SettingEnum* Enum;
	};
};

struct SettingEntry {
	char name[0x20] = "";
	char tooltip[255];  // Added tooltip field
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	void* extraData; // Only used by enum for now

	// ClickGui Data
	bool isDragging = false;  // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done

	void makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
};

class Module {
private:
	bool enabled = false;
	int keybind = 0x0;
	bool extended = false;
	Vec2 ModulePos;
private:
	Category category;
	const char* tooltip;

	std::vector<SettingEntry*> settings;

protected:
	Module(int key, Category cat, const char* tooltip);

	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue, const char* tooltip);
	void registerIntSetting(std::string name, int* intPtr, int defaultValue, int minValue, int maxValue, const char* tooltip);
	void registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue, const char* tooltip);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue, const char* tooltip);

	void clientMessage(const char* fmt, ...);

public:
	virtual ~Module();

	const Category getCategory() { return category; };

	inline Vec2* getPos() { return &ModulePos; };

	inline std::vector<SettingEntry*>* getSettings() { return &settings; };

	virtual const char* getModuleName() = 0;
	virtual const char* getRawModuleName();
	virtual std::string getModSettings();
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual bool allowAutoStart();
	virtual void onWorldTick(GameMode*);
	virtual void onTick(GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onKey(int key, bool isDown, bool& shouldCancel);
	virtual void onEnable();
	virtual void onDisable();
	virtual void onAttack(Entity*);
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx);
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx);
	virtual void onLevelRender();
	virtual void onMove(MoveInputHandler*);
	virtual void onPlayerTick(Player*);
	virtual void onImGuiRender();
	virtual void onLoadConfig(void* conf);
	virtual void onSaveConfig(void* conf);
	virtual bool isFlashMode();
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
	virtual void onSendPacket(Packet*);
	virtual void onSendClientPacket(Packet*);
	virtual bool callWhenDisabled();
	const char* getTooltip();
	virtual void onBaseTick(Entity*) {}
};