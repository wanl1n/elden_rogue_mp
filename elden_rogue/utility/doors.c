#include "doors.h"
#include "../screens/areas_screen.h"

Door* createDoorArray(int nArea) {
	
	Door sDoor;
	Door* pDoorList;

	int i;

	Door aStormveilDoors[4] = {{STORMVEIL, 1, 1, 0, NULL, NULL},
							   {STORMVEIL, 2, 6, 3, NULL, NULL},
							   {STORMVEIL, 2, 0, 3, NULL, NULL},
							   {STORMVEIL, 3, 6, 2, NULL, NULL}};

	Door aRayaDoors[8] = {{RAYA_LUCARIA, 1, 4, 2, NULL, NULL},
					   	  {RAYA_LUCARIA, 2, 0, 1, NULL, NULL},
					   	  {RAYA_LUCARIA, 2, 3, 2, NULL, NULL},
					   	  {RAYA_LUCARIA, 3, 3, 0, NULL, NULL},
					   	  {RAYA_LUCARIA, 3, 3, 4, NULL, NULL},
					  	  {RAYA_LUCARIA, 4, 2, 0, NULL, NULL},
					   	  {RAYA_LUCARIA, 3, 0, 2, NULL, NULL},
					  	  {RAYA_LUCARIA, 5, 7, 3, NULL, NULL}};

	Door aRedmaneDoors[12] = {{REDMANE_CASTLE, 1, 4, 1, NULL, NULL},
					   		  {REDMANE_CASTLE, 2, 1, 0, NULL, NULL},
					   		  {REDMANE_CASTLE, 2, 1, 6, NULL, NULL},
					   		  {REDMANE_CASTLE, 3, 2, 0, NULL, NULL},
					   		  {REDMANE_CASTLE, 3, 0, 2, NULL, NULL},
					   		  {REDMANE_CASTLE, 4, 4, 3, NULL, NULL},
					  		  {REDMANE_CASTLE, 4, 2, 0, NULL, NULL},
					  		  {REDMANE_CASTLE, 5, 1, 4, NULL, NULL},
					  		  {REDMANE_CASTLE, 5, 1, 0, NULL, NULL},
					  		  {REDMANE_CASTLE, 6, 7, 3, NULL, NULL},
					  		  {REDMANE_CASTLE, 6, 1, 3, NULL, NULL},
					  		  {REDMANE_CASTLE, 7, 2, 0, NULL, NULL}};

	Door aVolcanoDoors[12] = {{VOLCANO_MANOR, 1, 2, 0, NULL, NULL},
					   		  {VOLCANO_MANOR, 2, 6, 3, NULL, NULL},
					   		  {VOLCANO_MANOR, 2, 3, 0, NULL, NULL},
					   		  {VOLCANO_MANOR,21, 2, 4, NULL, NULL},
					   		  {VOLCANO_MANOR, 2, 0, 3, NULL, NULL},
					   		  {VOLCANO_MANOR, 3, 0, 1, NULL, NULL},
					   		  {VOLCANO_MANOR, 2, 3, 6, NULL, NULL},
					  		  {VOLCANO_MANOR,22, 2, 0, NULL, NULL},
					  		  {VOLCANO_MANOR,22, 0, 3, NULL, NULL},
					  		  {VOLCANO_MANOR,221,3, 1, NULL, NULL},
					  		  {VOLCANO_MANOR, 3, 7, 1, NULL, NULL},
					  		  {VOLCANO_MANOR, 4, 6, 2, NULL, NULL}};

	Door aLeyndellDoors[34] = {{LEYNDELL_CAPITAL, 1, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 2, 6, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 2, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 3, 4, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL, 3, 2, 4, NULL, NULL},
							   {LEYNDELL_CAPITAL, 4, 1, 0, NULL, NULL},
							   {LEYNDELL_CAPITAL, 4, 0, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL, 5, 3,13, NULL, NULL},
							   {LEYNDELL_CAPITAL, 5, 3, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL,51, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 5, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL,52, 6, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 5, 0, 7, NULL, NULL},
							   {LEYNDELL_CAPITAL,53, 6, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 5, 0,13, NULL, NULL},
							   {LEYNDELL_CAPITAL,54, 6, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL,52, 3, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL,53, 3, 0, NULL, NULL},
							   {LEYNDELL_CAPITAL,53, 3, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL,54, 3, 0, NULL, NULL},
							   {LEYNDELL_CAPITAL,52, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 6, 3, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL,53, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 6, 3, 7, NULL, NULL},
							   {LEYNDELL_CAPITAL,54, 0, 1, NULL, NULL},
							   {LEYNDELL_CAPITAL, 6, 3,13, NULL, NULL},
							   {LEYNDELL_CAPITAL, 6, 0, 7, NULL, NULL},
							   {LEYNDELL_CAPITAL, 7, 6,11, NULL, NULL},
							   {LEYNDELL_CAPITAL, 7, 1, 6, NULL, NULL},
							   {LEYNDELL_CAPITAL,71, 0, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL, 7, 9, 0, NULL, NULL},
							   {LEYNDELL_CAPITAL,72, 1, 2, NULL, NULL},
							   {LEYNDELL_CAPITAL, 7, 9,12, NULL, NULL},
							   {LEYNDELL_CAPITAL,73, 1, 0, NULL, NULL}};

	Door aThroneDoors[4] = {{STORMVEIL, 1, 0, 1, NULL, NULL},
						    {STORMVEIL, 2, 6, 3, NULL, NULL},
						    {STORMVEIL, 2, 0, 3, NULL, NULL},
						    {STORMVEIL, 3, 8, 1, NULL, NULL}};

	//Create a Door Array depending on area.
	switch(nArea) {
		
		case STORMVEIL:
			
			pDoorList = malloc(sizeof(aStormveilDoors));
			for(i = 0; i < (sizeof(aStormveilDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aStormveilDoors[i];
			}

			break;

		case RAYA_LUCARIA:
			
			pDoorList = malloc(sizeof(aRayaDoors));
			for(i = 0; i < (sizeof(aRayaDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aRayaDoors[i];
			}

			break;

		case REDMANE_CASTLE:
			
			pDoorList = malloc(sizeof(aRedmaneDoors));
			for(i = 0; i < (sizeof(aRedmaneDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aRedmaneDoors[i];
			}

			break;

		case VOLCANO_MANOR:
			
			pDoorList = malloc(sizeof(aVolcanoDoors));
			for(i = 0; i < (sizeof(aVolcanoDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aVolcanoDoors[i];
			}

			break;

		case LEYNDELL_CAPITAL:
			
			pDoorList = malloc(sizeof(aLeyndellDoors));
			for(i = 0; i < (sizeof(aLeyndellDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aLeyndellDoors[i];
			}

			break;

		case THE_ELDEN_THRONE:
			
			pDoorList = malloc(sizeof(aThroneDoors));
			for(i = 0; i < (sizeof(aThroneDoors) / sizeof(Door)); i++) {
				*(pDoorList + i) = aThroneDoors[i];
			}

			break;
	}
	return pDoorList;
}

Door* findDoor(Door* pDoorList, int nArea, int nFloor, int nRow, int nCol) {

	int nDoors, i;

	switch(nArea) {
		
		case STORMVEIL:

			nDoors = 4;
			break;

		case RAYA_LUCARIA:
			
			nDoors = 8;
			break;

		case REDMANE_CASTLE:
			
			nDoors = 12;
			break;

		case VOLCANO_MANOR:
			
			nDoors = 12;
			break;

		case LEYNDELL_CAPITAL:
			
			nDoors = 34;
			break;

		case THE_ELDEN_THRONE:
			
			nDoors = 4;
			break;
	}

	for (i = 0; i < nDoors; i++) {
		if ((pDoorList + i)->nFloorNumber == nFloor) {
			if ((pDoorList + i)->nRow == nRow &&
				(pDoorList + i)->nCol == nCol) {
				return (pDoorList + i);
			}
		}
	}

	return NULL;
}

Door* createNodeFromDoor (Door sDoor) {

	Door* pDoorNode = malloc(sizeof(Door));

	pDoorNode->nArea = sDoor.nArea;
	pDoorNode->nFloorNumber = sDoor.nFloorNumber;
	pDoorNode->nRow = sDoor.nRow;
	pDoorNode->nCol = sDoor.nCol;

	pDoorNode->pDoorForward = sDoor.pDoorForward;
	pDoorNode->pDoorBack = sDoor.pDoorBack;

	return pDoorNode;
}

void connectDoors(Door* pDoorList, Door* pDoorArray, int nIndex) {
	
	Door* pDoorOne;
	Door* pDoorTwo;

	pDoorOne = createNodeFromDoor(*(pDoorArray + nIndex));
	pDoorTwo = createNodeFromDoor(*(pDoorArray + (nIndex + 1)));

	pDoorOne->pDoorForward = pDoorTwo;
	pDoorOne->pDoorBack = NULL;

	pDoorTwo->pDoorBack = pDoorOne;
	pDoorTwo->pDoorForward = NULL;

	*(pDoorList + nIndex) = *pDoorOne;
	*(pDoorList + (nIndex + 1)) = *pDoorTwo;

}

Door* createConnectedDoorList (int nArea) {
	
	Door* pDoorList;
	Door* pDoorArray;

	//Reusable Variables
	int i;
	int nDoorConnections;

	switch(nArea) {
		
		case STORMVEIL:

			pDoorArray = createDoorArray(STORMVEIL);
			pDoorList = malloc(sizeof(Door) * 4);
			nDoorConnections = 2;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}
				
			break;

		case RAYA_LUCARIA:
			
			pDoorArray = createDoorArray(RAYA_LUCARIA);
			pDoorList = malloc(sizeof(Door) * 8);
			nDoorConnections = 4;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}

			break;

		case REDMANE_CASTLE:
			
			pDoorArray = createDoorArray(REDMANE_CASTLE);
			pDoorList = malloc(sizeof(Door) * 12);
			nDoorConnections = 6;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}

			break;

		case VOLCANO_MANOR:
			
			pDoorArray = createDoorArray(VOLCANO_MANOR);
			pDoorList = malloc(sizeof(Door) * 12);
			nDoorConnections = 6;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}

			break;

		case LEYNDELL_CAPITAL:
			
			pDoorArray = createDoorArray(LEYNDELL_CAPITAL);
			pDoorList = malloc(sizeof(Door) * 34);
			nDoorConnections = 17;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}

			break;

		case THE_ELDEN_THRONE:
			
			pDoorArray = createDoorArray(THE_ELDEN_THRONE);
			pDoorList = malloc(sizeof(Door) * 4);
			nDoorConnections = 2;

			for (i = 0; i <= nDoorConnections; i+=2) {
				connectDoors(pDoorList, pDoorArray, i);
			}

			break;
	}

	return pDoorList;
}