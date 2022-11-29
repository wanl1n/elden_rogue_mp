#ifndef INVENTORY_MANAGER
#define INVENTORY_MANAGER

void addWeapon(Slot* pNewSlot, Slot** pInventoryHead);
void removeWeapon(Slot* pWeaponSlot, Slot** pInventoryHead);
Slot* findWeaponSlot(int nIndex, Slot* pInventoryHead);
void equipWeapon(Slot* pWeaponToEquip, Player* pPlayer);
Slot* putWeaponInSlot(Weapon sWeapon);

#endif
