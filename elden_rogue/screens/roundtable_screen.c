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
#include "questlines/questline_screen.h"

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

	nInputRoundTable = scanIntInput(0, 6);
	displayRoundTableHoldScreen(nInputRoundTable, pPlayer);
	
	//display npc icon with exclamation point here.
	//Input 7 to interact.
	
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
		case NPC_INTERACT:
			openQuestScreen(pPlayer);
			break;
		case QUIT_GAME:
			openTitleScreen(pPlayer);
			break;
	}
}

/* 	openShop 			Opens the shop screen.

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
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

/* 	openSaveScreen		Opens the save screen.

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openSaveScreen(Player* pPlayer) {
	displaySaveScreen(pPlayer);

	FILE* fp;
	int nInventorySize, i;
	Slot** pTempHead = &(pPlayer->pInventory);

	int nInputSave = 100; //random value thats not part of the choices.

	while(nInputSave != 0) {
		nInputSave = scanIntInput(0, 1);

		if (nInputSave) {
			fp = fopen("saves/save.dat", "wb");

			fwrite(pPlayer, sizeof(Player), 1, fp);

			nInventorySize = getPlayerWeapons(&(pPlayer->pInventory));

			for (i = 0; i < nInventorySize; i++) {
				fwrite(*pTempHead, sizeof(Slot), 1, fp);
				*pTempHead = (*pTempHead)->pNext;
			}

			fclose(fp);

			printSystemMessage("Saved your progress.");
		} else {
			openRoundTableHoldScreen(pPlayer);
		}
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
	
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("Hi, %s! \n\n", pPlayer->strName);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("┌ JOB    ► %s \n", pPlayer->strJobClass);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("├ LEVEL  ► %d \n", pPlayer->nLevel);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("├ RUNES  ► %d \n", pPlayer->nRunes);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("└ SHARDS ► ", pPlayer->nLevel);
	

	int i; for(i = 0; i < 6; i++) {
		if (pPlayer->aShards[i]) {
			printf("■ ");
		} else {
			printf("□ ");
		}
	}

	printf("\n");		
	
	if (pPlayer->pQuestLine != NULL) {

		printf("\n");	

		printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
		printf("!! QUEST    ► ");

		switch(pPlayer->pQuestLine->nQuestStatus) {
			case 0:
				printf("INACTIVE\n");
				break;
			case 1:
				printf("IN PROGRESS\n");
				break;
			case 2:
				printf("COMPLETE\n");
				break;
		}

		printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
		printf(">> PROGRESS ► %d", pPlayer->nQuestProgress);
	}

	printf("\n");
	printOption(1, "FAST TRAVEL");
	printOption(2, "LEVEL UP");
	printOption(3, "INVENTORY");
	printOption(4, "SHOP");
	printOption(5, "SAVE");
	printOption(6, "INTERACT WITH NPC");
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

/* 	displayShop 	Displays the shop screen.						   */
void displayShop() {
	
	system("cls");
	
	printHeader("SHOP", 4);

	printf("\n\n");
	printOption(1, "BUY WEAPONS");
	printOption(2, "SELL WEAPONS");
	printOption(0, "BACK");
	printf("\n\n");
}

/*	displaySaveScreen 	Displays the save screen.			

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void displaySaveScreen(Player* pPlayer) {
	
	system("cls");

	printHeader("SAVE", 4);
	
	printOption(1, "SAVE");
	printOption(0, "BACK");
}