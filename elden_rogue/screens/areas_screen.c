// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "title_screen.h" // When player completes the area.
#include "chara_creation_screen.h" // When player completes the area.
#include "roundtable_screen.h" // When player completes the area.
#include "areas_screen.h" // Contains constants needed for Area Screen.
#include "battle_screen.h" // When Player triggers a battle.
#include "credits_screen.h" // When Player reaches the Credits.

#include "../driver.h" //Contains all the structures used in the code.

#include "../utility/colors.h" // Used for printing with colors.
#include "../utility/printer.h" // Used for printing Interface.
#include "../utility/doors.h" // Used to initialize and link doors.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openAreaScreen		Opens the Area Screen.
	
	@param 	nAreaNumber	An integer value contaning the Area number.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.
						nAreaNumber must be between 1 and 6 inclusive. */
void openAreaScreen(int nAreaNumber, Player* pPlayer) {
	
	// Player Inputs.
	char cPlayerInput;
	char aMoves[] = {'W', 'w', 'A', 'a', 'S', 's', 'D', 'd', 'E', 'e'};


	// Initializing variables.
	int nFloor = 1; 
	int nCleared = 0;
	int nBossClear = 0;
	int nPrompt = -1;

	// Initializing Initial Player Stats. 
	resetPlayerStats(pPlayer);
	
	// Saving player location.
	int* pPlayerLoc = findFastTravelTile(nAreaNumber, nFloor);
	pPlayer->aPlayerLoc[0] = *(pPlayerLoc + 0);
	pPlayer->aPlayerLoc[1] = *(pPlayerLoc + 1);

	while (pPlayer->nPlayerHP > 0 && !nCleared){
		
		printFloorHeader(nAreaNumber);
		printFloorMap(nAreaNumber, nFloor, pPlayer);
		displayUserInterface(pPlayer->nPlayerMaxHP, pPlayer, nPrompt);

		cPlayerInput = scanCharInput(aMoves, 10);

		nPrompt = processInput(cPlayerInput, nAreaNumber, &nFloor, pPlayer, &nCleared, &nBossClear);

	}

	// If the player didn't die.
	if (pPlayer->nPlayerHP > 0) 
		printf("You cleared the area!");
	else {
		resetPlayerStats(pPlayer);
		openRoundTableHoldScreen(pPlayer);
	}
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/* 	processInput		Decides what to do with player input. 

	@param	cInput		A character variable containing the Player's
						input.
	@param	nArea		An integer variable containing the Area number.
	@param	pFloor		An integer pointer variable containing the 
						address of the Floor variable.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param	pCleared	An integer pointer variable containing the 
						address of the Boolean flag in integer form.
	
	@return 			An integer value containing prompt type.

	Pre-condition		nArea value is within 1 to 6.
						nFloor should have a corresponding map 
						(depending on the area number, the integer 
						value is limited.)
						pPlayer should be initiated and all members 
						should have a value.
						pCleared should be 0 initially.				   */
int processInput(char cInput, int nArea, int* pFloor, Player* pPlayer, int* pCleared, int* pBossClear) {

	int nPrompt;

	switch(cInput) {
		case 'W':
		case 'w':
			movePlayerTile(UP, nArea, *pFloor, pPlayer);
			break;

		case 'S':
		case 's':
			movePlayerTile(DOWN, nArea, *pFloor, pPlayer);
			break;

		case 'A':
		case 'a':
			movePlayerTile(LEFT, nArea, *pFloor, pPlayer);
			break;

		case 'D':
		case 'd':
			movePlayerTile(RIGHT, nArea, *pFloor, pPlayer);
			break;

		case 'E':
		case 'e':
			nPrompt = usePlayer(nArea, pFloor, pPlayer, pCleared, pBossClear);
			break;
	}

	return nPrompt;
}

/* 	getFloorMap				Gets the Floor Map given the floor number 
							and area, as well as the length and width 
							of each	floor.

	@param	nArea			An integer variable containing the integer 
							value of the current Area.
	@param	nFloor			An integer variable containing the integer 
							value of the current Floor.
	@param	nFloorLength	An integer pointer variable containing the
							address of the Floor Length.
	@param	nFloorWidth		An integer pointer variable containing the
							address of the Floor Length.

	@return					An integer pointer array containing the
							Tile Map of the given Floor and Area.
	
	Pre-condition			nArea value is within 1 to 6.
							nFloor should have a corresponding map 
							(depending on the area number, the integer 
							value is limited.).
							nFloorLength should point to a variable.
							nFloorWidth should point to a variable.	   */
int* getFloorMap(int nArea, int nFloor, int* nFloorLength, int* nFloorWidth) {

	int* pFloor = malloc(sizeof(int) * MAX_FLOOR_LENGTH * MAX_FLOOR_WIDTH);
	int nRow, nCol;

	//CODE: 11
	int aStormveilFloor1[][3] = {{1, 3, 1}, 
							   {5, 1, 5},
							   {1, 1, 1},
							   {1, 1, 1},
							   {1, 1, 1},
							   {1, 1, 1},
							   {1, 2, 1}};
	//CODE: 12
	int aStormveilFloor2[][7] = {{1, 1, 1, 3, 1, 1, 1}, 
							   {1, 1, 1, 5, 1, 1, 1},
							   {1, 1, 1, 1, 1, 1, 1},
							   {5, 1, 5, 5, 5, 1, 5},
							   {1, 1, 1, 1, 1, 1, 1},
							   {1, 1, 5, 1, 5, 1, 1},
							   {1, 1, 1, 3, 1, 1, 1}};
	//CODE: 13
	int aStormveilFloor3[][5] = {{1, 1, 2, 1, 1}, 
							   {1, 1, 1, 1, 1},
							   {1, 1, 1, 1, 1},
							   {1, 1, 6, 1, 1},
							   {1, 1, 1, 1, 1},
							   {1, 1, 1, 1, 1},
							   {1, 1, 3, 1, 1}};

	//CODE: 21
	int aRayaLucariaFloor1[][5] = {{1, 1, 2, 1, 1},
						  		 {1, 1, 1, 1, 1},
						  		 {1, 1, 1, 1, 1},
						  		 {1, 5, 1, 5, 1},
						  		 {1, 1, 3, 1, 1}};
	//CODE: 22
	int aRayaLucariaFloor2[][3] = {{1, 3, 1}, 
						  		 {5, 1, 1},
						  		 {1, 1, 1},
						  		 {5, 1, 3},
						  		 {1, 1, 1},
						  		 {5, 1, 1},
						 		 {1, 1, 1}};
	//CODE: 23
	int aRayaLucariaFloor3[][5] = {{0, 1, 3, 1, 0}, 
						  		   {0, 1, 5, 1, 0},
						  		   {1, 1, 1, 1, 1},
						  		   {3, 1, 1, 1, 3},
						  		   {1, 1, 1, 1, 1},
						  		   {0, 1, 5, 1, 0},
						 		   {0, 1, 1, 1, 0}};
	//CODE: 24
	int aRayaLucariaFloor4[][6] = {{0, 1, 1, 1, 1, 1}, 
					  		 	 {1, 1, 5, 1, 5, 1},
					  		 	 {3, 1, 1, 1, 1, 1},
					  		 	 {1, 1, 5, 1, 5, 1},
					  		 	 {0, 1, 1, 1, 1, 1}};
	//CODE: 25
	int aRayaLucariaFloorB[][7] = {{0, 0, 1, 2, 1, 0, 0}, 
						  		   {1, 1, 1, 1, 1, 1, 1},
						  		   {1, 5, 1, 5, 1, 5, 1},
						  		   {1, 1, 1, 1, 1, 1, 1},
						  		   {1, 5, 1, 6, 1, 5, 1},
						  		   {1, 1, 1, 1, 1, 1, 1},
						  		   {1, 5, 1, 1, 1, 5, 1},
						  		   {1, 1, 1, 3, 1, 1, 1}};

	//CODE: 31
	int aRedmaneCastleFloor1[][5] = {{1, 1, 1, 1, 1},
							 	   {2, 1, 5, 1, 3},
								   {1, 1, 1, 1, 1}};
	//CODE: 32
	int aRedmaneCastleFloor2[][7] = {{1, 5, 1, 5, 1, 5, 1},
								   {3, 1, 1, 1, 1, 1, 3},
								   {1, 5, 1, 5, 1, 5, 1}};
	//CODE: 33
	int aRedmaneCastleFloor3[][5] = {{1, 1, 3, 1, 1},
							 	   {1, 1, 1, 1, 5},
							 	   {3, 1, 1, 1, 1},
							 	   {1, 1, 1, 1, 5},
								   {1, 5, 1, 5, 1}};
	//CODE: 34
	int aRedmaneCastleFloor4[][7] = {{1, 1, 1, 5, 1, 1, 1},
								   {1, 5, 1, 1, 1, 5, 1},
								   {3, 5, 1, 5, 1, 5, 1},
								   {1, 5, 1, 1, 1, 5, 1},
								   {1, 1, 1, 3, 1, 1, 1}};	
	//CODE: 35
	int aRedmaneCastleFloor5[][5] = {{1, 1, 1, 1, 1},
							 	   {3, 1, 5, 1, 3},
								   {1, 1, 1, 1, 1}};
	//CODE: 36
	int aRedmaneCastleFloor6[][4] = {{1, 1, 1, 1},
							 	   {1, 5, 1, 3},
							 	   {1, 1, 1, 1},
							 	   {5, 1, 5, 0},
							 	   {1, 1, 1, 0},
							 	   {5, 1, 5, 0},
							 	   {1, 1, 1, 1},
							 	   {1, 5, 1, 3},
								   {1, 1, 1, 1}};
	//CODE: 37
	int aRedmaneCastleFloor7[][7] = {{1, 1, 1, 1, 1, 1, 1},
								   {1, 5, 1, 1, 1, 5, 1},
								   {3, 1, 1, 6, 1, 1, 2},
								   {1, 5, 1, 1, 1, 5, 1},
								   {1, 1, 1, 1, 1, 1, 1}};							   

	//CODE: 41
	int aVolcanoManorFloor1[][5] = {{1, 1, 3, 1, 1},
							 	  {1, 1, 1, 1, 1},
							 	  {1, 5, 5, 5, 1},
							 	  {1, 1, 1, 1, 1},
								  {1, 1, 2, 1, 1}};
  	//CODE: 42
  	int aVolcanoManorFloor2[][7] = {{1, 1, 1, 3, 1, 1, 1},
							 	  {1, 1, 1, 5, 1, 1, 1},
							 	  {1, 1, 1, 1, 1, 1, 1},
							 	  {3, 5, 1, 5, 1, 5, 3},
							 	  {1, 1, 1, 1, 1, 1, 1},
							 	  {1, 1, 1, 1, 1, 1, 1},
								  {1, 1, 1, 3, 1, 1, 1}};
	//CODE: 421
	int aVolcanoManorFloor2W[][5] = {{1, 1, 5, 1, 1},
							 	   {1, 1, 1, 1, 1},
							 	   {5, 1, 5, 1, 3},
							 	   {1, 1, 1, 1, 1},
								   {1, 1, 5, 1, 1}};
    //CODE: 422
    int aVolcanoManorFloor2E[][7] = {{0, 1, 1, 3, 1, 1, 0},
							 	   {1, 1, 5, 1, 5, 1, 1},
							 	   {3, 1, 1, 1, 1, 1, 5},
							 	   {1, 1, 5, 1, 5, 1, 1},
								   {0, 1, 1, 1, 1, 1, 0}};
	//CODE: 4221
	int aVolcanoManorFloor2EN[][3] = {{1, 1, 1},
							 	    {1, 5, 1},
							 	    {1, 1, 1},
								    {0, 3, 0}};
    //CODE: 43
    int aVolcanoManorFloor3[][3] = {{1, 3, 1},
							 	  {1, 5, 1},
							 	  {5, 1, 5},
							 	  {1, 1, 1},
							 	  {1, 1, 1},
							 	  {5, 1, 5},
							 	  {1, 1, 1},
							 	  {1, 3, 1}};	
    //CODE: 44
    int aVolcanoManorFloorB[][5] = {{1, 1, 2, 1, 1},
							 	  {1, 1, 1, 1, 1},
							 	  {5, 1, 1, 1, 5},
							 	  {5, 1, 6, 1, 5},
							 	  {5, 1, 1, 1, 5},
							 	  {1, 1, 1, 1, 1},
								  {1, 1, 3, 1, 1}};										   

	//CODE: 51
	int aLeyndellCapitalFloor1[][3] = {{1, 3, 1},
									 {1, 1, 1},
									 {1, 1, 1},
									 {1, 2, 1}};
	//CODE: 52
	int aLeyndellCapitalFloor2[][3] = {{1, 3, 1},
									 {5, 1, 5},
									 {1, 1, 1},
									 {5, 1, 5},
									 {1, 1, 1},
									 {5, 1, 5},
									 {1, 3, 1}};
	//CODE: 53
	int aLeyndellCapitalFloor3[][5] = {{1, 1, 5, 1, 1},
									 {1, 0, 0, 0, 1},
									 {5, 0, 0, 0, 3},
									 {1, 0, 0, 0, 1},
									 {1, 1, 3, 1, 1}}; 
	//CODE: 54
	int aLeyndellCapitalFloor4[][5] = {{1, 1, 3, 1, 1},
									 {3, 1, 1, 1, 1},
									 {1, 5, 1, 5, 1}};
	//CODE: 55
	int aLeyndellCapitalFloor5[][15] = {{5, 3, 5, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1},
										{1, 5, 1, 1, 5, 1, 5, 1, 5, 1, 5, 1, 1, 1, 1},
										{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},  											 
										{1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 1}}; 
	//CODE: 551
	int aLeyndellCapitalFloor5S[][3] = {{1, 3, 1},
									  {1, 1, 1},
									  {5, 5, 5}}; 
	//CODE: 552
	int aLeyndellCapitalFloor5L[][3] = {{0, 3, 0},
									  {5, 5, 5},
									  {1, 1, 1},
									  {1, 1, 3},
									  {1, 1, 1},
									  {5, 5, 5},
									  {0, 3, 0}};											 
	//CODE: 553
	int aLeyndellCapitalFloor5C[][3] = {{0, 3, 0},
									  {5, 1, 5},
									  {5, 1, 5},
									  {3, 1, 3},
									  {5, 1, 5},
									  {5, 1, 5},
									  {0, 3, 0}};
	//CODE: 554
	int aLeyndellCapitalFloor5R[][3] = {{0, 3, 0},
									  {5, 5, 5},
									  {1, 1, 1},
									  {3, 1, 1},
									  {1, 1, 1},
									  {5, 5, 5},
									  {0, 3, 0}};
	//CODE: 56
	int aLeyndellCapitalFloor6[][15] = {{1, 1, 1, 5, 1, 1, 1, 3, 1, 1, 1, 5, 1, 1, 1},
										{1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1},
										{1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1},  											 
										{1, 3, 1, 5, 1, 1, 1, 3, 1, 1, 1, 5, 1, 3, 1}}; 
	//CODE: 57
	int aLeyndellCapitalFloor7[][13] = {{5, 1, 1, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0},
										{1, 1, 1, 5, 1, 1, 3, 1, 0, 0, 0, 0, 0},
										{5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5},  											 
										{3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},  											 
										{5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5},
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
										{5, 1, 1, 1, 1, 5, 3, 5, 1, 1, 1, 1, 5}}; 
	//CODE: 571
	int aLeyndellCapitalFloor7C[][5] = {{0, 1, 3, 1, 0},
									  {5, 1, 1, 1, 5},
									  {1, 1, 1, 1, 1},
									  {5, 1, 6, 1, 5},
									  {1, 1, 1, 1, 1},
									  {5, 1, 1, 1, 5},
									  {0, 1, 2, 1, 0}};
	//CODE: 572
	int aLeyndellCapitalFloor7L[][3] = {{1, 1, 1},
									  {5, 1, 3},
									  {1, 1, 1}};
	//CODE: 573
	int aLeyndellCapitalFloor7R[][3] = {{1, 1, 1},
									  {3, 1, 5},
									  {1, 1, 1}};

	//CODE: 61
	int aTheEldenThroneFloor1[][3] = {{1, 3, 1},
									{1, 1, 1},
									{1, 1, 1},
									{1, 1, 1},
									{1, 5, 1},
									{1, 1, 1},
									{1, 1, 1},
									{1, 1, 1},
									{1, 2, 1}};
	//CODE: 62
	int aTheEldenThroneFloor2[][7] = {{0, 1, 1, 3, 1, 1, 0},
									{1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 6, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1},
									{0, 1, 1, 3, 1, 1, 0}};
	//CODE: 63
	int aTheEldenThroneFloor3[][3] = {{1, 7, 1},
									{5, 1, 5},
									{1, 1, 1},
									{5, 1, 5},
									{1, 5, 1},
									{5, 1, 5},
									{1, 1, 1},
									{5, 1, 5},
									{1, 3, 1}};											
	
	switch(nArea) {
		
		case STORMVEIL:
			
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aStormveilFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aStormveilFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					break;
				case 3:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aStormveilFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					break;
			}

			*nFloorLength = 7;
			
			break;

		case RAYA_LUCARIA:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aRayaLucariaFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 5;
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aRayaLucariaFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 7;
					break;
				case 3:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aRayaLucariaFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 7;
					break;
				case 4:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 6; nCol++) {
							*(pFloor + (nRow * 6) + nCol) = aRayaLucariaFloor4[nRow][nCol];
						}
					}
					*nFloorWidth = 6;
					*nFloorLength = 5;
					break;
				case 5:
					for(nRow = 0; nRow < 8; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aRayaLucariaFloorB[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 8;
					break;
			}
			break;
		case REDMANE_CASTLE:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aRedmaneCastleFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 3;
					break;
				case 2:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aRedmaneCastleFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 3;					
					break;
				case 3:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aRedmaneCastleFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 5;
					break;
				case 4:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aRedmaneCastleFloor4[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 5;
					break;
				case 5:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aRedmaneCastleFloor5[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 3;
					break;
				case 6:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < 4; nCol++) {
							*(pFloor + (nRow * 4) + nCol) = aRedmaneCastleFloor6[nRow][nCol];
						}
					}
					*nFloorWidth = 4;
					*nFloorLength = 9;
					break;
				case 7:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aRedmaneCastleFloor7[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 5;
					break;
			}
			break;
		case VOLCANO_MANOR:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aVolcanoManorFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 5;
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aVolcanoManorFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 7;
					break;
				case 21:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aVolcanoManorFloor2W[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 5;
					break;
				case 22:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aVolcanoManorFloor2E[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 5;
					break;
				case 221:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aVolcanoManorFloor2EN[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 4;
					break;
				case 3:
					for(nRow = 0; nRow < 8; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aVolcanoManorFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 8;
					break;
				case 4:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aVolcanoManorFloorB[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 7;
					break;
			}
			break;
		case LEYNDELL_CAPITAL:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 4;
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 7;
					break;
				case 3:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aLeyndellCapitalFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 5;
					break;
				case 4:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aLeyndellCapitalFloor4[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 3;
					break;
				case 5:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 15; nCol++) {
							*(pFloor + (nRow * 15) + nCol) = aLeyndellCapitalFloor5[nRow][nCol];
						}
					}
					*nFloorWidth = 15;
					*nFloorLength = 4;
					break;
				case 51:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor5S[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 3;
					break;
				case 52:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor5L[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 7;
					break;
				case 53:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor5C[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 7;
					break;
				case 54:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor5R[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 7;
					break;
				case 6:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 15; nCol++) {
							*(pFloor + (nRow * 15) + nCol) = aLeyndellCapitalFloor6[nRow][nCol];
						}
					}
					*nFloorWidth = 15;
					*nFloorLength = 4;
					break;
				case 7:
					for(nRow = 0; nRow < 13; nRow++) {
						for (nCol = 0; nCol < 13; nCol++) {
							*(pFloor + (nRow * 13) + nCol) = aLeyndellCapitalFloor7[nRow][nCol];
						}
					}
					*nFloorWidth = 13;
					*nFloorLength = 13;
					break;
				case 71:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 5; nCol++) {
							*(pFloor + (nRow * 5) + nCol) = aLeyndellCapitalFloor7C[nRow][nCol];
						}
					}
					*nFloorWidth = 5;
					*nFloorLength = 7;
					break;
				case 72:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor7L[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 3;
					break;
				case 73:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aLeyndellCapitalFloor7R[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 3;
					break;
			}
			break;
		case THE_ELDEN_THRONE:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aTheEldenThroneFloor1[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 9;
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < 7; nCol++) {
							*(pFloor + (nRow * 7) + nCol) = aTheEldenThroneFloor2[nRow][nCol];
						}
					}
					*nFloorWidth = 7;
					*nFloorLength = 7;
					break;
				case 3:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < 3; nCol++) {
							*(pFloor + (nRow * 3) + nCol) = aTheEldenThroneFloor3[nRow][nCol];
						}
					}
					*nFloorWidth = 3;
					*nFloorLength = 9;
					break;
			}
			break;
	}

	return pFloor;
}

/* 	findFastTravelTile		Finds the Fast Travel Tile from a given 
							Floor Map.

	@param	nArea			An integer variable containing the integer 
							value of the current Area.
	@param	nFloor			An integer variable containing the integer 
							value of the current Floor.

	@return					An integer pointer array containing the row 
							and column of the Fast Travel Tile.
	
	Pre-condition			nArea value is within 1 to 6.
							nFloor should have a corresponding map 
							(depending on the area number, the integer 
							value is limited.)						   */
int* findFastTravelTile(int nArea, int nFloor) {

	int nLength, nWidth;
	int* pFloor = getFloorMap(nArea, nFloor, &nLength, &nWidth);

	int nRow, nCol;
	int* aSpawnLoc = malloc(sizeof(int) * 2);

	for(nRow = 0; nRow < nLength; nRow++) {
		
		for (nCol = 0; nCol < nWidth; nCol++) {
			
			if (*(pFloor + (nRow * nWidth) + nCol) == TILE_FAST_TRAVEL) {
				aSpawnLoc[0] = nRow;
				aSpawnLoc[1] = nCol;
			}
				
		}
	}
	return aSpawnLoc;
}

/* 	movePlayerTile		Moves the location of Player Tile on the map.

	@param	nArea		An integer variable containing the integer 
						value of the current Area.
	@param	nFloor		An integer variable containing the integer 
						value of the current Floor.

	@return				An integer pointer array containing the row 
						and column of the Fast Travel Tile.
	
	Pre-condition		nArea value is within 1 to 6.
						nFloor should have a corresponding map 
						(depending on the area number, the integer 
						value is limited.)						   */
void movePlayerTile(int nDirection, int nArea, int nFloor, Player* pPlayer) {

	int nLength, nWidth;
	int* pCurrentFloor = getFloorMap(nArea, nFloor, &nLength, &nWidth);

	int nRow = pPlayer->aPlayerLoc[0];
	int nCol = pPlayer->aPlayerLoc[1];

	switch(nDirection) {
		case UP:
			if (pCurrentFloor[((nRow-1) * nWidth) + nCol] != TILE_OUT &&
				nRow - 1 >= 0) {
				nRow--;
			}
			break;
		case DOWN:
			if (pCurrentFloor[((nRow+1) * nWidth) + nCol] != TILE_OUT &&
				nRow + 1 <= nLength-1) {
				nRow++;
			}
			break;
		case RIGHT:
			if (pCurrentFloor[(nRow * nWidth) + nCol+1] != TILE_OUT &&
				nCol + 1 <= nWidth-1) {
				nCol++;
			}
			break;
		case LEFT:
			if (pCurrentFloor[(nRow * nWidth) + nCol-1] != TILE_OUT &&
				nCol - 1 >= 0) {
				nCol--;
			}
			break;
	}

	pPlayer->aPlayerLoc[0] = nRow;
	pPlayer->aPlayerLoc[1] = nCol;

	free(pCurrentFloor);
}	

/*	getRandomBetween	Generate a random number between the parameters.
	
	@param nLower		An integer variable containing the lower bound of
						the random number.
	@param nUpper		An integer variable containing the upper bound
						of the random number.
	
	@return 			An integer value between nLower and nUpper
						inclusive.
	Pre-condition		nLower must be less than nUpper and they should
						both be valid integer values.				   */
int getRandomBetween(int nLower, int nUpper) {
	srand(time(0));

	return (rand() % (nUpper - nLower + 1)) + nLower;
}

/*	getRandomSpawn		Gets a random spawn from the spawn tile.	   

	@returns			Returns what type of spawn the tile spawns.	   */
int getRandomSpawn() {

	int nSpawnRandom = getRandomBetween(1, 100);

	if(nSpawnRandom <= 25) {
		return TREASURE;
	} else {
		return ENEMY;
	}
}

/*	spawnEnemy		Gets a randomly generated enemy based on the Area.
	
	@param nArea 	An integer variable containing the area number.
	
	@return 		Returns a randomly generated enemy given the area.

	Pre-condition 	nArea must be from 1-6 inclusive.				   */
Enemy spawnEnemy(int nArea) {
	
	//Making a new Enemy instance.
	Enemy sEnemy;

	//Setting Enemy type.
	int nEnemyType = getRandomBetween(1, 3);
	sEnemy.nType = nEnemyType;

	//Setting Enemy name.
	char strEnemyNames[][35] = {"Godrick Soldier", "Godrick Archer", "Godrick Knight", 
								"Living Jar", "Glintstone Sorcerer", "Battlemage", 
								"Radahn Soldier", "Radahn Archer", "Radahn Knight", 
								"Man-Serpent", "Mage-Serpent", "Abductor Virgin", 
								"Leyndell Soldier", "Leyndell Archer", "Leyndell Knight"};
	//Calculating which name the Enemy will get depending on Type and Area.
	int nNameIndex = (3 * (nArea - 1)) + (nEnemyType - 1);
	strcpy(sEnemy.strName, strEnemyNames[nNameIndex]);

	//Setting Enemy Stats based on Enemy Type and Area.
	switch(nEnemyType) {
		case 1:
			sEnemy.nHP = getRandomBetween(20, 30);
			sEnemy.nAtk = getRandomBetween(70, 80);
			sEnemy.fPhysDef = 0.20;
			sEnemy.fSorcDef = 0.15;
			sEnemy.fIncanDef = 0.10;
			break;
		case 2:
			sEnemy.nHP = getRandomBetween(25, 35);
			sEnemy.nAtk = getRandomBetween(110, 120);
			sEnemy.fPhysDef = 0.50;
			sEnemy.fSorcDef = 0.15;
			sEnemy.fIncanDef = 0.20;
			break;
		case 3:
			sEnemy.nHP = getRandomBetween(70, 80);
			sEnemy.nAtk = getRandomBetween(120, 130);
			sEnemy.fPhysDef = 0.25;
			sEnemy.fSorcDef = 0.25;
			sEnemy.fIncanDef = 0.20;
			break;
	}

	sEnemy.nMaxHP = sEnemy.nHP;

	return sEnemy;
}

/*	spawnBoss		Gets the boss stats for a specific area.
	
	@param nArea 	An integer variable containing the area number. 
	@param nEldenThroneStage	An integer variable containing the 
								stage number of the boss in The 
								Elden Throne.

	@return 		Returns an Enemy variable containing the boss.

	Pre-condition	nArea must be 1-6 only.
					nEldenThroneStage should only be 0 or 1.		   */
Enemy spawnBoss(int nArea, int nEldenThroneStage) {

	Enemy sEnemy;

	sEnemy.nType = 4; //BOSS TYPE IS 4.

	switch(nArea) {
		case STORMVEIL:
			strcpy(sEnemy.strName, "GODRICK THE GRAFTED");
			sEnemy.nHP = 200;
			sEnemy.nAtk = getRandomBetween(150, 300);
			sEnemy.fPhysDef = 0.35;
			sEnemy.fSorcDef = 0.20;
			sEnemy.fIncanDef = 0.15;
			break;
		case RAYA_LUCARIA:
			strcpy(sEnemy.strName, "RENNALA, QUEEN  OF THE FULL MOON");
			sEnemy.nHP = 400;
			sEnemy.nAtk = getRandomBetween(200, 300);
			sEnemy.fPhysDef = 0.15;
			sEnemy.fSorcDef = 0.35;
			sEnemy.fIncanDef = 0.25;
			break;
		case REDMANE_CASTLE:
			strcpy(sEnemy.strName, "STARSCOURGE RADAHN");
			sEnemy.nHP = 600;
			sEnemy.nAtk = getRandomBetween(200, 400);
			sEnemy.fPhysDef = 0.30;
			sEnemy.fSorcDef = 0.20;
			sEnemy.fIncanDef = 0.20;
			break;
		case VOLCANO_MANOR:
			strcpy(sEnemy.strName, "PRAETOR RYKARD");
			sEnemy.nHP = 600;
			sEnemy.nAtk = getRandomBetween(250, 350);
			sEnemy.fPhysDef = 0.15;
			sEnemy.fSorcDef = 0.25;
			sEnemy.fIncanDef = 0.30;
			break;
		case LEYNDELL_CAPITAL:
			strcpy(sEnemy.strName, "MORGOTT THE OMEN KING");
			sEnemy.nHP = 800;
			sEnemy.nAtk = getRandomBetween(250, 500);
			sEnemy.fPhysDef = 0.35;
			sEnemy.fSorcDef = 0.30;
			sEnemy.fIncanDef = 0.20;
			break;
		case THE_ELDEN_THRONE:
			if (nEldenThroneStage == 1) {
				strcpy(sEnemy.strName, "RADAGON OF THE GOLDEN ORDER");
				sEnemy.nHP = 1000;
				sEnemy.nAtk = getRandomBetween(300, 600);
				sEnemy.fPhysDef = 0.35;
				sEnemy.fSorcDef = 0.25;
				sEnemy.fIncanDef = 0.40;
			} else {
				strcpy(sEnemy.strName, "THE ELDEN BEAST");
				sEnemy.nHP = 1250;
				sEnemy.nAtk = getRandomBetween(450, 900);
				sEnemy.fPhysDef = 0.25;
				sEnemy.fSorcDef = 0.50;
				sEnemy.fIncanDef = 0.40;
			}
			break;
	}

	sEnemy.nMaxHP = sEnemy.nHP;

	return sEnemy;
}

/*	spawnTreasure	Generates the rune rewards from a spawn tile.
	
	@param nArea 	An integer variable containing the area number. 

	@return 		Returns an integer variable containing the amount of 
					runes the Player will earn..

	Pre-condition	nArea must be 1-6 only.							   */
int spawnTreasure(int nArea) {
	int nRewards = getRandomBetween(50, 150) * nArea;

	return nRewards;
}

/*	checkIfTileUsed		Checks if the Player is on a used tile.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nFloor 		An integer variable containing the floor
						number of the current floor.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.
						nFloor should be an integer value.		  	   */
int checkIfTileUsed(Player* pPlayer, int nFloor) {
	
	UsedTile* pUsedTileHead = pPlayer->pUsedTiles;

	while (pUsedTileHead != NULL) {

		if (pUsedTileHead->nFloor == nFloor) {
			if (pUsedTileHead->aCoords[0] == pPlayer->aPlayerLoc[0]) {
				if (pUsedTileHead->aCoords[1] == pPlayer->aPlayerLoc[1]) {
					return 1;
				}
			}
		}

		pUsedTileHead = pUsedTileHead->pNext;
	}

	return 0;
}

/* 	setTileToUsed		Adds a used tile to the Used Tiles List.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param pUsedTileHead	A UsedTile pointer poiting to the UsedTile
							Head.
	@param nFloor 		An integer variable containing the floor number
						of the current floor.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   
						pUsedTileHead should be a valid UsedTile pointer. 
						nFloor should be a valid integer value.		   */
void setTileToUsed(Player* pPlayer, UsedTile** pUsedTileHead, int nFloor) {

	UsedTile* pUsedTile = *pUsedTileHead;
	UsedTile* pNewlyUsedTile = malloc(sizeof(UsedTile));

	pNewlyUsedTile->aCoords[0] = pPlayer->aPlayerLoc[0];
	pNewlyUsedTile->aCoords[1] = pPlayer->aPlayerLoc[1];
	pNewlyUsedTile->nFloor = nFloor;
	pNewlyUsedTile->pNext = NULL;

	if (*pUsedTileHead == NULL) {
		*pUsedTileHead = pNewlyUsedTile;

	} else {
		while (pUsedTile->pNext != NULL) {
			pUsedTile = pUsedTile->pNext;
		}

		pUsedTile->pNext = pNewlyUsedTile;
	}
	
}

/*	resetPlayerStats 	Sets Player stats to initial values when entering
						a new area.

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void resetPlayerStats(Player* pPlayer) {

	int nPlayerHP = pPlayer->nHealth; //for calculating Max HP.
	int nWeaponHP = pPlayer->sEquippedWeapon.nHP; //for calculating Max HP.
	int nPlayerMaxHP = 100 * (nPlayerHP + nWeaponHP) / 2;
	pPlayer->nPlayerMaxHP = nPlayerMaxHP; //Saving Player's Max HP.
	pPlayer->nPlayerHP = nPlayerMaxHP;
	pPlayer->nPotions = 8; // Always start with 8 potions.
	pPlayer->pUsedTiles = NULL;
}

/*	resetPlayerStatsto0	Sets Player stats to 0.

	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void resetPlayerStatsTo0(Player* pPlayer) {
	
	int i;

	pPlayer->nPlayerHP = 0;
	pPlayer->nRunes = 0;

	for (i = 0; i < 6; i++) {
		pPlayer->aShards[i] = 0;
	}
}

/*	usePlayer 			Sets Player stats to initial values when entering
						a new area.
	
	@param nArea 		An integer variable containing the area number. 	
	@param pFloor 		An integer pointer pointing to the integer containing
						the current floor number.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param pCleared 	A Boolean flag (integer pointer) that checks if the 
						area has been cleared or not.
	@param pBossResult	An integer pointer pointing to the result of the 
						boss battle.
	
	@return 			An integer value containing the prompt type.

	Pre-condition		nArea must be 1-6 only.						   
						pFloor should be an integer value.		  	   
						pPlayer should be initiated and all members 
						should have a value.
						pCleared should be either 1 or 0.
						pBossResult should be either 1 or 0.		   */
int usePlayer(int nArea, int* pFloor, Player* pPlayer, int* pCleared, int* pBossResult) {

	//Make a reference map for the current floor.
	int nLength, nWidth;
	int nSpawnTile;
	int nBattleResult = 0;
	int nBattleRewards;
	int* pFloorMap = getFloorMap(nArea, *pFloor, &nLength, &nWidth);

	//Get the tile the player is standing on right now.
	int nTileType = *(pFloorMap + (pPlayer->aPlayerLoc[0] * nWidth) + pPlayer->aPlayerLoc[1]);
	Enemy sEnemy;
	Door* pDoorList;
	Door* pCurrentDoor;

	int nPotions = pPlayer->nPotions;
	int nTileUsed = 0;
	int nSpecialPrompt;

	switch(nTileType) {

		case TILE_EMPTY:

			return TILE_EMPTY;
			break;

		case TILE_SPECIAL:
			
			nTileUsed = checkIfTileUsed(pPlayer, *pFloor);

			if (!nTileUsed) {
				nSpawnTile = getRandomSpawn();

				if (nSpawnTile == TREASURE) {

					int nTreasure = spawnTreasure(nArea);
					pPlayer->nRunes += nTreasure;
					nSpecialPrompt = TILE_TREASURE;
					// printSystemMessage("You got some runes!");

					if (pPlayer->pQuestLine != NULL) {
						// If Twinkle Toes is Active and at Stage 2
						if (pPlayer->pQuestLine->nQuestNumber == 1 && pPlayer->pQuestLine->nQuestStatus == 1 && pPlayer->pQuestLine->nStage == 2) {
							if (nArea == RAYA_LUCARIA) {
								pPlayer->nQuestProgress++;
							}
						}
					}
						
				} else if (nSpawnTile == ENEMY) {

					sEnemy = spawnEnemy(nArea);
					nSpecialPrompt = TILE_ENEMY;

					// printSystemMessage("You encountered an enemy.");
					
					nPotions = pPlayer->nPotions; // To check if Player used any weapons.

					nBattleResult = openBattleScreen(sEnemy, pPlayer, nArea);

					if (nBattleResult){
						
						nBattleRewards = sEnemy.nMaxHP * 2;
						pPlayer->nRunes += nBattleRewards;

						if (pPlayer->pQuestLine != NULL) {
							// If Twinkle Toes is Active and at Stage 1
							if (pPlayer->pQuestLine->nQuestNumber == 1 && pPlayer->pQuestLine->nQuestStatus == 1 && pPlayer->pQuestLine->nStage == 1) {
								if (nArea == STORMVEIL) {
									pPlayer->nQuestProgress++;
								}
							}

							// If Swift Broil is Active and at Stage 1
							if (pPlayer->pQuestLine->nQuestNumber == 2 && pPlayer->pQuestLine->nQuestStatus == 1) {
								// If player did not use any potions during the battle.
								if (pPlayer->pQuestLine->nStage == 1 && pPlayer->nPotions == nPotions)
									pPlayer->nQuestProgress++;
								if (pPlayer->pQuestLine->nStage == 2)
									pPlayer->nQuestProgress++;
							}
						}

					} else {
						resetPlayerStatsTo0(pPlayer);
					}

					displayResultScreen(1, nBattleResult, nBattleRewards);
				}

				setTileToUsed(pPlayer, &(pPlayer->pUsedTiles), *pFloor);

				return nSpecialPrompt;

			} else {

				return TILE_CLEARED;
			}

			break;

		case TILE_DOOR:

			pDoorList = createConnectedDoorList(nArea);
			pCurrentDoor = findDoor(pDoorList, nArea, *pFloor, pPlayer->aPlayerLoc[0], pPlayer->aPlayerLoc[1]);
			
			if (pCurrentDoor->pDoorForward != NULL)
				pCurrentDoor = pCurrentDoor->pDoorForward;
			else
				pCurrentDoor = pCurrentDoor->pDoorBack;

			*pFloor = pCurrentDoor->nFloorNumber;

			pPlayer->aPlayerLoc[0] = pCurrentDoor->nRow;
			pPlayer->aPlayerLoc[1] = pCurrentDoor->nCol;


			free(pDoorList);

			return TILE_DOOR;
			break;

		case TILE_FAST_TRAVEL:
			if(*pFloor == 1) {
				openFastTravelScreen(pPlayer);
			} else if (*pBossResult){
				*pCleared = 1;
				openFastTravelScreen(pPlayer);
			} else {
				printSystemMessage("You haven't cleared the boss.");
			}

			return TILE_FAST_TRAVEL;
			break;

		case TILE_BOSS:
			
			// If boss hasn't been cleared yet, start battle.
			if (!*pBossResult) {
				//If the area is not The Elden Throne, spawn normally.
				if (nArea != THE_ELDEN_THRONE)
					sEnemy = spawnBoss(nArea, 0);
				// If the area is the Elden Throne, check first if first stage or not.
				else { 
					sEnemy = spawnBoss(nArea, 1);
				}
				
				//Return 1 if the player won.
				*pBossResult = openBattleScreen(sEnemy, pPlayer, nArea);

				//If the player won against the boss.
				if (*pBossResult) {
					nBattleRewards = sEnemy.nMaxHP * 5;
					pPlayer->nRunes += nBattleRewards;

					//Set shard to 1.
					pPlayer->aShards[nArea-1] = 1;

					if (pPlayer->pQuestLine != NULL) {
						// If Twinkle Toes is Active and at Stage 3
						if (pPlayer->pQuestLine->nQuestNumber == 1 && pPlayer->pQuestLine->nQuestStatus == 1 && pPlayer->pQuestLine->nStage == 3) {
							if (nArea == REDMANE_CASTLE) {
								pPlayer->nQuestProgress++;
							}
						}

						if (pPlayer->pQuestLine->nQuestNumber == 2 && pPlayer->pQuestLine->nQuestStatus == 1 && pPlayer->pQuestLine->nStage == 3) {
							if (nArea == LEYNDELL_CAPITAL)
								pPlayer->nQuestProgress++;
						}
					}
				} else {

					resetPlayerStatsTo0(pPlayer);
				}


				displayResultScreen(2, *pBossResult, nBattleRewards);
			} else {
				printSystemMessage("You have cleared the boss.");
			}

			return TILE_BOSS;
			break;

		case TILE_CREDITS:

			printSystemMessage("credits now!!!");

			if (*pBossResult){
				displayCredits();
				*pCleared = 1;
			} else {
				printSystemMessage("You haven't cleared the boss.");
			}

			return TILE_CREDITS;
			
			break;
	}

	free(pFloorMap);

	return 0;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayUserInterface	Prints the User Interface of the Area Screen.
	
	@param	nPlayerMaxHP	An integer value containing the Player's 
							Max HP.
	@param	pPlayer			The Player Structure containing all 
							of the Player's statistics and items. 

	Pre-condition			pPlayer should be initiated and all 
							members should have a value.			   */
void displayUserInterface(int nPlayerMaxHP, Player* pPlayer, int nPrompt) {
	
	printPlayerHealth(pPlayer->nPlayerHP, nPlayerMaxHP);
	printItems(pPlayer->nPotions, pPlayer->nRunes);
	printPlayerMoves();

	switch(nPrompt) {
		case TILE_EMPTY:
			printSystemMessage("There's nothing there.");
			break;
		case TILE_TREASURE:
			printSystemMessage("You found some runes!");
			break;
		case TILE_ENEMY:
			printSystemMessage("You encountered an enemy.");
			break;
		case TILE_FAST_TRAVEL:
			printSystemMessage("You fast travelled.");
			break;
		case TILE_DOOR:
			printSystemMessage("You entered another room.");
			break;
		case TILE_BOSS:
			printSystemMessage("You encountered a boss.");
			break;
		case TILE_CREDITS:
			printSystemMessage("Thank you for playing!");
			break;

		case TILE_CLEARED:
			printSystemMessage("You cleared this tile.");
			break;
		default:
			break;

	}
}

/* 	displayResultScreen		Prints the User Interface of the Result
							Screen.
	
	@param	nType			An integer variable containing the Enemy Type.
	@param	nBattleResult	An integer variable containing the result of
							the battle. 
	@param	nRewards		An integer varaible containing the amount of
							runes the Player received.

	Pre-condition			nType should be either 1 or 2.
							nBattleResult should be either 1 or 0.
							nRewards should not exceed maximum Rune 
							amount.   								   */
void displayResultScreen(int nType, int nBattleResult, int nRewards) {
	
	system("cls");
	
	if (nBattleResult) {

		if (nType == 1) {
			printHeader("ENEMY FELLED", 12);
		} else if (nType == 2) {
			printHeader("GREAT ENEMY FELLED", 18);
		}

		printf("\t\tYou gained %d runes.", nRewards);

	} else {

		printHeader("YOU DIED", 8);
	}

	Sleep(2500);
}



// ───────────────────── 〔 PRINTING FUNCTIONS 〕 ────────────────────── //
/* 	printFloorHeader	Prints the name of the area in the header.
	
	@param nArea 		An integer variable containing the area number
						of the current area.

	Pre-condition		nArea should be 1 to 6.						   */
void printFloorHeader(int nArea) {

	system("cls");
	
	//Print Area Name
	switch(nArea) {
		case STORMVEIL:
			printHeader("STORMVEIL CASTLE", 16);
			break;
		case RAYA_LUCARIA:
			printHeader("RAYA LUCARIA", 12);
			break;
		case REDMANE_CASTLE:
			printHeader("REDMANE CASTLE", 14);
			break;
		case VOLCANO_MANOR:
			printHeader("VOLCANO MANOR", 13);
			break;
		case LEYNDELL_CAPITAL:
			printHeader("LEYNDELL CAPITAL", 16);
			break;
		case THE_ELDEN_THRONE:
			printHeader("THE ELDEN THRONE", 16);
			break;
	}
}

/*	printFloorMap	Prints the Floor Map of the current floor the player
					is in.

	@param nArea 	An integer variable containing the area number. 	
	@param nFloor 	An integer variable containing the current floor 
					number.
	@param pPlayer	The Player Structure containing all of the Player's 
					statistics and items.

	Pre-condition	nArea must be 1-6 only.						   
					pFloor should be an integer value.		  	   
					pPlayer should be initiated and all members 
					should have a value.							   */
void printFloorMap(int nArea, int nFloor, Player* pPlayer) {

	int nRow, nCol;
	int nPadding;

	//Get a reference map of the current floor.
	int nLength, nWidth;
	int *pBaseFloor = getFloorMap(nArea, nFloor, &nLength, &nWidth);
	nPadding = ((SCREEN_WIDTH - (nWidth * 4)) / 2) - (nWidth - 2);

	//Put the player in the reference map for printing.
	int pPlayerLoc[2];
	pPlayerLoc[0] = pPlayer->aPlayerLoc[0];
	pPlayerLoc[1] = pPlayer->aPlayerLoc[1];
	*(pBaseFloor + (pPlayerLoc[0] * nWidth) + pPlayerLoc[1]) = TILE_PLAYER;
	
	//Print Board.
	for(nRow = 0; nRow < nLength; nRow++) {
		printMultiple(" ", nPadding);
		for(nCol = 0; nCol < nWidth; nCol++) {
			printBorder(*(pBaseFloor + (nRow * nWidth) + nCol), TOP);
		}
		printf("\n");

		printMultiple(" ", nPadding);
		for(nCol = 0; nCol < nWidth; nCol++) {
			printBorder(*(pBaseFloor + (nRow * nWidth) + nCol), MIDDLE);
		}
		printf("\n");

		printMultiple(" ", nPadding);
		for(nCol = 0; nCol < nWidth; nCol++) {
			printBorder(*(pBaseFloor + (nRow * nWidth) + nCol), BOTTOM);
		}
		printf("\n");
	}
}

/*	printBorder 		Prints the border of the tiles.
	
	@param nType 		An integer variable containing the tile type.
	@param nPosition 	An integer variable containing what type of 
						border to print.

	Pre-condition		nType has to be from 0 to 8.
						nPosition has to be 1 to 3. 				   */
void printBorder(int nType, int nPosition) {
	switch(nPosition) {
		case TOP:
			switch(nType) {
				case TILE_EMPTY:
					colorText(COLOR_TILE_EMPTY);
					printf("┌───┐ ");
					break;

				case TILE_BOSS:
					colorText(COLOR_TILE_BOSS);
					printf("┌───┐ ");
					break;

				case TILE_FAST_TRAVEL:
					colorText(COLOR_TILE_FAST_TRAVEL);
					printf("┌───┐ ");
					break;

				case TILE_DOOR:
					colorText(COLOR_TILE_DOOR);
					printf("┌───┐ ");
					break;

				case TILE_SPECIAL:
					colorText(COLOR_TILE_SPECIAL);
					printf("┌───┐ ");
					break;

				case TILE_OUT:
					colorText(COLOR_TILE_OUT);
					printf("┌┬┬┬┐ ");
					break;

				case TILE_PLAYER:
					colorText(COLOR_TILE_PLAYER);
					printf("╔═══╗ ");
					break;

				case TILE_CREDITS:
					colorText(COLOR_TILE_CREDITS);
					printf("┌───┐ ");
					break;
			}
			break;

		case MIDDLE:
			switch(nType) {
				case TILE_EMPTY:
					colorText(COLOR_TILE_EMPTY);
					printf("│   │ ");
					break;

				case TILE_BOSS:
					colorText(COLOR_TILE_BOSS);
					printf("│ ! │ ");
					break;

				case TILE_FAST_TRAVEL:
					colorText(COLOR_TILE_FAST_TRAVEL);
					printf("│ F │ ");
					break;

				case TILE_DOOR:
					colorText(COLOR_TILE_DOOR);
					printf("│ ▼ │ ");
					break;

				case TILE_SPECIAL:
					colorText(COLOR_TILE_SPECIAL);
					printf("│ ? │ ");
					break;

				case TILE_OUT:
					colorText(COLOR_TILE_OUT);
					printf("│││││ ");
					break;

				case TILE_PLAYER:
					colorText(COLOR_TILE_PLAYER);
					printf("║ ■ ║ ");
					break;

				case TILE_CREDITS:
					colorText(COLOR_TILE_CREDITS);
					printf("│ C │ ");
					break;
			}
			break;

		case BOTTOM:
			switch(nType) {
				case TILE_EMPTY:
					colorText(COLOR_TILE_EMPTY);
					printf("└───┘ ");
					break;

				case TILE_BOSS:
					colorText(COLOR_TILE_BOSS);
					printf("└───┘ ");
					break;

				case TILE_FAST_TRAVEL:
					colorText(COLOR_TILE_FAST_TRAVEL);
					printf("└───┘ ");
					break;

				case TILE_DOOR:
					colorText(COLOR_TILE_DOOR);
					printf("└───┘ ");
					break;

				case TILE_SPECIAL:
					colorText(COLOR_TILE_SPECIAL);
					printf("└───┘ ");
					break;

				case TILE_OUT:
					colorText(COLOR_TILE_OUT);
					printf("└┴┴┴┘ ");
					break;

				case TILE_PLAYER:
					colorText(COLOR_TILE_PLAYER);
					printf("╚═══╝ ");
					break;

				case TILE_CREDITS:
					colorText(COLOR_TILE_CREDITS);
					printf("└───┘ ");
					break;
			}
			break;
	}

	resetColors();
}

/* 	printPlayerHealth 		Prints a health bar.
	
	@param nPlayerHealth 	An integer variable containing the player's
							current health.
	@param nPlayerMaxHP 	An integer variable containing the player's
							max health.

	Pre-condition 			nPlayerHealth should be less than max hp.*/
void printPlayerHealth(int nPlayerHealth, int nPlayerMaxHP) {
	int i;

	nPlayerHealth /= HEADER_WIDTH;
	nPlayerMaxHP /= HEADER_WIDTH;

	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	printf("[HEALTH]: ");
	
	for(i = 0; i < nPlayerHealth; i++) {
		colorText(COLOR_TILE_PLAYER);
		// printf("█ ");
		printf("█");
	}

	for(i = 0; i < (nPlayerMaxHP - nPlayerHealth); i++) {
		colorText(COLOR_TILE_OUT);
		// printf("█ ");
		printf("█");
	}

	resetColors();
}

/* 	printItems 		Prints the players items.
	
	@param nPotions	An integer variable containing the player's potions.
	@param nRunes 	An integer variable containing the player's runes.

	Pre-condition	nPotions cannot be more than 8.					   */
void printItems(int nPotions, int nRunes) {
	
	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	printf("[RUNES]: %d", nRunes);
	printMultiple(" ", SCREEN_PADDING);
	printf("[POTIONS]: %d", nPotions);
}

/* 	printPlayerMoves 	Prints the player's possible moves.			   */
void printPlayerMoves() {
	int nPadding;
	nPadding = SCREEN_PADDING + ((SCREEN_WIDTH - 40) / 2);

	printf("\n\n");

	printMultiple(" ", nPadding);
	colorText(COLOR_CONTROL_ARROW);
	printf("       ┌ A ┐  ┌ W ┐  ┌ S ┐  ┌ D ┐\n");
	resetColors();

	printMultiple(" ", nPadding);
	printf("       ╔───╗  ╔───╗  ╔───╗  ╔───╗\n");

	printMultiple(" ", nPadding);
	printf("       │ ");
	colorText(COLOR_CONTROL_ARROW);
	printf("◄");
	resetColors();
	printf(" │  │ ");
	colorText(COLOR_CONTROL_ARROW);
	printf("▲");
	resetColors();
	printf(" │  │ ");
	colorText(COLOR_CONTROL_ARROW);
	printf("▼");
	resetColors();
	printf(" │  │ ");
	colorText(COLOR_CONTROL_ARROW);
	printf("►");
	resetColors();
	printf(" │\n");

	printMultiple(" ", nPadding);
	colorText(COLOR_CONTROL_DISABLED);
	printf("┌───┐");
	resetColors();
	printf("  ╚───╝  ╚───╝  ╚───╝  ╚───╝  ");
	colorText(COLOR_CONTROL_INTERACT);
	printf("┌ E ┐");
	resetColors();
	printf("\n");

	printMultiple(" ", nPadding);
	printf("╔───╗                              ╔───╗\n");
	
	printMultiple(" ", nPadding);
	printf("│ ");
	colorText(COLOR_CONTROL_DISABLED);
	printf("¤");
	resetColors();
	printf(" │                              │ ");
	colorText(COLOR_CONTROL_INTERACT);
	printf("O");
	resetColors();
	printf(" │\n");

	printMultiple(" ", nPadding);
	printf("╚───╝                              ╚───╝\n");

	resetColors();
}
