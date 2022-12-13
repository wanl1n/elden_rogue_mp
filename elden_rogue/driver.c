#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"
#include "time.h"
#include "driver.h"
#include "conio.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"
#include "utility/doors.c"
#include "utility/inventory_manager.c"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/roundtable_screen.c"
#include "screens/areas_screen.c"
#include "screens/battle_screen.c"
#include "screens/credits_screen.c"
#include "screens/roundtable_screens/fasttravel_screen.c"
#include "screens/roundtable_screens/levelup_screen.c"
#include "screens/roundtable_screens/inventory_screen.c"
#include "screens/roundtable_screens/buy_screen.c"
#include "screens/roundtable_screens/sell_screen.c"

#include "screens/questlines/questline_screen.c"


int main() {

	system("chcp 65001");
	system("cls");

	//Player Initialization
	Player sPlayer;

	//Initial Player Statistics
	strcpy(sPlayer.strName, "");
	strcpy(sPlayer.strJobClass, "");
	// sPlayer.nRunes = 500000; // For testing purposes.
	sPlayer.nRunes = 0;
	sPlayer.nPotions = 8;
	
	int i; for(i = 0; i < 6; i++) {
		sPlayer.aShards[i] = 0;
	}

	// sPlayer.aShards[4] = 1; // Sets Leyndell Capital to cleared for testing purposes.

	Player* pPlayer;
	pPlayer = &sPlayer;

	//Inventory Initialization
	Weapon sWeaponBase = {0, "NONE", 0, 0, 0, 0, 0, 0, 0};
	pPlayer->pInventory = NULL;
	pPlayer->sEquippedWeapon = sWeaponBase;

	pPlayer->pQuestLine = NULL;
	pPlayer->nQuestProgress = 0;
	pPlayer->nCompletedQuests = 0;

	resetColors();
	openTitleScreen(pPlayer);

	return 0;
}