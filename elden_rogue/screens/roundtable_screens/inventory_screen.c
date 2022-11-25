#include "../title_screen.h"
#include "../chara_creation_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

//User Interface / Printing Functions 
void printInventorySlot(Weapon sWeapon) {

	int nSpaces = 2;

	int nLength = strlen(sWeapon.strWeaponName);

	printf("\n");

	// Print top border.
	printMultiple(" ", SCREEN_PADDING);
	printf("╔");
	printMultiple("═", SLOT_WIDTH);
	printf("╗\n");

	// Print Weapon Name.
	printMultiple(" ", SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%-*.*s", SLOT_WIDTH-4, nLength/2, sWeapon.strWeaponName);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName + nLength/2);
	printMultiple(" ", nSpaces);
	printf("│\n");

	//Print Weapon Image.
	printMultiple(" ", SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	//add weapon image
	printf("  <weapon>  ");
	printMultiple(" ", nSpaces);
	printf("│\n");

	//Print Weapon Index.
	printMultiple(" ", SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", SLOT_WIDTH-4, sWeapon.nWeaponIndex);
	printMultiple(" ", nSpaces);
	printf("│\n");

	// Print bottom border.
	printMultiple(" ", SCREEN_PADDING);
	printf("╚");
	printMultiple("═", SLOT_WIDTH);
	printf("╝\n");

	printf("\n");
}

void printInventoryGrid(Player* pPlayer) {

	Slot* pTempSlot = pPlayer->pInventory;
	Weapon* sWeapon = pTempSlot->sWeapon;
	Weapon* sEmpty = createEmptyWeapon();

	int nRowCounter = 0;
	int nColCounter = 0;

	printf("\n");

	//Print existing weapons in a 4x3 grid.
	//Traversing Linked List
	while (nRowCounter <= INVENTORY_MAX_ROWS) {

		while(nColCounter <= INVENTORY_MAX_COLS) {

			if (!strcmp(pTempSlot->sWeapon->strWeaponName, "NONE") || pTempSlot == NULL) { //only true if walang laman
				printInventorySlot(*sEmpty);
			} else {
				printInventorySlot(*sWeapon);

				pTempSlot = pTempSlot->pNext;
				sWeapon = pTempSlot->sWeapon;
			}
			nColCounter++;
		}
		nRowCounter++;
	}
}

void displayInventory(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("INVENTORY\n"
		"OPTIONS:\n");

	printInventoryGrid(pPlayer);

	printf("\n\n");
	printOption(1, "SELECT WEAPON");
	printOption(2, "PREVIOUS PAGE");
	printOption(3, "NEXT PAGE");
	printOption(0, "BACK");
	printf("\n\n");

	switch(nPrompt) {
		case SELECT:
			printf("You equipped %s.", pPlayer->pEquippedWeapon->strWeaponName);
			break;
		case NO_EXIST:
			printSystemMessage("There's no weapon at that index.");
			break;
	}

	printInputTag();
}

//Utility Functions
Weapon* findWeapon(int nInputIndex, Player* pPlayer) {

	Slot* pWeaponSlot = pPlayer->pInventory;
	Weapon* sWeapon = pWeaponSlot->sWeapon;
	
	while(sWeapon->nWeaponIndex != nInputIndex || pWeaponSlot != NULL) {
		pWeaponSlot = pWeaponSlot->pNext;
		sWeapon = pWeaponSlot->sWeapon;
	}

	return sWeapon;
}

Weapon* createEmptyWeapon() {
	
	Weapon* sWeapon;

	sWeapon->nWeaponIndex = 0;
	strcpy(sWeapon->strWeaponName, "NONE");

	sWeapon->nDexReq = 0;
	sWeapon->nHP = 0;
	sWeapon->nInt = 0;
	sWeapon->nEnd = 0;
	sWeapon->nStr = 0;
	sWeapon->nFth = 0;

	return sWeapon;
}

void sortInventory(Player* pPlayer) {
	
	Slot* sInventorySlot = pPlayer->pInventory;

	if (!strcmp(sInventorySlot->pNext->sWeapon->strWeaponName, "NONE")) {
		
		if (strcmp(sInventorySlot->pNext->pNext->sWeapon->strWeaponName, "NONE")) {
			
			while (sInventorySlot->pNext != NULL) {
				if (sInventorySlot->pNext->pNext != NULL)
					sInventorySlot->pNext->pNext->sWeapon->nWeaponIndex--;
				sInventorySlot->pNext = sInventorySlot->pNext->pNext;
				sInventorySlot = sInventorySlot->pNext;
			}
		}
	}

	//Store the sorted inventory in the Player Struct.
	pPlayer->pInventory = sInventorySlot;
}

void removeWeaponFromInventory(Weapon sWeapon, Player* pPlayer) {
	Slot* sInventorySlot = pPlayer->pInventory; //get the first weapon

	//Find the weapon and set it to slot.
	while (!strcmp(sInventorySlot->sWeapon->strWeaponName, sWeapon.strWeaponName) && 
			sInventorySlot->sWeapon->nWeaponIndex == sWeapon.nWeaponIndex) {
		sInventorySlot = sInventorySlot->pNext;
	}

	//Set the slot to empty.
	sInventorySlot->sWeapon = createEmptyWeapon();
	pPlayer->pInventory = sInventorySlot;

	//Remove empty spaces between items.
	sortInventory(pPlayer);
}

void addWeaponToInventory(Weapon* sWeapon, Player* pPlayer) {
	Slot* sInventorySlot = pPlayer->pInventory; //get the first weapon

	//Get the last inventory slot.
	while (sInventorySlot->pNext != NULL) {
		sInventorySlot = sInventorySlot->pNext;
	}

	//Set the next of the Last item to the removed equipped item.
	sInventorySlot->pNext->sWeapon = sWeapon;

	pPlayer->pInventory = sInventorySlot;

}

//Central Inventory Function
void openInventory(Player* pPlayer) {
	displayInventory(5, pPlayer);

	int nInputInventory = 100; //random value basta wala sa choices
	int nInputWeapon;

	Weapon* pSelectedWeapon;

	while(nInputInventory != 0) {

		nInputInventory = scanIntInput(0, 3); //Inventory Screen

		switch (nInputInventory) {

			case SELECT:
				scanf("%d", &nInputWeapon); //Input Weapon Index
				
				if (nInputWeapon != 0) 
					pSelectedWeapon = findWeapon(nInputWeapon, pPlayer); //Weapon to be equipped

				if (pSelectedWeapon != NULL) { //if the index the player inputted has a weapon

					addWeaponToInventory(pPlayer->pEquippedWeapon, pPlayer);
					pPlayer->pEquippedWeapon = pSelectedWeapon;
					//remove weapon from inventory
					//add previous equipped weapon to the end of inventory
					displayInventory(SELECT, pPlayer);

				} else {
					displayInventory(NO_EXIST, pPlayer);
				}

				break;

			case PREVIOUS:

				break;

			case NEXT:

				break;

			case I_BACK:

				break;


		}
	}
}