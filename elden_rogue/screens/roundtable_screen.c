#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"

#include "../driver.h"

#include "../config/settings.h"

void displayRoundTableHoldScreen(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf(" NAME: %s\n"
		   " JOB CLASS: %s\n"
		   " LEVEL: %d\n"
		   " RUNES: %d\n"
		   " SHARDS: ",
		   pPlayer->strName, pPlayer->strJobClass, pPlayer->nLevel,
		   pPlayer->nRunes);

	int i; for(i = 0; i < 6; i++) {
		printf("[%d]", pPlayer->aShards[i]);
	}		

	printf("\n\n");
	printOption(1, "FAST TRAVEL");
	printOption(2, "LEVEL UP");
	printOption(3, "INVENTORY");
	printOption(4, "SHOP");
	printOption(5, "SAVE");
	printOption(0, "QUIT GAME");
	printf("\n\n");

	switch(nPrompt) {
		case FAST_TRAVEL:
			printSystemMessage("Taking you to Fast Travel menu...");
			break;
		case LEVEL_UP:
			printSystemMessage("Taking you to Level Up menu...");
			break;
		case INVENTORY:
			printSystemMessage("Taking you to Inventory...");
			break;
		case SHOP:
			printSystemMessage("Taking you to Shop...");
			break;
		case SAVE:
			printSystemMessage("Taking you to Save Menu...");
			break;
		case QUIT_GAME:
			printSystemMessage("Going back to Title Screen...");
			break;
		case 6:
			break;
	}

	Sleep(DELAY);
}

void displayFastTravelScreen(int nPrompt) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);

	printf("\t\tFAST TRAVEL:\n");

	printf("\n\n");
	printOption(1, "STORMVEIL");
	printOption(2, "RAYA LUCARIA");
	printOption(3, "REDMANE CASTLE");
	printOption(4, "VOLCANO MANOR");
	printOption(5, "LEYNDELL CAPITAL");
	printOption(6, "THE ELDEN THRONE");
	printOption(0, "BACK");
	printf("\n\n");

	switch(nPrompt) {
		case STORMVEIL:
			printSystemMessage("Travelling to Stormveil.");
			break;
		case RAYA_LUCARIA:
			printSystemMessage("Travelling to Raya Lucaria.");
			break;
		case REDMANE_CASTLE:
			printSystemMessage("Travelling to Redmane Castle.");
			break;		
		case VOLCANO_MANOR:
			printSystemMessage("Travelling to Volcano Manor.");
			break;
		case LEYNDELL_CAPITAL:
			printSystemMessage("Travelling to Leyndell Capital.");
			break;
		case THE_ELDEN_THRONE:
			printSystemMessage("Travelling to The Elden Throne.");
			break;
		case FT_BACK:
			printSystemMessage("Going back to Roundtable Hold.");
			break;
	}
	
	printInputTag();

	Sleep(DELAY);
}

void displayLevelUpScreen(int nPrompt, Player* pPlayer, int nRuneCost) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);

	printf("	LEVEL UP:			RUNES: %d\n"
		"	Current Job Class: %s\n\n"
		"	STATISTICS:			[1] HEALTH			%d\n"
		"   LEVEL		%d 		[2] ENDURANCE			%d\n"
		"   RUNE COST		%d		[3] DEXTERITY			%d\n"
		"					[4] STRENGTH			%d\n"
		"					[5] INTELLIGENCE		%d\n"
		"					[6] FAITH			%d\n\n"
		"					[0] BACK\n\n", 
		pPlayer->nRunes, pPlayer->strJobClass,
		pPlayer->nHealth,
		pPlayer->nLevel, pPlayer->nEndurance,
		nRuneCost, pPlayer->nDexterity,
		pPlayer->nStrength, pPlayer->nIntelligence, pPlayer->nFaith);

	switch(nPrompt) {
		case HEALTH:
			printSystemMessage("You have levelled up your Health.");
			break;
		case ENDURANCE:
			printSystemMessage("You have levelled up your Endurance.");
			break;
		case DEXTERITY:
			printSystemMessage("You have levelled up your Dexterity.");
			break;
		case STRENGTH:
			printSystemMessage("You have levelled up your Strength.");
			break;
		case INTELLIGENCE:
			printSystemMessage("You have levelled up your Intelligence.");
			break;
		case FAITH:
			printSystemMessage("You have levelled up your Faith.");
			break;
		case INSUFFICIENT_RUNES:
			printSystemMessage("You don't have enough runes :(");
			break;
		case MAXED_OUT:
			printSystemMessage("You have reached the maximum level for this stat.");
			break;
		case 9:
			break;
	}
	
	printInputTag();
}

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

	Slot* pTemp = pPlayer->pInventory;

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

void displayShop() {
	
	system("cls");
	
	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\t\tSHOP\n");

	printf("\n\n");
	printOption(1, "BUY WEAPONS");
	printOption(2, "SELL WEAPONS");
	printOption(0, "BACK");
	printf("\n\n");

	printInputTag();
}

void displayBuyShop(Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("		____SHOP____	RUNES: %d\n"
		"[1] SHORT SWORD		$1000 	DEX: 13\n"
		"[2] ROGIER'S RAPIER	$2000 	DEX: 18\n"
		"[3] CODED SWORD		$4000 	DEX: 21\n"
		"[4] NIGHT & FLAME		$8000 	DEX: 25\n"
		"[0] BACK\n\n"
		"INPUT: ", pPlayer->nRunes);
}

void displaySellShop(Player* pPlayer) {
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printInventoryGrid(pPlayer);

	// printf("		____SHOP____	RUNES: %d\n"
	// 	"[1] SHORT SWORD		$1000 	DEX: 13\n"
	// 	"[2] ROGIER'S RAPIER	$2000 	DEX: 18\n"
	// 	"[3] CODED SWORD		$4000 	DEX: 21\n"
	// 	"[4] NIGHT & FLAME		$8000 	DEX: 25\n"
	// 	"[0] BACK\n\n"
	// 	"INPUT: ", pPlayer->nRunes);
}

void displaySaveScreen(Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("			SAVE\n"
		"[1] SAVE\n"
		"[0] BACK\n\n"
		"INPUT: ");
}

void openRoundTableHoldScreen(Player* pPlayer) {
	displayRoundTableHoldScreen(6, pPlayer);

	int nInputRoundTable;

	nInputRoundTable = scanIntInput(0, 5);
	displayRoundTableHoldScreen(nInputRoundTable, pPlayer);

	switch(nInputRoundTable) {
		case FAST_TRAVEL:
			openFastTravelScreen(pPlayer);
			break;
		case LEVEL_UP:
			openLevelUpScreen(pPlayer);
			break;
		case INVENTORY:
			openInventory(pPlayer);
			break;
		case SHOP:
			openShop(pPlayer);
			break;
		case SAVE:
			openSaveScreen(pPlayer);
			break;
		case QUIT_GAME:
			openTitleScreen(pPlayer);
			break;
	}

}

int getPlayerShards() {
	
}

void openFastTravelScreen(Player* pPlayer) {
	displayFastTravelScreen(7);

	int nInputFastTravel;

	nInputFastTravel = scanIntInput(0, 6);

	displayFastTravelScreen(nInputFastTravel);

	switch(nInputFastTravel) {
		case STORMVEIL:
		case RAYA_LUCARIA:
		case REDMANE_CASTLE:
		case VOLCANO_MANOR:
			openAreaScreen(nInputFastTravel, pPlayer);
			break;
		case LEYNDELL_CAPITAL:
			if (pPlayer->aShards)
			break;

		case THE_ELDEN_THRONE:

			break;

		case FT_BACK:
			openRoundTableHoldScreen(pPlayer);
			break;

	}
}

void levelUp(int nStat, Player* pPlayer, int nRuneCost) {

	int nSuccess = 0;

	switch(nStat) {
		case HEALTH:
			if (pPlayer->nHealth < 50) {
				pPlayer->nHealth++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case ENDURANCE:
			if (pPlayer->nEndurance < 50) {
				pPlayer->nEndurance++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case DEXTERITY:
			if (pPlayer->nDexterity < 50) {
				pPlayer->nDexterity++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case STRENGTH:
			if (pPlayer->nStrength < 50) {
				pPlayer->nStrength++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case INTELLIGENCE:
			if (pPlayer->nIntelligence < 50) {
				pPlayer->nIntelligence++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case FAITH:
			if (pPlayer->nFaith < 50) {
				pPlayer->nFaith++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;

	}

	if(nSuccess) {
		pPlayer->nLevel++;
		pPlayer->nRunes -= nRuneCost; printf("%d", nRuneCost);
	} else {
		displayLevelUpScreen(MAXED_OUT, pPlayer, nRuneCost);
	}
	
}

void openLevelUpScreen(Player* pPlayer) {

	int nInputLevelUp = 100; //random value basta wala sa choices
	int nRuneCost = (pPlayer->nLevel * 100) / 2;

	displayLevelUpScreen(9, pPlayer, nRuneCost);

	while(nInputLevelUp != 0) {

		nInputLevelUp = scanIntInput(0, 6);

		if (nInputLevelUp == 0) {
			openRoundTableHoldScreen(pPlayer);
		} else if (pPlayer->nRunes >= nRuneCost) {
			levelUp(nInputLevelUp, pPlayer, nRuneCost);
			displayLevelUpScreen(nInputLevelUp, pPlayer, nRuneCost);
		} else {
			displayLevelUpScreen(INSUFFICIENT_RUNES, pPlayer, nRuneCost);
		}

		nRuneCost = (pPlayer->nLevel * 100) / 2; //Calculate new rune cost after level up.
	}
}

Slot* findWeapon(int nInputIndex, Player* pPlayer) {

	Slot* pWeapon = pPlayer->pInventory;
	
	while(pWeapon->nWeaponIndex != nInputIndex || pWeapon != NULL) {
		pWeapon = pWeapon->pNext;
	}

	return pWeapon;
}

void openInventory(Player* pPlayer) {
	displayInventory(5, pPlayer);

	int nInputInventory = 100; //random value basta wala sa choices
	int nInputWeapon;

	Slot* pSelectedWeapon;

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

void openBuyScreen(Player* pPlayer) {
	displayBuyShop(pPlayer);
}

void openSellScreen(Player* pPlayer) {
	displaySellShop(pPlayer);
}

void openShop(Player* pPlayer) {
	displayShop();

	int nInputShop;

	while(nInputShop != 0) {
		nInputShop = scanIntInput(0, 2);

		switch(nInputShop) {
			case BUY_WEAPON:
				openBuyScreen(pPlayer);
				break;
			case SELL_WEAPON:
				break;
			case S_BACK:
				break;
		}
	}
}

void openSaveScreen(Player* pPlayer) {
	displaySaveScreen(pPlayer);

	int nInputSave = 100; //random value thats not part of the choices.

	while(nInputSave != 0) {
		nInputSave = scanIntInput(0, 1);

		if (nInputSave) {
			//save game
		} else {
			openRoundTableHoldScreen(pPlayer);
		}
	}
}