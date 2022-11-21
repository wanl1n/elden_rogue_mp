#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"

#include "../driver.h"

#include "../config/settings.h"

int* getFloorMap(int nArea, int nFloor) {
	
	int* pFloor = malloc(sizeof(int) * 13 * 15);
	int nRow, nCol;

	//CODE: 11
	int aStormveilFloor1[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0}, 
										   {0, 0, 5, 1, 5, 0, 0},
										   {0, 0, 1, 1, 1, 0, 0},
										   {0, 0, 1, 1, 1, 0, 0},
										   {0, 0, 1, 1, 1, 0, 0},
										   {0, 0, 1, 1, 1, 0, 0},
										   {0, 0, 1, 2, 1, 0, 0}};
	//CODE: 12
	int aStormveilFloor2[][FLOOR_WIDTH] = {{1, 1, 1, 3, 1, 1, 1}, 
										   {1, 1, 1, 5, 1, 1, 1},
										   {1, 1, 1, 1, 1, 1, 1},
										   {5, 1, 5, 5, 5, 1, 5},
										   {1, 1, 1, 1, 1, 1, 1},
										   {1, 1, 5, 1, 5, 1, 1},
										   {1, 1, 1, 4, 1, 1, 1}};
	//CODE: 13
	int aStormveilFloor3[][FLOOR_WIDTH] = {{0, 1, 1, 2, 1, 1, 0}, 
										   {0, 1, 1, 1, 1, 1, 0},
										   {0, 1, 1, 1, 1, 1, 0},
										   {0, 1, 1, 6, 1, 1, 0},
										   {0, 1, 1, 1, 1, 1, 0},
										   {0, 1, 1, 1, 1, 1, 0},
										   {0, 1, 1, 4, 1, 1, 0}};

	//CODE: 21
	int aRayaLucariaFloor1[][FLOOR_WIDTH] = {{0, 1, 1, 2, 1, 1, 0},
									  		 {0, 1, 1, 1, 1, 1, 0},
									  		 {0, 1, 1, 1, 1, 1, 0},
									  		 {0, 1, 5, 1, 5, 1, 0},
									  		 {0, 1, 1, 3, 1, 1, 0}};
	//CODE: 22
	int aRayaLucariaFloor2[][FLOOR_WIDTH] = {{0, 0, 1, 4, 1, 0, 0}, 
									  		 {0, 0, 5, 1, 1, 0, 0},
									  		 {0, 0, 1, 1, 1, 0, 0},
									  		 {0, 0, 5, 1, 3, 0, 0},
									  		 {0, 0, 1, 1, 1, 0, 0},
									  		 {0, 0, 5, 1, 1, 0, 0},
									 		 {0, 0, 1, 1, 1, 0, 0}};
	//CODE: 23
	int aRayaLucariaFloor3[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0}, 
									  		 {0, 0, 1, 5, 1, 0, 0},
									  		 {0, 1, 1, 1, 1, 1, 0},
									  		 {0, 4, 1, 1, 1, 3, 0},
									  		 {0, 1, 1, 1, 1, 1, 0},
									  		 {0, 0, 1, 5, 1, 0, 0},
									 		 {0, 0, 1, 1, 1, 0, 0}};
	//CODE: 24
	int aRayaLucariaFloor4[][FLOOR_WIDTH] = {{0, 1, 1, 1, 1, 1, 0}, 
								  		 	 {1, 1, 5, 1, 5, 1, 0},
								  		 	 {4, 1, 1, 1, 1, 1, 0},
								  		 	 {1, 1, 5, 1, 5, 1, 0},
								  		 	 {0, 1, 1, 1, 1, 1, 0}};
	//CODE: 25
	int aRayaLucariaFloorB[][FLOOR_WIDTH] = {{0, 0, 1, 2, 1, 0, 0}, 
									  		 {1, 1, 1, 1, 1, 1, 1},
									  		 {1, 5, 1, 5, 1, 5, 1},
									  		 {1, 1, 1, 1, 1, 1, 1},
									  		 {1, 5, 1, 6, 1, 5, 1},
									  		 {1, 1, 1, 1, 1, 1, 1},
									  		 {1, 5, 1, 1, 1, 5, 1},
									  		 {1, 1, 1, 4, 1, 1, 1}};

	//CODE: 31
	int aRedmaneCastleFloor1[][FLOOR_WIDTH] = {{0, 1, 1, 1, 1, 1, 0},
										 	   {0, 2, 1, 5, 1, 3, 0},
											   {0, 1, 1, 1, 1, 1, 0}};
	//CODE: 32
	int aRedmaneCastleFloor2[][FLOOR_WIDTH] = {{1, 5, 1, 5, 1, 5, 1},
											   {4, 1, 1, 1, 1, 1, 3},
											   {1, 5, 1, 5, 1, 5, 1}};
	//CODE: 33
	int aRedmaneCastleFloor3[][FLOOR_WIDTH] = {{0, 1, 1, 3, 1, 1, 0},
										 	   {0, 1, 1, 1, 1, 5, 0},
										 	   {0, 4, 1, 1, 1, 1, 0},
										 	   {0, 1, 1, 1, 1, 5, 0},
											   {0, 1, 5, 1, 5, 1, 0}};
	//CODE: 34
	int aRedmaneCastleFloor4[][FLOOR_WIDTH] = {{1, 1, 1, 5, 1, 1, 1},
											   {1, 5, 1, 1, 1, 5, 1},
											   {3, 5, 1, 5, 1, 5, 1},
											   {1, 5, 1, 1, 1, 5, 1},
											   {1, 1, 1, 4, 1, 1, 1}};	
	//CODE: 35
	int aRedmaneCastleFloor5[][FLOOR_WIDTH] = {{0, 1, 1, 1, 1, 1, 0},
										 	   {0, 3, 1, 5, 1, 4, 0},
											   {0, 1, 1, 1, 1, 1, 0}};
	//CODE: 36
	int aRedmaneCastleFloor6[][FLOOR_WIDTH] = {{0, 1, 1, 1, 1, 0, 0},
										 	   {0, 1, 5, 1, 3, 0, 0},
										 	   {0, 1, 1, 1, 1, 0, 0},
										 	   {0, 5, 1, 5, 0, 0, 0},
										 	   {0, 1, 1, 1, 0, 0, 0},
										 	   {0, 5, 1, 5, 0, 0, 0},
										 	   {0, 1, 1, 1, 1, 0, 0},
										 	   {0, 1, 5, 1, 4, 0, 0},
											   {0, 1, 1, 1, 1, 0, 0}};
	//CODE: 37
	int aRedmaneCastleFloor7[][FLOOR_WIDTH] = {{1, 1, 1, 1, 1, 1, 1},
											   {1, 5, 1, 1, 1, 5, 1},
											   {4, 1, 1, 6, 1, 1, 2},
											   {1, 5, 1, 1, 1, 5, 1},
											   {1, 1, 1, 1, 1, 1, 1}};							   

	//CODE: 41
	int aVolcanoManorFloor1[][FLOOR_WIDTH] = {{0, 1, 1, 3, 1, 1, 0},
										 	  {0, 1, 1, 1, 1, 1, 0},
										 	  {0, 1, 5, 5, 5, 1, 0},
										 	  {0, 1, 1, 1, 1, 1, 0},
											  {0, 1, 1, 2, 1, 1, 0}};
  	//CODE: 42
  	int aVolcanoManorFloor2[][FLOOR_WIDTH] = {{1, 1, 1, 3, 1, 1, 1},
										 	  {1, 1, 1, 5, 1, 1, 1},
										 	  {1, 1, 1, 1, 1, 1, 1},
										 	  {3, 5, 1, 5, 1, 5, 3},
										 	  {1, 1, 1, 1, 1, 1, 1},
										 	  {1, 1, 1, 1, 1, 1, 1},
											  {1, 1, 1, 4, 1, 1, 1}};
	//CODE: 421
	int aVolcanoManorFloor2W[][FLOOR_WIDTH] = {{0, 1, 1, 5, 1, 1, 0},
										 	   {0, 1, 1, 1, 1, 1, 0},
										 	   {0, 5, 1, 5, 1, 4, 0},
										 	   {0, 1, 1, 1, 1, 1, 0},
											   {0, 1, 1, 5, 1, 1, 0}};
    //CODE: 422
    int aVolcanoManorFloor2E[][FLOOR_WIDTH] = {{0, 1, 1, 3, 1, 1, 0},
										 	   {1, 1, 5, 1, 5, 1, 1},
										 	   {4, 1, 1, 1, 1, 1, 5},
										 	   {1, 1, 5, 1, 5, 1, 1},
											   {0, 1, 1, 1, 1, 1, 0}};
	//CODE: 4221
	int aVolcanoManorFloor2EN[][FLOOR_WIDTH] = {{0, 0, 1, 1, 1, 0, 0},
										 	    {0, 0, 1, 5, 1, 0, 0},
										 	    {0, 0, 1, 1, 1, 0, 0},
											    {0, 0, 0, 4, 0, 0, 0}};
    //CODE: 43
    int aVolcanoManorFloor3[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0},
										 	  {0, 0, 1, 5, 1, 0, 0},
										 	  {0, 0, 5, 1, 5, 0, 0},
										 	  {0, 0, 1, 1, 1, 0, 0},
										 	  {0, 0, 1, 1, 1, 0, 0},
										 	  {0, 0, 5, 1, 5, 0, 0},
										 	  {0, 0, 1, 1, 1, 0, 0},
										 	  {0, 0, 1, 4, 1, 0, 0}};	
    //CODE: 44
    int aVolcanoManorFloorB[][FLOOR_WIDTH] = {{0, 1, 1, 2, 1, 1, 0},
										 	  {0, 1, 1, 1, 1, 1, 0},
										 	  {0, 5, 1, 1, 1, 5, 0},
										 	  {0, 5, 1, 6, 1, 5, 0},
										 	  {0, 5, 1, 1, 1, 5, 0},
										 	  {0, 1, 1, 1, 1, 1, 0},
											  {0, 1, 1, 4, 1, 1, 0}};										   

	//CODE: 51
	int aLeyndellCapitalFloor1[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0},
												 {0, 0, 1, 1, 1, 0, 0},
												 {0, 0, 1, 1, 1, 0, 0},
												 {0, 0, 1, 2, 1, 0, 0}};
	//CODE: 52
	int aLeyndellCapitalFloor2[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0},
												 {0, 0, 5, 1, 5, 0, 0},
												 {0, 0, 1, 1, 1, 0, 0},
												 {0, 0, 5, 1, 5, 0, 0},
												 {0, 0, 1, 1, 1, 0, 0},
												 {0, 0, 5, 1, 5, 0, 0},
												 {0, 0, 1, 4, 1, 0, 0}};
	//CODE: 53
	int aLeyndellCapitalFloor3[][FLOOR_WIDTH] = {{0, 1, 1, 5, 1, 1, 0},
												 {0, 1, 0, 0, 0, 1, 0},
												 {0, 5, 0, 0, 0, 3, 0},
												 {0, 1, 0, 0, 0, 1, 0},
												 {0, 1, 1, 4, 1, 1, 0}}; 
	//CODE: 54
	int aLeyndellCapitalFloor4[][FLOOR_WIDTH] = {{0, 1, 1, 3, 1, 1, 0},
												 {0, 4, 1, 1, 1, 1, 0},
												 {0, 1, 5, 1, 5, 1, 0}};
	//CODE: 55
	int aLeyndellCapitalFloor5[][15] = {{5, 3, 5, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1},
										{1, 5, 1, 1, 5, 1, 5, 1, 5, 1, 5, 1, 1, 1, 1},
										{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},  											 
										{1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 1}}; 
	//CODE: 551
	int aLeyndellCapitalFloor5S[][FLOOR_WIDTH] = {{0, 0, 1, 4, 1, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 5, 5, 5, 0, 0}}; 
	//CODE: 552
	int aLeyndellCapitalFloor5L[][FLOOR_WIDTH] = {{0, 0, 0, 3, 0, 0, 0},
												  {0, 0, 5, 5, 5, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 1, 1, 3, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 5, 5, 5, 0, 0},
												  {0, 0, 0, 4, 0, 0, 0}};											 
	//CODE: 553
	int aLeyndellCapitalFloor5C[][FLOOR_WIDTH] = {{0, 0, 0, 3, 0, 0, 0},
												  {0, 0, 5, 1, 5, 0, 0},
												  {0, 0, 5, 1, 5, 0, 0},
												  {0, 0, 4, 1, 4, 0, 0},
												  {0, 0, 5, 1, 5, 0, 0},
												  {0, 0, 5, 1, 5, 0, 0},
												  {0, 0, 0, 4, 0, 0, 0}};
	//CODE: 554
	int aLeyndellCapitalFloor5R[][FLOOR_WIDTH] = {{0, 0, 0, 3, 0, 0, 0},
												  {0, 0, 5, 5, 5, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 3, 1, 1, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 5, 5, 5, 0, 0},
												  {0, 0, 0, 4, 0, 0, 0}};
	//CODE: 56
	int aLeyndellCapitalFloor6[][15] = {{1, 1, 1, 5, 1, 1, 1, 3, 1, 1, 1, 5, 1, 3, 1},
										{1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1},
										{1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1},  											 
										{1, 4, 1, 5, 1, 1, 1, 4, 1, 1, 1, 5, 1, 4, 1}}; 
	//CODE: 57
	int aLeyndellCapitalFloor7[][15] = {{0, 5, 1, 1, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
										{0, 1, 1, 1, 5, 1, 1, 3, 1, 0, 0, 0, 0, 0, 0},
										{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  											 
										{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0},  											 
										{0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0},  											 
										{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0},
										{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
										{0, 5, 1, 1, 1, 1, 5, 4, 5, 1, 1, 1, 1, 5, 0}}; 
	//CODE: 571
	int aLeyndellCapitalFloor7C[][FLOOR_WIDTH] = {{0, 0, 1, 4, 1, 0, 0},
												  {0, 5, 1, 1, 1, 5, 0},
												  {0, 1, 1, 1, 1, 1, 0},
												  {0, 5, 1, 6, 1, 5, 0},
												  {0, 1, 1, 1, 1, 1, 0},
												  {0, 5, 1, 1, 1, 5, 0},
												  {0, 0, 1, 2, 1, 0, 0}};
	//CODE: 572
	int aLeyndellCapitalFloor7L[][FLOOR_WIDTH] = {{0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 5, 1, 4, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0}};
	//CODE: 573
	int aLeyndellCapitalFloor7R[][FLOOR_WIDTH] = {{0, 0, 1, 1, 1, 0, 0},
												  {0, 0, 4, 1, 5, 0, 0},
												  {0, 0, 1, 1, 1, 0, 0}};

	//CODE: 61
	int aTheEldenThroneFloor1[][FLOOR_WIDTH] = {{0, 0, 1, 3, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 5, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 1, 2, 1, 0, 0}};
	//CODE: 62
	int aTheEldenThroneFloor2[][FLOOR_WIDTH] = {{0, 1, 1, 3, 1, 1, 0},
												{1, 1, 1, 1, 1, 1, 1},
												{1, 1, 1, 1, 1, 1, 1},
												{1, 1, 1, 6, 1, 1, 1},
												{1, 1, 1, 1, 1, 1, 1},
												{1, 1, 1, 1, 1, 1, 1},
												{0, 1, 1, 4, 1, 1, 0}};
	//CODE: 63
	int aTheEldenThroneFloor3[][FLOOR_WIDTH] = {{0, 0, 1, 7, 1, 0, 0},
												{0, 0, 5, 1, 5, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 5, 1, 5, 0, 0},
												{0, 0, 1, 5, 1, 0, 0},
												{0, 0, 5, 1, 5, 0, 0},
												{0, 0, 1, 1, 1, 0, 0},
												{0, 0, 5, 1, 5, 0, 0},
												{0, 0, 1, 4, 1, 0, 0}};											
	
	switch(nArea) {
		case STORMVEIL:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aStormveilFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aStormveilFloor2[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aStormveilFloor3[nRow][nCol];
						}
					}
					break;
			}
			break;
		case RAYA_LUCARIA:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRayaLucariaFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRayaLucariaFloor2[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRayaLucariaFloor3[nRow][nCol];
						}
					}
					break;
				case 4:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRayaLucariaFloor4[nRow][nCol];
						}
					}
					break;
				case 5:
					for(nRow = 0; nRow < 8; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRayaLucariaFloorB[nRow][nCol];
						}
					}
					break;
			}
			break;
		case REDMANE_CASTLE:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor2[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor3[nRow][nCol];
						}
					}
					break;
				case 4:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor4[nRow][nCol];
						}
					}
					break;
				case 5:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor5[nRow][nCol];
						}
					}
					break;
				case 6:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor6[nRow][nCol];
						}
					}
					break;
				case 7:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aRedmaneCastleFloor7[nRow][nCol];
						}
					}
					break;
			}
			break;
		case VOLCANO_MANOR:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor2[nRow][nCol];
						}
					}
					break;
				case 21:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor2W[nRow][nCol];
						}
					}
					break;
				case 22:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor2E[nRow][nCol];
						}
					}
					break;
				case 221:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor2EN[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 8; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloor3[nRow][nCol];
						}
					}
					break;
				case 4:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aVolcanoManorFloorB[nRow][nCol];
						}
					}
					break;
			}
			break;
		case LEYNDELL_CAPITAL:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor2[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 5; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor3[nRow][nCol];
						}
					}
					break;
				case 4:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor4[nRow][nCol];
						}
					}
					break;
				case 5:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 15; nCol++) {
							*(pFloor + (nRow * 15) + nCol) = aLeyndellCapitalFloor5[nRow][nCol];
						}
					}
					break;
				case 51:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor5S[nRow][nCol];
						}
					}
					break;
				case 52:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor5L[nRow][nCol];
						}
					}
					break;
				case 53:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor5C[nRow][nCol];
						}
					}
					break;
				case 54:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor5R[nRow][nCol];
						}
					}
					break;
				case 6:
					for(nRow = 0; nRow < 4; nRow++) {
						for (nCol = 0; nCol < 15; nCol++) {
							*(pFloor + (nRow * 15) + nCol) = aLeyndellCapitalFloor6[nRow][nCol];
						}
					}
					break;
				case 7:
					for(nRow = 0; nRow < 13; nRow++) {
						for (nCol = 0; nCol < 15; nCol++) {
							*(pFloor + (nRow * 15) + nCol) = aLeyndellCapitalFloor7[nRow][nCol];
						}
					}
					break;
				case 71:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor7C[nRow][nCol];
						}
					}
					break;
				case 72:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor7L[nRow][nCol];
						}
					}
					break;
				case 73:
					for(nRow = 0; nRow < 3; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aLeyndellCapitalFloor7R[nRow][nCol];
						}
					}
					break;
			}
			break;
		case THE_ELDEN_THRONE:
			switch(nFloor) {
				case 1:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aTheEldenThroneFloor1[nRow][nCol];
						}
					}
					break;
				case 2:
					for(nRow = 0; nRow < 7; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aTheEldenThroneFloor2[nRow][nCol];
						}
					}
					break;
				case 3:
					for(nRow = 0; nRow < 9; nRow++) {
						for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
							*(pFloor + (nRow * FLOOR_WIDTH) + nCol) = aTheEldenThroneFloor3[nRow][nCol];
						}
					}
					break;
			}
			break;
	}

	return pFloor;
}

void printFloorMap(int* pFloorMap) {

}

void printUserInterface(int nArea, Player* pPlayer) {
	switch(nArea) {
		case STORMVEIL:
		case RAYA_LUCARIA:
		case REDMANE_CASTLE:
		case VOLCANO_MANOR:
		case LEYNDELL_CAPITAL:
		case THE_ELDEN_THRONE:
			break;
	}
		
}

int* findFastTravelTile(int* nArea, int nLength) {

	int nRow, nCol;
	int* aSpawnLoc = malloc(sizeof(int) * 2);

	for(nRow = 0; nRow < nLength; nRow++) {
		for (nCol = 0; nCol < FLOOR_WIDTH; nCol++) {
			if (*(nArea + (nRow * FLOOR_WIDTH) + nCol) == TILE_FAST_TRAVEL)
				aSpawnLoc[0] = nRow;
				aSpawnLoc[1] = nCol;
		}
	}

	return aSpawnLoc;
}

void openAreaScreen(int nAreaNumber, Player* pPlayer) {
	
	//Player Inputs.
	char cPlayerInput;
	char aMoves[] = {'W', 'w', 'A', 'a', 'S', 's', 'D', 'd', 'E', 'e'};

	//Initializing player's starter HP.
	int nFloor = 1;
	int nPlayerHP = pPlayer->nPlayerHP;
	int nWeaponHP = pPlayer->pEquippedWeapon->nHP;
	int nPlayerMaxHP = 100 * (nPlayerHP + nWeaponHP) / 2;
	
	//Initializing player location.
	int* pFloor = getFloorMap(nAreaNumber, nFloor);
	int nLength = sizeof(pFloor)/sizeof(pFloor[0]);
	int* aPlayerLoc = findFastTravelTile(pFloor, nLength);

	do {
		printFloorMap(pFloor);
		printUserInterface(nAreaNumber, pPlayer);

		cPlayerInput = scanCharInput(aMoves, 10);
	} while (pPlayer->nPlayerHP != 0);

	if (pPlayer->nPlayerHP <= 0) 
		printf("DEAD");
	else
		printf("win");
}	

void goNextDoor(int nFloor){

}		