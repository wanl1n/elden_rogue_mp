#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"
#include "time.h"
#include "driver.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"
#include "utility/doors.c"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/roundtable_screen.c"
#include "screens/areas_screen.c"
#include "screens/battle_screen.c"
#include "screens/credits_screen.c"
#include "screens/roundtable_screens/fasttravel_screen.c"
#include "screens/roundtable_screens/levelup_screen.c"
#include "screens/roundtable_screens/inventory_screen.c"


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
	Weapon sWeaponBase = {0, "NONE", 0, 0, 0, 0, 0, 0};
	Weapon* sEmptyWeapon = &sWeaponBase;
	pPlayer->pInventory->sWeapon = sEmptyWeapon;
	pPlayer->pInventory->pNext = NULL;

	pPlayer->pEquippedWeapon = sEmptyWeapon;

	resetColors();
	openTitleScreen(pPlayer);

	return 0;
}