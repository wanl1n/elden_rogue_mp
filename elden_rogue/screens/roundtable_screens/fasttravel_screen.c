// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "../roundtable_screen.h" //When player goes back.
#include "../areas_screen.h" //When player fast travels to an area.

#include "../../driver.h" //Contains all the structures used in the code.

#include "../../config/settings.h" //Contains printing settings.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openFastTravelScreen	Opens the Fast Travel Screen.
	
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void openFastTravelScreen(Player* pPlayer) {
	displayFastTravelScreen(7);

	int nInputFastTravel;
	int nSuccessfulTravel = 0;

	while (!nSuccessfulTravel) {
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

				if (pPlayer->aShards[LEYNDELL_CAPITAL-1]) {
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



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	getPlayerShards		Checks how many areas the Player has cleared.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
int getPlayerShards(Player* pPlayer) {
	
	int nShards = 0;
	int i;

	for(i = 0; i < 6; i++) {
		if(pPlayer->aShards[i])
			nShards++;
	}

	return nShards;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayFastTravelScreen		Displays the Fast Travel Screen.
	
	@param nPrompt				An integer variable that contains the 
								Player's input.
	Pre-condition				nPrompt should be an integer value from 
								0 to 6.								   */
void displayFastTravelScreen(int nPrompt) {
	
	system("cls");

	printHeader("FAST TRAVEL", 11);

	printOption(1, "STORMVEIL");
	printOption(2, "RAYA LUCARIA");
	printOption(3, "REDMANE CASTLE");
	printOption(4, "VOLCANO MANOR");
	printOption(5, "LEYNDELL CAPITAL");
	printOption(6, "THE ELDEN THRONE");
	printOption(0, "BACK");
	printf("\n\n");

	//Constants are defined in Roundtable Hold Screen.
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