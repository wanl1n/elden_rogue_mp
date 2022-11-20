#ifndef ROUNDTABLE_SCREEN
#define ROUNDTABLE_SCREEN

//ROUNDTABLE SCREEN CHOICES
#define FAST_TRAVEL			1
#define LEVEL_UP			2
#define INVENTORY			3
#define SHOP				4
#define SAVE 				5
#define QUIT_GAME			0

void displayRoundTableHoldScreen(Player* pPlayer);
void displayFastTravelScreen();
void displayLevelUpScreen(Player* pPlayer);
void displayInventory(Player* pPlayer);
void displayShop();
void displayBuyShop(Player* pPlayer);
void displaySaveScreen(Player* pPlayer);

void openRoundTableHoldScreen(Player* pPlayer);
void openFastTravelScreen();
void openLevelUpScreen(Player* pPlayer);
void openInvetory(Player* pPlayer);
void openShop(Player* pPlayer);
void openSaveScreen(Player* pPlayer);

#endif 