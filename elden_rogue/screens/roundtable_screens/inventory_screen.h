#ifndef INVENTORY_SCREEN
#define INVENTORY_SCREEN

#define INVENTORY_MAX_ROWS	4
#define INVENTORY_MAX_COLS	5

//INVENTORY PRINTING
#define SLOT_WIDTH			16
#define SELECT				1
#define PREVIOUS			2
#define NEXT 				3
#define I_BACK 				0
#define NO_EXIST			4


void openInventory(Player* pPlayer);
void processInventoryInput(int nInput, Player* pPlayer, int nPage);

// Weapon* findWeapon(int nInputIndex, Player* pPlayer);
Weapon* createEmptyWeapon();
void sortInventory(Player* pPlayer);
// void removeWeaponFromInventory(Weapon sWeapon, Player* pPlayer);
// void addWeaponToInventory(Weapon sNewWeapon, Player* pPlayer);
int getPlayerWeapons(Slot** pInventoryHead);

// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
void printTopBorderSlots(int nCols);
void printBottomBorderSlots(int nCols);
void printContentSlot(Weapon sWeapon, int nLine);
void printEmptySlot();
void printInventoryGrid(Player* pPlayer, int nPage);
void displayInventory(int nPrompt, Player* pPlayer, int nPage);

#endif