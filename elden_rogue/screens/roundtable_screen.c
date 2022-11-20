#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"

#include "../driver.h"

#include "../config/settings.h"

void displayRoundTableHoldScreen(Player* pPlayer) {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"Player Statistics:\n"
		" NAME: %s\n"
		" JOB CLASS: %s\n"
		" LEVEL: %d\n"
		" RUNES: %d\n"
		" SHARDS: ",
		pPlayer->cName, pPlayer->cJobClass, pPlayer->nLevel,
		pPlayer->nRunes);

	int i; for(i = 0; i < 6; i++) {
		printf("[%d]", pPlayer->nShards[i]);
	}		

	printf("\n\n"
		"[1] FAST TRAVEL\n"
		"[2] LEVEL UP\n"
		"[3] INVENTORY\n"
		"[4] SHOP\n"
		"[5] SAVE\n"
		"[0] QUIT GAME\n\n"
		"SYSTEM MESSAGES: ");
}

void displayFastTravelScreen() {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"FAST TRAVEL:\n"
		"[1] STORMVEIL\n"
		"[2] RAYA LUCARIA\n"
		"[3] REDMANE CASTLE\n"
		"[4] VOLCANO MANOR\n"
		"[5] LEYNDELL CAPITAL\n"
		"[6] THE ELDEN THRONE\n"
		"[0] BACK\n\n"
		"INPUT: ");
}

void displayLevelUpScreen(Player* pPlayer) {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"LEVEL UP:							RUNES: %d\n"
		"					%s\n\n"
		"	STATISTICS		[1] HEALTH			%d\n"
		"LEVEL		%d 		[2] ENDURANCE		%d\n"
		"RUNE COST	%d		[3] DEXTERITY		%d\n"
		"					[4] STRENGTH		%d\n"
		"					[5] INTELLIGENCE	%d\n"
		"					[6] FAITH			%d\n\n"
		"[0] BACK\n\n"
		"INPUT: ", 
		pPlayer->nRunes, pPlayer->cJobClass,
		pPlayer->nHealth,
		pPlayer->nLevel, pPlayer->nEndurance,
		350, pPlayer->nDexterity,
		pPlayer->nStrength, pPlayer->nIntelligence, pPlayer->nFaith);
}

void displayInventory(Player* pPlayer) {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"INVENTORY\n"
		"OPTIONS:\n");

	//temporary inventory grid
	int i, j;

	for(j = 0; j < 3; j++) {
		for(i = 0; i < 3*5; i++) {
			printf("_");
		} printf("\n");
		for(i = 0; i < 3; i++) {
			printf("|    ");
		} printf("|\n");
		for(i = 0; i < 3; i++) {
			printf("|    ");
		} printf("|\n");
	}
		
	printf("[1] SELECT\n"
		"[2] PREVIOUS PAGE\n"
		"[3] NEXT PAGE\n"
		"[0] BACK\n\n"
		"INPUT: ");
}

void displayShop() {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"			SHOP\n"
		"OPTIONS:\n"
		"[1] BUY WEAPONS\n"
		"[2] SELL WEAPONS\n"
		"[0] BACK\n\n"
		"INPUT: ");

}

void displayBuyShop(Player* pPlayer) {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"			SHOP  				RUNES: %d\n"
		"[1] SHORT SWORD		$1000 	DEX: 13\n"
		"[2] ROGIER'S RAPIER	$2000 	DEX: 18\n"
		"[3] CODED SWORD		$4000 	DEX: 21\n"
		"[4] NIGHT & FLAME		$8000 	DEX: 25\n"
		"[0] BACK\n\n"
		"INPUT: ", pPlayer->nRunes);
}

void displaySaveScreen(Player* pPlayer) {
	printf("-------ROUNDTABLE HOLD-------\n\n"
		"			SAVE\n"
		"[1] SAVE\n"
		"[0] BACK\n\n"
		"INPUT: ");
}

void openRoundTableHoldScreen(Player* pPlayer) {
	displayRoundTableHoldScreen(pPlayer);

	int nInputRoundTable;

	nInputRoundTable = scanIntInput(0, 5);
	switch(nInputRoundTable) {
		case FAST_TRAVEL:
			openFastTravelScreen();
			break;
		case LEVEL_UP:
			openLevelUpScreen(pPlayer);
			break;
		case INVENTORY:
			openInvetory(pPlayer);
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

void openFastTravelScreen() {
	displayFastTravelScreen();
}

void openLevelUpScreen(Player* pPlayer) {
	displayLevelUpScreen(pPlayer);
}

void openInvetory(Player* pPlayer) {
	displayInventory(pPlayer);
}

void openShop(Player* pPlayer) {
	displayShop();
}

void openSaveScreen(Player* pPlayer) {
	displaySaveScreen(pPlayer);
}