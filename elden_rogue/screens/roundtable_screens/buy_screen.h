#ifndef BUY_SCREEN
#define BUY_SCREEN

//Weapon Types
#define WEAPON_SWORD		1
#define WEAPON_KATANA		2
#define WEAPON_WHIP			3
#define WEAPON_GREATSWORD	4
#define WEAPON_STAVE		5
#define WEAPON_SEAL			6

//Weapon Index within the category in shop
#define ITEM_ONE		1
#define ITEM_TWO		2
#define ITEM_THREE		3
#define ITEM_FOUR		4

#define B_BACK			0
#define UNSUCCESSFUL	7

//Printing Spacings
#define SHOP_SLOT_WIDTH		32
#define SHOP_SCREEN_PADDING	6
#define SHOP_SLOT_HEIGHT	18

void openBuyScreen(Player* pPlayer);

Stock* getStocksFromType(int nWeaponType);
char* getSpriteFromStock(Stock sShopStock);

void printTopShopBorders(int nCols);
void printBottomShopBorder(int nCols);
void printShopContent(Stock sShopStock, int nLine);
void printWeaponSprite(Stock sShopStock, int nLine);

void displayBuyStocks(int nPrompt, Player* pPlayer, Stock* sStockList);
void displayBuyTypes(int nPrompt, Player* pPlayer);





#endif
