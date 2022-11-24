#include "areas_screen.h"


int* findDoorTile(int nArea, int nFloor) {
	
	int nLength, nWidth;
	int* pReferenceMap = getFloorMap(nArea, nFloor, &nLength, &nWidth);

	//Check how many doors are present on the floor.
	int nDoorsAmount = 0;

	for(i = 0; i < nLength; i++) {
		for (j = 0; j < nWidth; j++) {
			if (pReferenceMap[(i * nWidth) + j] == TILE_DOOR) {
				nDoorsAmount++;
			}
		}
	}

	//Allocate enough memory for all the doors.
	int* pDoor = malloc(sizeof(int) * 2 * nDoorsAmount);

	int i, j, nCounter;

	nCounter = 0;

	for(i = 0; i < nLength; i++) {
		for (j = 0; j < nWidth; j++) {
			if (pReferenceMap[(i * nWidth) + j] == TILE_DOOR) {
				*(pDoor + (0 + nCounter)) = i;
				*(pDoor + (1 + nCounter)) = j;
				nCounter++;
			}
		}
	}

	return pDoor;
}

Door* createDoor(int nArea, int nFloor) {
	Door sNewDoor = {0, 0, NULL, NULL};

	//Create a Door depending on area and floor number.
	switch(nArea) {
		
		case STORMVEIL:
			
			switch(nFloor) {
				case 1:
					sNewDoor = {STORMVEIL, 1, NULL, NULL};
					break;
				case 2:
					sNewDoor = {STORMVEIL, 2, NULL, NULL};
					break;
				case 3:
					sNewDoor = {STORMVEIL, 3, NULL, NULL};
					break;
			}			
			break;

		case RAYA_LUCARIA:
			switch(nFloor) {
				case 1:
					sNewDoor = {RAYA_LUCARIA, 1,  NULL, NULL};
					break;
				case 2:
					sNewDoor = {RAYA_LUCARIA, 2, NULL, NULL};
					break;
				case 3:
					sNewDoor = {RAYA_LUCARIA, 3, NULL, NULL};
					break;
				case 4:
					sNewDoor = {RAYA_LUCARIA, 4, NULL, NULL};
					break;
				case 5:
					sNewDoor = {RAYA_LUCARIA, 5, NULL, NULL};
					break;
			}
			break;
		case REDMANE_CASTLE:
			switch(nFloor) {
				case 1:
					sNewDoor = {REDMANE_CASTLE, 1, NULL, NULL};
					break;
				case 2:
					sNewDoor = {REDMANE_CASTLE, 2, NULL, NULL};				
					break;
				case 3:
					sNewDoor = {REDMANE_CASTLE, 3, NULL, NULL};
					break;
				case 4:
					sNewDoor = {REDMANE_CASTLE, 4, NULL, NULL};
					break;
				case 5:
					sNewDoor = {REDMANE_CASTLE, 5, NULL, NULL};
					break;
				case 6:
					sNewDoor = {REDMANE_CASTLE, 6, NULL, NULL};
					break;
				case 7:
					sNewDoor = {REDMANE_CASTLE, 7, NULL, NULL};
					break;
			}
			break;
		case VOLCANO_MANOR:
			switch(nFloor) {
				case 1:
					sNewDoor = {VOLCANO_MANOR, 1, NULL, NULL};
					break;
				case 2:
					sNewDoor = {VOLCANO_MANOR, 2, NULL, NULL};
					break;
				case 21:
					sNewDoor = {VOLCANO_MANOR, 21, NULL, NULL};
					break;
				case 22:
					sNewDoor = {VOLCANO_MANOR, 22, NULL, NULL};
					break;
				case 221:
					sNewDoor = {VOLCANO_MANOR, 221, NULL, NULL};
					break;
				case 3:
					sNewDoor = {VOLCANO_MANOR, 3, NULL, NULL};
					break;
				case 4:
					sNewDoor = {VOLCANO_MANOR, 4, NULL, NULL};
					break;
			}
			break;
		case LEYNDELL_CAPITAL:
			switch(nFloor) {
				case 1:
					sNewDoor = {LEYNDELL_CAPITAL, 1, NULL, NULL};
					break;
				case 2:
					sNewDoor = {LEYNDELL_CAPITAL, 2, NULL, NULL};
					break;
				case 3:
					sNewDoor = {LEYNDELL_CAPITAL, 3, NULL, NULL};
					break;
				case 4:
					sNewDoor = {LEYNDELL_CAPITAL, 4, NULL, NULL};
					break;
				case 5:
					sNewDoor = {LEYNDELL_CAPITAL, 5, NULL, NULL};
					break;
				case 51:
					sNewDoor = {LEYNDELL_CAPITAL, 51, NULL, NULL};
					break;
				case 52:
					sNewDoor = {LEYNDELL_CAPITAL, 52, NULL, NULL};
					break;
				case 53:
					sNewDoor = {LEYNDELL_CAPITAL, 53, NULL, NULL};
					break;
				case 54:
					sNewDoor = {LEYNDELL_CAPITAL, 54, NULL, NULL};
					break;
				case 6:
					sNewDoor = {LEYNDELL_CAPITAL, 6, NULL, NULL};
					break;
				case 7:
					sNewDoor = {LEYNDELL_CAPITAL, 7, NULL, NULL};
					break;
				case 71:
					sNewDoor = {LEYNDELL_CAPITAL, 71, NULL, NULL};
					break;
				case 72:
					sNewDoor = {LEYNDELL_CAPITAL, 72, NULL, NULL};
					break;
				case 73:
					sNewDoor = {LEYNDELL_CAPITAL, 73, NULL, NULL};
					break;
			}
			break;
		case THE_ELDEN_THRONE:
			switch(nFloor) {
				case 1:
					sNewDoor = {THE_ELDEN_THRONE, 1, NULL, NULL};
					break;
				case 2:
					sNewDoor = {THE_ELDEN_THRONE, 2, NULL, NULL};
					break;
				case 3:
					sNewDoor = {THE_ELDEN_THRONE, 3, NULL, NULL};
					break;
			}
			break;
	}

}

void addDoor(Door* sHead, int nArea, int nFloor) {
	Door* sTemp = sHead;
	Door* sNew = {nArea, nFloor, }

	while (sTemp->pDoorForward != NULL) {
		sTemp = sTemp->pDoorForward;
	}

	sNew 
	sTemp->pDoorForward = 
}

void createDoorList(int nArea, int nFloor) {

	Door* sDoorHead;
	Door* sNewDoor;

	sDoorHead = createDoor(nArea, 1);
	sNewDoor = createDoor(nArea, 2);

	switch(nArea) {
		case STORMVEIL:
			sDoorHead->pDoorForward = sNewDoor;
	}

}
