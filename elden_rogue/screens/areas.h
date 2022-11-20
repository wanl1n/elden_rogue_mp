#ifndef AREAS
#define AREAS

//AREAS
#define STORMVEIL			1
#define RAYA_LUCARIA		2
#define REDMANE_CASTLE		3
#define VOLCANO_MANOR		4
#define LEYNDELL_CAPITAL	5	
#define THE_ELDEN_THRONE	6
#define FT_BACK				0	

//MAP AREAS
#define FLOOR_WIDTH			7

//TILE TYPES
#define TILE_EMPTY			1
#define TILE_OUT			0
#define TILE_FAST_TRAVEL	2
#define TILE_DOOR_NEXT		3
#define TILE_DOOR_BACK		4
#define TILE_SPECIAL		5
#define TILE_BOSS			6
#define TILE_CREDITS		7

typedef struct Door {
	
	int nPosX, nPosY;

	struct Area* pDoorBack;
	struct Area* pDoorForward;
} Door;

#endif 