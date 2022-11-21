#ifndef ORIGIN
#define ORIGIN 

struct InventorySlot {

	int nWeaponIndex;
	char strWeaponName[24];

	int nDexReq;
	int nHP;
	int nInt;
	int nEnd;
	int nStr;
	int nFth;

	struct InventorySlot* pNext;
	struct InventorySlot* pPrev;
};
typedef struct InventorySlot Slot;

typedef struct Player {

	char strName[26];
	char strJobClass[11];
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
	Slot* pInventory;

	//Equipment (Currently equipped)
	Slot* pEquippedWeapon;
	int nPotions;

	int aShards[6];

	//Area Details
	int aPlayerLoc[2];
	int nPlayerMaxHP;

} Player;



#endif