#include "title_screen.h"
#include "chara_creation_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"

#include "../driver.h"

#include "../config/settings.h"

//User Interface / Printing Functions 
void printInventorySlot(int nIndex, char strName[], int nDexReq) {

	int nSpaces = 2;

	int nLength = strlen(strName);

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
	printf("%-*.*s", SLOT_WIDTH-4, nLength/2, strName);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, strName + nLength/2);
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
	printf("%*d", SLOT_WIDTH-4, nIndex);
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

	Weapon* pTemp = pPlayer->pInventory;

	printf("\n");

	//Traversing Linked List
	while(pTemp != NULL) {

		// printMultiple(" ", SCREEN_PADDING);
		printInventorySlot(pTemp->nWeaponIndex, pTemp->strWeaponName, pTemp->nDexReq);

		pTemp = pTemp->pNext;
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

	Weapon* pWeapon = pPlayer->pInventory;
	
	while(pWeapon->nWeaponIndex != nInputIndex || pWeapon != NULL) {
		pWeapon = pWeapon->pNext;
	}

	return pWeapon;
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
				scanf("%d", &nInputWeapon); //Select Weapon.
				
				pSelectedWeapon = findWeapon(nInputWeapon, pPlayer); //The selected weapon.

				if (pSelectedWeapon != NULL) {
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