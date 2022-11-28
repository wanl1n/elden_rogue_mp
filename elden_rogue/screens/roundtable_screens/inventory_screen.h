#ifndef INVENTORY_SCREEN
#define INVENTORY_SCREEN

#define INVENTORY_MAX_ROWS	4
#define INVENTORY_MAX_COLS	5


void openInventory(Player* pPlayer);

Weapon* findWeapon(int nInputIndex, Player* pPlayer);
Weapon* createEmptyWeapon();
void sortInventory(Player* pPlayer);
void removeWeaponFromInventory(Weapon sWeapon, Player* pPlayer);
void addWeaponToInventory(Weapon* sWeapon, Player* pPlayer);
int getPlayerWeapons(Player* pPlayer);

void printInventorySlot(Weapon sWeapon);
void printTopBorderSlots(int nCols);
void printBottomBorderSlots(int nCols);
void printInventoryGrid(Player* pPlayer, int nPage);
void displayInventory(int nPrompt, Player* pPlayer, int nPage);




#endif