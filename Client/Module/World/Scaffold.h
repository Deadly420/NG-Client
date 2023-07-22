#pragma once
#include "../Module.h"
class Scaffold : public Module {
private:
	bool autoSelect = false;
	bool down = false;
	bool highlight = true;
	bool hive = false;
	bool rotations = true;
	int extend = 0;
	bool Ylock = false;
	bool Count = false;
	float scY = 20.f;
	float scX = 10.f;
	bool tryScaffold(Vector3 blockBelow);
	bool tryClutchScaffold(Vector3 blockBelow);
	bool findBlock();
	float YCoord;

public:
	Scaffold();
	~Scaffold(){};

	void handleScaffoldDown(Player* player, float speed, const Vector3& velocity);
	void handleScaffoldUp(Player* player, float speed, const Vector3& velocity);
	Vector3 getBlockBelow(Player* player, float yOffset);
	void adjustYCoordinate(Vector3& blockBelow, const Vector3& blockBelowReal);
	void extendBlock(Player* player, const Vector3& velocity, Vector3& blockBelow);
	void attemptScaffoldWhileMoving(Player* player, float speed, const Vector3& velocity, Vector3& blockBelow, Vector3& blockBelowBelow);
	void handleReplaceableBlock(Player* player, float speed, const Vector3& velocity, Vector3& blockBelow);
	void handleNonReplaceableBlock(Player* player, float speed, const Vector3& velocity, Vector3& blockBelow);
	Vector3 getNextBlock(Player* player, const Vector3& velocity, const Vector3& blockBelow);

	virtual const char* getModuleName() {
		return "Scaffold";
	};
	virtual void onEnable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;
		float yPos = player->eyePos0.y;  // Block 1 block below the player
		yPos -= player->height;
		yPos -= 0.5f;
		YCoord = yPos;
	};
	virtual void onPostRender(MinecraftUIRenderContext* ctx) override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onPlayerTick(Player* player) override;
};
