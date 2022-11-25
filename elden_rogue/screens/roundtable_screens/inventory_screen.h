#ifndef INVENTORY_SCREEN
#define INVENTORY_SCREEN

void printInventorySlot(int nIndex, char strName[], int nDexReq);
void printInventoryGrid(Player* pPlayer);
void displayInventory(int nPrompt, Player* pPlayer);
Weapon* findWeapon(int nInputIndex, Player* pPlayer);
void openInventory(Player* pPlayer);

#endif