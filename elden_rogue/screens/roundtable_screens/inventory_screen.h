#ifndef INVENTORY_SCREEN
#define INVENTORY_SCREEN

#define INVENTORY_MAX_ROWS	3
#define INVENTORY_MAX_COLS	4

void printInventorySlot(Weapon sWeapon);
void printInventoryGrid(Player* pPlayer, int nPage);
void displayInventory(int nPrompt, Player* pPlayer, int nPage);

Weapon* findWeapon(int nInputIndex, Player* pPlayer);
Weapon* createEmptyWeapon();
void sortInventory(Player* pPlayer);
void removeWeaponFromInventory(Weapon sWeapon, Player* pPlayer);
void addWeaponToInventory(Weapon* sWeapon, Player* pPlayer);

void openInventory(Player* pPlayer);

#endif