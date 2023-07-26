#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "../Module.h"

class FightBot : public Module {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = true;
	void findWeapon();
	bool silent = true;

public:
	int targ = 100;
	bool noSwing = false;
	bool isMulti = true;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	bool targetListA = false;
	bool sexy = true;
	Vec2 joe;

	FightBot();
	~FightBot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onSendPacket(Packet* packet) override;
};