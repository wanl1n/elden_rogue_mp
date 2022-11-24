#ifndef AREA_SCREEN
#define AREA_SCREEN

//AREAS
#define STORMVEIL			1
#define RAYA_LUCARIA		2
#define REDMANE_CASTLE		3
#define VOLCANO_MANOR		4
#define LEYNDELL_CAPITAL	5	
#define THE_ELDEN_THRONE	6
#define FT_BACK				0	

//MAP AREAS
#define MAX_FLOOR_WIDTH		15
#define MAX_FLOOR_LENGTH	13

//TILE TYPES
#define TILE_EMPTY			1
#define TILE_OUT			0
#define TILE_FAST_TRAVEL	2
#define TILE_DOOR			3
#define TILE_SPECIAL		5
#define TILE_BOSS			6
#define TILE_CREDITS		7
#define TILE_PLAYER			8

//BORDER SIDES
#define TOP 				1
#define MIDDLE				2
#define BOTTOM				3

//PLAYER MOVEMENT
#define UP 					1
#define DOWN				2
#define LEFT 				3
#define RIGHT 				4

//RANDOM SPAWN
#define TREASURE			1
#define ENEMY				0


int* getFloorMap(int nArea, int nFloor, int* nFloorLength, int* nFloorWidth);
void printFloorHeader(int nArea);
void printFloorMap(int nArea, int nFloorLength, Player* pPlayer);
void printBorder(int nType, int nPosition);

void printPlayerHealth(int nPlayerHealth, int nPlayerMaxHP);
void printItems(int nPotions, int nRunes);
void printPlayerMoves();
void printUserInterface(int nPlayerMaxHP, Player* pPlayer);

int* findFastTravelTile(int nArea, int nFloor);

void openAreaScreen(int nAreaNumber, Player* pPlayer);
void processInput(char cInput, int nArea, int nFloor, Player* pPlayer);

void movePlayerTile(int nDirection, int nArea, int nFloor, Player* pPlayer);
void goNextDoor(Door* sDoor);
void goBackDoor(Door* sDoor);

int getRandomBetween(int nLower, int nUpper);
int getRandomSpawn();
Enemy spawnEnemy(int nArea);
int spawnTreasure(int nArea);
void usePlayer(int nArea, int nFloor, Player* pPlayer);

#endif 