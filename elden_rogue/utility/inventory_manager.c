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
	
	Slot* pPrevWeaponSlot;

	if (pWeaponSlot == *pInventoryHead) {

		if(pWeaponSlot->pNext != NULL) {
			*pInventoryHead = pWeaponSlot->pNext;

			while (pWeaponSlot != NULL) {
				pWeaponSlot->sWeapon.nWeaponIndex--;
				pWeaponSlot = pWeaponSlot->pNext;
			}
		}
		else {
			*pInventoryHead = NULL;
		}

	} else {
		pPrevWeaponSlot = findWeaponSlot(pWeaponSlot->sWeapon.nWeaponIndex-1, *pInventoryHead);
		pPrevWeaponSlot->pNext = pWeaponSlot->pNext;

		pPrevWeaponSlot = pPrevWeaponSlot->pNext;
		
		while (pPrevWeaponSlot != NULL) {
			pPrevWeaponSlot->sWeapon.nWeaponIndex--;
			pPrevWeaponSlot = pPrevWeaponSlot->pNext;
		}
	}
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
	Slot* pWeaponSlot = pInventoryHead; 

	while (pWeaponSlot != NULL) {

		if(pWeaponSlot->sWeapon.nWeaponIndex == nIndex) {
			return pWeaponSlot;
		}

		pWeaponSlot = pWeaponSlot->pNext;
	}

	return NULL;
}

Slot* convertStockToSlot(Stock sStock) {
	Slot* pNewSlot = malloc(sizeof(Slot));

	pNewSlot->sWeapon = sStock.sWeapon;
	pNewSlot->pNext = NULL;

	return pNewSlot;
}