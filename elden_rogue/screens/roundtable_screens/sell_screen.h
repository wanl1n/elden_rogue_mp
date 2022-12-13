#ifndef SELL_SCREEN
#define SELL_SCREEN

#define SUCCESSFUL 		1
#define UNIQUE 			2

void displaySellShop(int nPrompt, Player* pPlayer, Weapon sWeapon, int nProfit);
void openSellScreen(Player* pPlayer);
Weapon* createPlaceholderWeapon();

#endif
