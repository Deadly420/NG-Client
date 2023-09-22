#include "InventoryTransaction.h"
#include "../Utils/Utils.h"
void InventoryTransactionManager::addInventoryAction(const InventoryAction& action, bool idk) {
	static auto InventoryTransactionManager__addAction = Utils::FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 83 EC ? 45 ? ? F8 4C 8B F2 48 8B F9");
	if (InventoryTransactionManager__addAction)
		reinterpret_cast<void(__fastcall*)(InventoryTransactionManager*, const InventoryAction&, bool)>(InventoryTransactionManager__addAction)(this, action, idk);
}

void InventoryAction::fixInventoryStuff(ItemDescriptor* a1, ItemStack* a2) {
	static auto fixInvStuff = Utils::FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 ? ? 48 8B FA 48 8B F1 48 89 4C ? ? ? ? 5A 22");
	if (fixInvStuff)
		reinterpret_cast<void(__fastcall*)(ItemDescriptor*, ItemStack*)>(fixInvStuff)(a1, a2);
}