#include "../title_screen.h"
#include "../chara_creation_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openInventory		Opens the Inventory of the Player.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openInventory(Player* pPlayer) {

	// Input Variables
	int nInputInventory = 100; //random value basta wala sa choices
	int nInputWeapon;

	// Get the amount of Weapons the Player has.
	int nPlayerWeapons = getPlayerWeapons(pPlayer);
	
	// Temporary Variables
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



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/* 	findWeapon			Finds the weapon using a given index inside the 
						Player's Inventory.

	@param	nInputIndex	An integer variable containing the Index of the 
						Weapon the Player chose from the Inventory.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	@return				A pointer of type Weapon.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
Weapon* findWeapon(int nInputIndex, Player* pPlayer) {

	Slot* pWeaponSlot = pPlayer->pInventory;
	Weapon* pWeapon = pWeaponSlot->pWeapon;
	
	while(pWeapon->nWeaponIndex != nInputIndex || pWeaponSlot != NULL) {
		pWeaponSlot = pWeaponSlot->pNext;
		pWeapon = pWeaponSlot->pWeapon;
	}

	return pWeapon;
}

/* 	createEmptyWeapon	Creates an instance of an empty Weapon.

	@return				A pointer of type Weapon.					   */
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

/* 	sortInventory		Fills in empty spaces in between items in the
						Player's Inventory by moving items back to fill 
						the gap.

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
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

/* 	removeWeaponFromInventory	asdsadasdasd

	@param	pPlayer				The Player Structure containing all of 
								the Player's statistics and items.

	Pre-condition				pPlayer should be initiated and all 
								members should have a value.		   */
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

	Slot* pInventorySlot = pPlayer->pInventory; //get the first weapon

	if (strcmp(pInventorySlot->pWeapon->strWeaponName, "NONE")) {
		//Get the last inventory slot.
		while (pInventorySlot != NULL) {
			pInventorySlot = pInventorySlot->pNext;
			nPlayerWeapons++;
		}
	}
	
	return nPlayerWeapons;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
void printTopBorderSlots(int nCols) {

	int i;

	for (i = 0; i < nCols; i++) {
		printMultiple(" ", SCREEN_PADDING);
		printf("╔");
		printMultiple("═", SLOT_WIDTH);
		printf("╗");
	}

	printf("\n");
}

void printBottomBorderSlots(int nCols) {

	int i;

	for (i = 0; i < nCols; i++) {
		printMultiple(" ", SCREEN_PADDING);
		printf("╚");
		printMultiple("═", SLOT_WIDTH);
		printf("╝");
	}

	printf("\n");
}

void printContentSlots(int nCols, Slot* pInventoryHead) {

	int i;
	int nSpaces = 2;
	Slot* pTempHead = pInventoryHead; // Stores the Head so as not to alter it.
	Weapon sWeapon = *(pTempHead->pWeapon); // Gets the weapon from the head.

	// FIRST LINE -------------------------------------------------------
	// Print the Weapon Name first line.
	for (i = 0; i < nCols; i++) {

		sWeapon = *(pTempHead->pWeapon); // Resets the Weapon after every run.

		printMultiple(" ", SCREEN_PADDING);
		printf("│");
		printMultiple(" ", nSpaces);
		printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName);
		printMultiple(" ", nSpaces);
		printf("│");

		pTempHead = pTempHead->pNext; // Move to the next item.
	}

	printf("\n");


	// SECOND LINE ------------------------------------------------------
	pTempHead = pInventoryHead; //reset the head.

	// Print the Weapon Name first line.
	for (i = 0; i < nCols; i++) {

		sWeapon = *(pTempHead->pWeapon); // Resets the Weapon after every run.

		printMultiple(" ", SCREEN_PADDING);
		printf("│");
		printMultiple(" ", nSpaces);
		printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName + SLOT_WIDTH-4);
		printMultiple(" ", nSpaces);
		printf("│");

		pTempHead = pTempHead->pNext; // Move to the next item.
	}

	printf("\n");


	// THIRD LINE ------------------------------------------------------
	pTempHead = pInventoryHead; //reset the head.

	// Print the Weapon Name first line.
	for (i = 0; i < nCols; i++) {

		sWeapon = *(pTempHead->pWeapon); // Resets the Weapon after every run.

		printMultiple(" ", SCREEN_PADDING);
		printf("│");
		printMultiple(" ", nSpaces);
		//add weapon image
		printf("  <weapon>  ");
		printMultiple(" ", nSpaces);
		printf("│");

		pTempHead = pTempHead->pNext; // Move to the next item.
	}

	printf("\n");


	// FOURTH LINE ------------------------------------------------------
	pTempHead = pInventoryHead; //reset the head.

	// Print the Weapon Name first line.
	for (i = 0; i < nCols; i++) {

		sWeapon = *(pTempHead->pWeapon); // Resets the Weapon after every run.

		printMultiple(" ", SCREEN_PADDING);
		printf("│");
		printMultiple(" ", nSpaces);
		printf("%*d", SLOT_WIDTH-4, sWeapon.nWeaponIndex);
		printMultiple(" ", nSpaces);
		printf("│");

		pTempHead = pTempHead->pNext; // Move to the next item.
	}

	printf("\n");
}

void printEmptySlots(int nCols) {
	
	int i, j;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < nCols; i++) {

			printMultiple(" ", SCREEN_PADDING);
			printf("│");
			printMultiple(" ", SLOT_WIDTH);
			printf("│");

		}

		printf("\n");
	}
}

void printInventoryGrid(Player* pPlayer, int nPage) {

	// Contains the values need to be printed.
	Slot* pInventoryHead = pPlayer->pInventory; // Head of the inventory.
	Weapon* pEmpty = createEmptyWeapon(); // Empty instance to fill.

	int i, j, k; // Counts the rows, columns, and offsets the head.

	// Page numbers start at 1. So, offset the Head by 20 for every additional page.
	// nPage - 1 because at the first page (nPage = 1), the condition will be false 
	// at and there won't be any offset.
	for (k = 0; k < 20 * (nPage-1); k++) {
		pInventoryHead = pInventoryHead->pNext;
	}

	printf("\n");

	//Print existing weapons in a 5x4 grid.
	for(i = 0; i < INVENTORY_MAX_ROWS; i++) {

		printTopBorderSlots(INVENTORY_MAX_COLS);

		for (j = 0; j < INVENTORY_MAX_COLS; j++) {

			// First check if the inventory is NOT empty.
			if (strcmp(pInventoryHead->pWeapon->strWeaponName, "NONE") && 
				pInventoryHead != NULL) {

				printf("(debugging)");
				// If inventory is NOT empty, print the weapon info.				
				printContentSlots(INVENTORY_MAX_COLS, pInventoryHead);
				pInventoryHead = pInventoryHead->pNext;
			} 
			// If there's no weapon in the slot, print empty.
			else {
				printEmptySlots(INVENTORY_MAX_COLS);
			}
		}

		printBottomBorderSlots(INVENTORY_MAX_COLS);
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