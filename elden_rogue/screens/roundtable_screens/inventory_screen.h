#ifndef INVENTORY_SCREEN
#define INVENTORY_SCREEN

//INVENTORY PRINTING
#define INVENTORY_MAX_ROWS		2
#define INVENTORY_MAX_COLS		4
#define INVENTORY_SLOT_HEIGHT 	16
#define SLOT_WIDTH				16

#define SELECT				1
#define PREVIOUS			2
#define NEXT 				3
#define I_BACK 				0
#define NO_EXIST			4
#define LACK_DEX			5


void openInventory(Player* pPlayer);

void processInventoryInput(int nInput, Player* pPlayer, int* pPage);
int getPlayerWeapons(Slot** pInventoryHead);
char* getSpriteFromWeapon(Weapon sWeapon);

// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
void printTopBorderSlots(int nCols);
void printBottomBorderSlots(int nCols);
void printContentSlot(Weapon sWeapon, int nLine);
void printSprite(Weapon sWeapon, int nLine);
void printEmptySlot();
void printInventoryGrid(Player* pPlayer, int nPage);
void displayInventory(int nPrompt, Player* pPlayer, int nPage);

#endif