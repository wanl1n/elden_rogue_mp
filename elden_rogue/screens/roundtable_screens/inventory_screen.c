#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"
#include "../../utility/inventory_manager.h"



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openInventory		Opens the Inventory of the Player.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
// void openInventory(Player* pPlayer) {

// 	// Input Variables
// 	int nInputInventory = 100; //random value basta wala sa choices
// 	int nInputWeapon;

// 	// Get the amount of Weapons the Player has.
// 	int nPlayerWeapons = getPlayerWeapons(pPlayer);
	
// 	// Temporary Variables
// 	int nTemp;
// 	int nPage = 1;

// 	Weapon* pSelectedWeapon = NULL;

// 	displayInventory(5, pPlayer, nPage);

// 	while(nInputInventory != 0) {

// 		nInputInventory = scanIntInput(0, 3); // Contains the Player's choice.
// 		nPlayerWeapons = getPlayerWeapons(pPlayer);

// 		switch (nInputInventory) {
			
// 			case SELECT:

// 				// Ask Player which weapon they want by inputting index.
// 				printInputTag();
// 				scanf("%d", &nInputWeapon); //Input Weapon Index
				
// 				// check if the index has a corresponding weapon in inventory.
// 				if (nInputWeapon != 0) 
// 					pSelectedWeapon = findWeapon(nInputWeapon, pPlayer); //Weapon to be equipped

// 				// if the index the player inputted has a weapon
// 				if (pSelectedWeapon != NULL) { 

// 					// if the currently equipped weapon is not empty,
// 					if (strcmp(pPlayer->pEquippedWeapon->strWeaponName, "NONE")) {
// 						addWeaponToInventory(*(pPlayer->pEquippedWeapon), pPlayer);
// 					}
	
// 					pPlayer->pEquippedWeapon = pSelectedWeapon;
// 					removeWeaponFromInventory(*pSelectedWeapon, pPlayer);
// 					displayInventory(SELECT, pPlayer, nPage);

// 				} else {
// 					displayInventory(NO_EXIST, pPlayer, nPage);
// 				}

// 				break;

// 			case PREVIOUS:
// 				if (nPage > 1) 
// 					nPage--;
// 				break;

// 			case NEXT:

// 				nTemp = nPlayerWeapons / 12;

// 				if (nPlayerWeapons % 12 != 0)
// 					nTemp++;

// 				if (nPage < nTemp)
// 					nPage++;

// 				break;

// 			case I_BACK:

// 				openRoundTableHoldScreen(pPlayer);
// 				break;


// 		}
// 	}
// }
void openInventory(Player* pPlayer) {

	// Input Variables
	int nInputInventory = -1; //random value basta wala sa choices

	// Temporary Variables
	int nPage = 1;

	do {

		displayInventory(5, pPlayer, nPage);

		nInputInventory = scanIntInput(0, 3); // Contains the Player's choice.

		processInventoryInput(nInputInventory, pPlayer, nPage);

	} while(nInputInventory != 0);
}

void processInventoryInput(int nInput, Player* pPlayer, int nPage) {
	
	// Get the amount of Weapons the Player has.
	int nPlayerWeapons;
	nPlayerWeapons = getPlayerWeapons(pPlayer);

	// Input variables.
	int nInputWeapon = -1;

	// Slot containing the Player's selected weapon.
	Slot* pSelectedWeapon = NULL;
	int nTemp;

	switch (nInput) {
			
			case SELECT:

				// Ask Player which weapon they want by inputting index.
				printInputTag();
				scanf("%d", &nInputWeapon); //Input Weapon Index
				
				// check if the index has a corresponding weapon in inventory.
				if (nInputWeapon != 0) 
					pSelectedWeapon = findWeaponSlot(nInput, pPlayer->pInventory); 
					//returns NULL if there is not weapon at that index.

				// if the index the player inputted has a weapon
				if (pSelectedWeapon != NULL) { 

					if (strcmp(pPlayer->sEquippedWeapon.strWeaponName, "NONE")){
						addWeapon(putWeaponInSlot(pPlayer->sEquippedWeapon), &(pPlayer->pInventory));
					}
	
					pPlayer->sEquippedWeapon = pSelectedWeapon->sWeapon;

					removeWeapon(pSelectedWeapon, &(pPlayer->pInventory));
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
// Weapon* findWeapon(int nInputIndex, Player* pPlayer) {

// 	Slot* pWeaponSlot = pPlayer->pInventory;
// 	Weapon* pWeapon = pWeaponSlot->pWeapon;
	
// 	while(pWeapon->nWeaponIndex != nInputIndex || pWeaponSlot != NULL) {
// 		pWeaponSlot = pWeaponSlot->pNext;
// 		pWeapon = pWeaponSlot->pWeapon;
// 	}

// 	return pWeapon;
// }

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

	if (!strcmp(sInventorySlot->pNext->sWeapon.strWeaponName, "NONE")) {
		
		if (strcmp(sInventorySlot->pNext->pNext->sWeapon.strWeaponName, "NONE")) {
			
			while (sInventorySlot->pNext != NULL) {
				if (sInventorySlot->pNext->pNext != NULL)
					sInventorySlot->pNext->pNext->sWeapon.nWeaponIndex--;
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
// void removeWeaponFromInventory(Weapon sWeapon, Player* pPlayer) {
// 	Slot* sInventorySlot = pPlayer->pInventory; //get the first weapon

// 	//Find the weapon and set it to slot.
// 	while (!strcmp(sInventorySlot->pWeapon->strWeaponName, sWeapon.strWeaponName) && 
// 			sInventorySlot->pWeapon->nWeaponIndex == sWeapon.nWeaponIndex) {
// 		sInventorySlot = sInventorySlot->pNext;
// 	}

// 	//Set the slot to empty.
// 	sInventorySlot->pWeapon = createEmptyWeapon();
// 	pPlayer->pInventory = sInventorySlot;

// 	//Remove empty spaces between items.
// 	sortInventory(pPlayer);
// }

// void addWeaponToInventory(Weapon sNewWeapon, Player* pPlayer) {

// 	Slot* pInventorySlot = pPlayer->pInventory; //get the first weapon in slot.
// 	Slot* pNewSlot = malloc(sizeof(Slot));
// 	pNewSlot->pWeapon = &sNewWeapon;

// 	//Get the last inventory slot.
// 	while (pInventorySlot->pNext != NULL) {
// 		pInventorySlot = pInventorySlot->pNext;
// 	}

// 	pInventorySlot->pNext = pNewSlot;
// 	pNewSlot->pNext = NULL;

// 	while (pPlayer->pInventory != NULL) {
// 		printf("\n%s\n", pPlayer->pInventory->pWeapon->strWeaponName);
// 	}
// }

int getPlayerWeapons(Player* pPlayer) {
	int nPlayerWeapons = 0;

	Slot* pInventorySlot = pPlayer->pInventory; //get the first weapon

	if (strcmp(pInventorySlot->sWeapon.strWeaponName, "NONE")) {
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
		printf("╔");
		printMultiple("═", SLOT_WIDTH);
		printf("╗");
	}

	printf("\n");
}

void printBottomBorderSlots(int nCols) {

	int i;

	for (i = 0; i < nCols; i++) {
		printf("╚");
		printMultiple("═", SLOT_WIDTH);
		printf("╝");
	}

	printf("\n");
}

void printContentSlot(Weapon sWeapon, int nLine) {

	int nSpaces = 2;

	switch (nLine) {
		case 1:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 2:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName + SLOT_WIDTH-4);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 3:
			printf("│");
			printMultiple(" ", nSpaces);
			//add weapon image
			printf("  <weapon>  ");
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 4:
			printf("│");
			printf("HP ");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nHP);
			printf("END");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nEnd);
			printf("│");
			break;
		case 5:
			printf("│");
			printf("DEX");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nDexReq);
			printf("STR");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nStr);
			printf("│");
			break;
		case 6:
			printf("│");
			printf("INT");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nInt);
			printf("FTH");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nFth);
			printf("│");
			break;
		case 7:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%*d", SLOT_WIDTH-4, sWeapon.nWeaponIndex);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
	}
}

void printEmptySlot() {
	
	printf("│");
	printMultiple(" ", SLOT_WIDTH);
	printf("│");
}

void printInventoryGrid(Player* pPlayer, int nPage) {

	// Contains the values need to be printed.
	Slot* pInventoryHead = pPlayer->pInventory; // Head of the inventory.
	Slot* pTempHead;
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

		for (k = 1; k <= 7; k++) {

			pTempHead = pInventoryHead; //reset every line

			for (j = 0; j < INVENTORY_MAX_COLS; j++) {
				
				if (pTempHead != NULL) {
					if (strcmp(pTempHead->sWeapon.strWeaponName, "NONE")) {
						
						printContentSlot(pTempHead->sWeapon, k);
						pTempHead = pTempHead->pNext;
					} else {
						printEmptySlot(INVENTORY_MAX_COLS, INVENTORY_MAX_ROWS);
					}
				} else {
					printEmptySlot(INVENTORY_MAX_COLS, INVENTORY_MAX_ROWS);
				}
			}

			printf("\n");
		}

		//Update the outer one too.
		for (k = 0; k < INVENTORY_MAX_COLS; k++) {
			
			if (pInventoryHead != NULL)
				pInventoryHead = pInventoryHead->pNext;
		}				
			
		printBottomBorderSlots(INVENTORY_MAX_COLS);
	}
}

void displayInventory(int nPrompt, Player* pPlayer, int nPage) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	printMultiple(" ", 25);
	printf("--- INVENTORY ---\n\n");

	printInventoryGrid(pPlayer, nPage);

	printf("\n\n");
	printMultiple(" ", SCREEN_PADDING);
	printf("OPTIONS:\n");
	printOption(1, "SELECT WEAPON");
	printOption(2, "PREVIOUS PAGE");
	printOption(3, "NEXT PAGE");
	printOption(0, "BACK");
	printf("\n\n");

	switch(nPrompt) {
		case SELECT:
			printf("You equipped %s.", pPlayer->sEquippedWeapon.strWeaponName);
			break;
		case NO_EXIST:
			printSystemMessage("There's no weapon at that index.");
			break;
		default:
			break;
	}

	printInputTag();
}