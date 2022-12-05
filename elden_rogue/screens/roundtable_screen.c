// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "title_screen.h" //When Player goes back.
#include "roundtable_screen.h" // When Player chooses Continue.
#include "areas_screen.h" //When the Player fast travels.

//Screens accessed through the Roundtable Hold Screen.
#include "roundtable_screens/fasttravel_screen.h"
#include "roundtable_screens/levelup_screen.h"
#include "roundtable_screens/inventory_screen.h"
#include "roundtable_screens/buy_screen.h"
#include "roundtable_screens/sell_screen.h"

#include "../driver.h" //Contains all the structures used in the code.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openRoundTableHoldScreen	Opens the Character Creation Screen.
	
	@param	pPlayer				The Player Structure containing all 
								of the Player's statistics and items. 

	Pre-condition				pPlayer should be initiated and all 
								members should have a value.	   	   */
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



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayRoundTableHoldScreen		Prints the User Interface of the 
									Roundtable Hold Screen.
	
	@param	nPrompt					An integer value containing the 
									prompt integer code.
	@param	pPlayer					The Player Structure containing all 
									of the Player's statistics and items. 

	Pre-condition					pPlayer should be initiated and all 
									members should have a value.	   */
void displayRoundTableHoldScreen(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\tNAME: %s\n"
		   "\tJOB CLASS: %s\n"
		   "\tLEVEL: %d\n"
		   "\tRUNES: %d\n"
		   "\tSHARDS: ",
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



//TO BE MOVED
void displayShop() {
	
	system("cls");
	
	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\t\tSHOP\n");

	printf("\n\n");
	printOption(1, "BUY WEAPONS");
	printOption(2, "SELL WEAPONS");
	printOption(0, "BACK");
	printf("\n\n");
}

void displaySaveScreen(Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("			SAVE\n"
		"[1] SAVE\n"
		"[0] BACK\n\n"
		"INPUT: ");
}

void openShop(Player* pPlayer) {
	displayShop();

	int nInputShop;

	while(nInputShop != 0) {
		nInputShop = scanIntInput(0, 2);

		switch(nInputShop) {
			case BUY_WEAPON:
				openBuyScreen(pPlayer);
				nInputShop = 0;
				break;
			case SELL_WEAPON:
				openSellScreen(pPlayer);
				nInputShop = 0;
				break;
			case S_BACK:
				openRoundTableHoldScreen(pPlayer);
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