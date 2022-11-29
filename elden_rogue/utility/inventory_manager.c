#include "../screens/roundtable_screen.h"
#include "../screens/areas_screen.h"

#include "../driver.h"

#include "../config/settings.h"

#include "inventory_manager.h"

void addWeapon(Slot* pNewSlot, Slot** pInventoryHead) {
	
	Slot* pWeaponSlot = *pInventoryHead;
	int nWeaponsInInventory = 1;

	if (*pInventoryHead == NULL) {
		pNewSlot->sWeapon.nWeaponIndex = 1;
		*pInventoryHead = pNewSlot;
	}

	else {
		while(pWeaponSlot->pNext != NULL) {
			nWeaponsInInventory++;
			pWeaponSlot = pWeaponSlot->pNext;
		}

		pNewSlot->sWeapon.nWeaponIndex = nWeaponsInInventory + 1;
		pWeaponSlot->pNext = pNewSlot;
	}
}

void removeWeapon(Slot* pWeaponSlot, Slot** pInventoryHead) {
	
	if (pWeaponSlot == *pInventoryHead) {

		if(pWeaponSlot->pNext != NULL) {
			*pInventoryHead = pWeaponSlot->pNext;
		}
		else {
			*pInventoryHead = NULL;
		}

	} else {
		findWeaponSlot(pWeaponSlot->sWeapon.nWeaponIndex - 1, 
			*pInventoryHead)->pNext = pWeaponSlot->pNext;

	}
	
	free(pWeaponSlot);
}

void equipWeapon(Slot* pWeaponToEquip, Player* pPlayer) {
	Weapon sWeaponToEquip = pWeaponToEquip->sWeapon;

	pPlayer->sEquippedWeapon = sWeaponToEquip;
}

Slot* putWeaponInSlot(Weapon sWeapon) {
	Slot* pWeaponSlot = malloc(sizeof(Slot));

	pWeaponSlot->sWeapon = sWeapon;
	pWeaponSlot->pNext = NULL;

	return pWeaponSlot;
}

Slot* findWeaponSlot(int nIndex, Slot* pInventoryHead) {
	Slot* pWeaponSlot = pInventoryHead; // Provided variable, DO NOT REMOVE. But you MAY change the initialized value.

	int i;

	for(i = 0; i < nIndex; i++) {
		pWeaponSlot = pWeaponSlot->pNext;
	}

	return pWeaponSlot;
}

Slot* convertStockToSlot(Stock sStock) {
	Slot* pNewSlot = malloc(sizeof(Slot));

	pNewSlot->sWeapon = sStock.sWeapon;
	pNewSlot->pNext = NULL;

	return pNewSlot;
}