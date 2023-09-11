#pragma once
#include "../Module.h"
#include "../../../SDK/Attribute.h"

class AutoPot : public Module {
private:
	int health = 5;
	bool findPot() {
		PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
		Inventory* inv = supplies->inventory;
		auto prevSlot = supplies->selectedHotbarSlot;
		for (int n = 0; n < 9; n++) {
			ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (isPot(stack)) {
					if (prevSlot != n) {
						supplies->selectedHotbarSlot = n;
						MobEquipmentPacket p;
						p.hotbarSlot = n;
						Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);
					}
					return true;
				}
			}
		}
		return false;
	}
	bool isPot(ItemStack* itemStack) { return itemStack->getItem()->name.getText() == (std::string) "splash_potion"; }

public:
	AutoPot() : Module(0x0, Category::COMBAT, "Auto throws potions at the selected health") {
		registerIntSetting("Health", &health, health, 1, 20);
	}
	~AutoPot() {}

	virtual void onTick(GameMode* gm) override {
		// Atributes
		static HealthAttribute attribute = HealthAttribute();
		auto Health = Game.getLocalPlayer()->getAttribute(&attribute)->currentValue;
		auto HealthMax = Game.getLocalPlayer()->getAttribute(&attribute)->maximumValue;

		PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
		Inventory* inv = supplies->inventory;
		if (Game.getLocalPlayer()->isAlive() && Game.isInGame()) {
			if (!Game.getLocalPlayer()->canOpenContainerScreen()) {
				int slot;
				int potSlot;
				for (int n = 0; n < 36; n++) {
					ItemStack* stack = inv->getItemStack(n);
					if (stack->item != nullptr && isPot(stack)) {
						auto PotSlot = inv->getFirstEmptySlot();
						potSlot = PotSlot;
						slot = n;
					}
				}
				if (slot != 0) {
					inv->swapSlots(slot, potSlot);
				}
			}

			// checks if it can throw yet
			if (Health < health) {
				findPot();

				// Rots to look down
				float rotChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.f)) + 1.f;
				LocalPlayer* player = Game.getLocalPlayer();
				MovePlayerPacket mpp(player, *player->getPos());
				mpp.pitch = 90.f - rotChange;
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
				Level* level = Game.getLocalPlayer()->level;

				bool idk = true;
				gm->buildBlock(new Vec3i(level->block), level->blockSide, idk);
			}
		}
	}
	const char* getModuleName() override {
		return "AutoPot";
	}
	std::string getModSettings() {
		return "HP: " + std::to_string(health);
	}
};