#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/"


struct sPlayer {

	char[25] cName;
	char[10] cJobClass;
	int nLevel;
	int nRunes;

	//Player Statistics
	int nHealth;
	int nEndurance;
	int nDexterity;
	int nStrength;
	int nIntelligence;
	int nFaith; 

	//Inventory
	int* nInventory = (int*) malloc(9*sizeof(int));
	int* nWeapons = (int*) malloc(9*sizeof(int));

	//Equipment (Currently equipped)
	int nEquippedWeapon;
	int nPotions;

	int[6] nShards;

	//Area Details
	int nPlayerRow;
	int nPlayerCol;
	int nPlayerHP;
	int nPlayerMaxHP;

};

int main() {

	struct sPlayer sPlayer;

	resetColors();
	openTitleScreen(sPlayer);

	return 0;
}