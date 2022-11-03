#ifndef ORIGIN
#define ORIGIN 

typedef struct sPlayer {

	char cName[26];
	char cJobClass[11];
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
	int* nInventory;
	int* nWeapons;

	//Equipment (Currently equipped)
	int nEquippedWeapon;
	int nPotions;

	int nShards[6];

	//Area Details
	int nPlayerRow;
	int nPlayerCol;
	int nPlayerHP;
	int nPlayerMaxHP;

} sPlayer;

#endif