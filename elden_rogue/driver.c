#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"
#include "driver.h"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/roundtable_screen.c"

int main() {

	system("chcp 65001");
	system("cls");

	//Player Initialization
	Player sPlayer;

	//Initial Player Statistics
	strcpy(sPlayer.cName, "");
	strcpy(sPlayer.cJobClass, "");
	sPlayer.nRunes = 700;
	
	int i; for(i = 0; i < 6; i++) {
		sPlayer.nShards[i] = 0;
	}

	Player* pPlayer;
	pPlayer = &sPlayer;

	//Inventory Initialization
	pPlayer->pInventory = NULL;
	Slot sWeapon = {0, "NONE", 0, NULL, NULL};
	pPlayer->pInventory = &sWeapon;

	pPlayer->pEquippedWeapon = &sWeapon;

	resetColors();
	openTitleScreen(pPlayer);

	return 0;
}