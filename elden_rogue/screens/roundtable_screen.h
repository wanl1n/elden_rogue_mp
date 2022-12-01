#ifndef ROUNDTABLE_SCREEN
#define ROUNDTABLE_SCREEN

//ROUNDTABLE SCREEN CHOICES
#define FAST_TRAVEL			1
#define LEVEL_UP			2
#define INVENTORY			3
#define SHOP				4
#define SAVE 				5
#define QUIT_GAME			0

//FAST TRAVEL CHOICES
#define STORMVEIL			1
#define RAYA_LUCARIA		2
#define REDMANE_CASTLE		3
#define VOLCANO_MANOR		4
#define LEYNDELL_CAPITAL	5	
#define THE_ELDEN_THRONE	6
#define FT_BACK				0	

//LEVEL UP CHOICES
#define HEALTH				1	
#define ENDURANCE			2	
#define DEXTERITY			3	
#define STRENGTH			4	
#define INTELLIGENCE		5	
#define FAITH				6

//LEVEL UP PROMPTS
#define INSUFFICIENT_RUNES	7
#define MAXED_OUT			8	

//SHOP OPTIONS
#define BUY_WEAPON			1
#define SELL_WEAPON			2
#define S_BACK				0

void displayRoundTableHoldScreen(int nPrompt, Player* pPlayer);
void displayShop();
void displaySaveScreen(Player* pPlayer);

void openRoundTableHoldScreen(Player* pPlayer);
void openShop(Player* pPlayer);
void openSaveScreen(Player* pPlayer);

#endif 