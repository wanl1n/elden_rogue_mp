#include "../chara_creation_screen.h"
#include "../title_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

//User Interface / Printing Functions
void displayFastTravelScreen(int nPrompt) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);

	printf("\t\tFAST TRAVEL:\n");

	printf("\n\n");
	printOption(1, "STORMVEIL");
	printOption(2, "RAYA LUCARIA");
	printOption(3, "REDMANE CASTLE");
	printOption(4, "VOLCANO MANOR");
	printOption(5, "LEYNDELL CAPITAL");
	printOption(6, "THE ELDEN THRONE");
	printOption(0, "BACK");
	printf("\n\n");

	switch(nPrompt) {
		case STORMVEIL:
			printSystemMessage("Travelling to Stormveil.");
			break;
		case RAYA_LUCARIA:
			printSystemMessage("Travelling to Raya Lucaria.");
			break;
		case REDMANE_CASTLE:
			printSystemMessage("Travelling to Redmane Castle.");
			break;		
		case VOLCANO_MANOR:
			printSystemMessage("Travelling to Volcano Manor.");
			break;
		case LEYNDELL_CAPITAL:
			printSystemMessage("Travelling to Leyndell Capital.");
			break;
		case THE_ELDEN_THRONE:
			printSystemMessage("Travelling to The Elden Throne.");
			break;
		case FT_BACK:
			printSystemMessage("Going back to Roundtable Hold.");
			break;
	}

	Sleep(DELAY);
}

//Utility Functions
int getPlayerShards(Player* pPlayer) {
	
	int nShards = 0;
	int i;

	for(i = 0; i < 6; i++) {
		if(pPlayer->aShards[i])
			nShards++;
	}

	return nShards;
}

//Central Fast Travel Function
void openFastTravelScreen(Player* pPlayer) {
	displayFastTravelScreen(7);

	int nInputFastTravel;
	int nSuccessfulTravel = 0;

	while (!nSuccessfulTravel) {
		printInputTag();
		nInputFastTravel = scanIntInput(0, 6);
	
		displayFastTravelScreen(nInputFastTravel);
	
		switch(nInputFastTravel) {
			case STORMVEIL:
			case RAYA_LUCARIA:
			case REDMANE_CASTLE:
			case VOLCANO_MANOR:
				nSuccessfulTravel = 1;
				openAreaScreen(nInputFastTravel, pPlayer);
				break;
			case LEYNDELL_CAPITAL:
				if (getPlayerShards(pPlayer) >= 2) {
					openAreaScreen(nInputFastTravel, pPlayer);
				} else {
					printSystemMessage("You have to clear 2 stages to unlock.");
				}
				break;
	
			case THE_ELDEN_THRONE:
				if (pPlayer->aShards[LEYNDELL_CAPITAL]) {
					openAreaScreen(nInputFastTravel, pPlayer);
				} else {
					printSystemMessage("You have to clear Leyndell Capital to unlock.");
				}
				break;
	
			case FT_BACK:
				nSuccessfulTravel = 1;
				openRoundTableHoldScreen(pPlayer);
				break;
	
		}
	}
}