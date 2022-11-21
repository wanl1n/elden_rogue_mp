#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"
#include "time.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"
#include "driver.h"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/roundtable_screen.c"
#include "screens/areas_screen.c"
#include "screens/battle_screen.c"

int main() {

	system("chcp 65001");
	system("cls");

	//Player Initialization
	Player sPlayer;

	//Initial Player Statistics
	strcpy(sPlayer.strName, "");
	strcpy(sPlayer.strJobClass, "");
	sPlayer.nRunes = 700;
	
	int i; for(i = 0; i < 6; i++) {
		sPlayer.aShards[i] = 0;
	}

	Player* pPlayer;
	pPlayer = &sPlayer;

	//Inventory Initialization
	pPlayer->pInventory = NULL;
	Slot sWeapon = {0, "NONE", 0, 0, 0, 0, 0, 0, NULL, NULL};
	pPlayer->pInventory = &sWeapon;

	pPlayer->pEquippedWeapon = &sWeapon;

	resetColors();
	openTitleScreen(pPlayer);

	return 0;
}