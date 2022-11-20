#ifndef ORIGIN
#define ORIGIN 

struct InventorySlot {

	int nWeaponIndex;
	char strWeaponName[24];

	int nDexReq;

	struct InventorySlot* pNext;
	struct InventorySlot* pPrev;
};
typedef struct InventorySlot Slot;

typedef struct Player {

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
	Slot* pInventory;

	//Equipment (Currently equipped)
	Slot* pEquippedWeapon;
	int nPotions;

	int nShards[6];

	//Area Details
	int nPlayerRow;
	int nPlayerCol;
	int nPlayerHP;
	int nPlayerMaxHP;

} Player;



#endif