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

void printInventoryGrid(Player* pPlayer, int nPage) {

	Slot* pTempSlot = pPlayer->pInventory;
	Weapon* pWeapon = pTempSlot->pWeapon;
	Weapon* pEmpty = createEmptyWeapon();

	int nRowCounter = 0;
	int nColCounter = 0;

	printf("\n");

	//Print existing weapons in a 4x3 grid.
	//Traversing Linked List
	while (nRowCounter*nPage <= INVENTORY_MAX_ROWS*nPage) {

		while(nColCounter*nPage <= INVENTORY_MAX_COLS*nPage) {

			if (!strcmp(pTempSlot->pWeapon->strWeaponName, "NONE") || pTempSlot == NULL) { //only true if walang laman
				printInventorySlot(*pEmpty);
			} else {
				printInventorySlot(*pWeapon);

				pTempSlot = pTempSlot->pNext;
				pWeapon = pTempSlot->pWeapon;
			}
			nColCounter++;
		}
		nRowCounter++;
	}
}

void displayInventory(int nPrompt, Player* pPlayer, int nPage) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\t\tINVENTORY\n\n"
		"OPTIONS:\n");

	printInventoryGrid(pPlayer, nPage);

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
		default:
			break;
	}

	printInputTag();
}

//Utility Functions
Weapon* findWeapon(int nInputIndex, Player* pPlayer) {

	Slot* pWeaponSlot = pPlayer->pInventory;
	Weapon* pWeapon = pWeaponSlot->pWeapon;
	
	while(pWeapon->nWeaponIndex != nInputIndex || pWeaponSlot != NULL) {
		pWeaponSlot = pWeaponSlot->pNext;
		pWeapon = pWeaponSlot->pWeapon;
	}

	return pWeapon;
}

Weapon* createEmptyWeapon() {
	
	Weapon* pWeapon = malloc(sizeof(Weapon));

	pWeapon->nWeaponIndex = 0;
	strcpy(pWeapon->strWeaponName, "NONE");
	pWeapon->nWeaponType = 0;

	pWeapon->nDexReq = 0;
	pWeapon->nHP = 0;
	pWeapon->nInt = 0;
	pWeapon->nEnd = 0;
	pWeapon->nStr = 0;
	pWeapon->nFth = 0;

	return pWeapon;
}

void sortInventory(Player* pPlayer) {
	
	Slot* sInventorySlot = pPlayer->pInventory;

	if (!strcmp(sInventorySlot->pNext->pWeapon->strWeaponName, "NONE")) {
		
		if (strcmp(sInventorySlot->pNext->pNext->pWeapon->strWeaponName, "NONE")) {
			
			while (sInventorySlot->pNext != NULL) {
				if (sInventorySlot->pNext->pNext != NULL)
					sInventorySlot->pNext->pNext->pWeapon->nWeaponIndex--;
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
	while (!strcmp(sInventorySlot->pWeapon->strWeaponName, sWeapon.strWeaponName) && 
			sInventorySlot->pWeapon->nWeaponIndex == sWeapon.nWeaponIndex) {
		sInventorySlot = sInventorySlot->pNext;
	}

	//Set the slot to empty.
	sInventorySlot->pWeapon = createEmptyWeapon();
	pPlayer->pInventory = sInventorySlot;

	//Remove empty spaces between items.
	sortInventory(pPlayer);
}

void addWeaponToInventory(Weapon* pWeapon, Player* pPlayer) {
	Slot* sInventorySlot = pPlayer->pInventory; //get the first weapon

	//Get the last inventory slot.
	while (sInventorySlot->pNext != NULL) {
		sInventorySlot = sInventorySlot->pNext;
	}

	//Set the next of the Last item to the removed equipped item.
	sInventorySlot->pNext->pWeapon = pWeapon;
	//Set the index of the new item.
	sInventorySlot->pNext->pWeapon->nWeaponIndex = sInventorySlot->pWeapon->nWeaponIndex + 1;

	//Update the player's inventory.
	pPlayer->pInventory = sInventorySlot;
}

int getPlayerWeapons(Player* pPlayer) {
	int nPlayerWeapons = 0;

	Slot* sInventorySlot = pPlayer->pInventory; //get the first weapon

	//Get the last inventory slot.
	while (sInventorySlot != NULL) {
		sInventorySlot = sInventorySlot->pNext;
		nPlayerWeapons++;
	}

	return nPlayerWeapons;
}

//Central Inventory Function
void openInventory(Player* pPlayer) {

	int nInputInventory = 100; //random value basta wala sa choices
	int nInputWeapon;
	int nPlayerWeapons = getPlayerWeapons(pPlayer);
	int nTemp;
	int nPage = 1;

	Weapon* pSelectedWeapon;

	displayInventory(5, pPlayer, nPage);

	while(nInputInventory != 0) {

		nInputInventory = scanIntInput(0, 3); //Inventory Screen
		nPlayerWeapons = getPlayerWeapons(pPlayer);

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
					displayInventory(SELECT, pPlayer, nPage);

				} else {
					displayInventory(NO_EXIST, pPlayer, nPage);
				}

				break;

			case PREVIOUS:
				if (nPage > 1) 
					nPage--;
				break;

			case NEXT:

				nTemp = nPlayerWeapons / 12;

				if (nPlayerWeapons % 12 != 0)
					nTemp++;

				if (nPage < nTemp)
					nPage++;

				break;

			case I_BACK:

				openRoundTableHoldScreen(pPlayer);
				break;


		}
	}
}