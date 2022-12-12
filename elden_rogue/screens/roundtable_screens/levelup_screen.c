// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "../roundtable_screen.h" //When Player goes back.

#include "../../driver.h" //Contains all the structure definitions.

#include "../../config/settings.h" //Contains printing settings.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openLevelUpScreen	Opens the Level Up Screen.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openLevelUpScreen(Player* pPlayer) {

	int nInputLevelUp = 100; //random value basta wala sa choices
	int nRuneCost = (pPlayer->nLevel * 100) / 2;

	displayLevelUpScreen(9, pPlayer, nRuneCost);

	while(nInputLevelUp != 0) {

		nInputLevelUp = scanIntInput(0, 6);

		if (nInputLevelUp == 0) {
			openRoundTableHoldScreen(pPlayer);
		} else if (pPlayer->nRunes >= nRuneCost) {
			levelUp(nInputLevelUp, pPlayer, nRuneCost);
			displayLevelUpScreen(nInputLevelUp, pPlayer, nRuneCost);
		} else {
			displayLevelUpScreen(INSUFFICIENT_RUNES, pPlayer, nRuneCost);
		}

		nRuneCost = (pPlayer->nLevel * 100) / 2; //Calculate new rune cost after level up.
	}
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	levelUp 			Levels up the Player's chosen stat.
	
	@param nStat		An integer variable containing the stat needed
						to level up.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nRuneCost	An integer variable containing the cost of the
						level up.

	Pre-condition		nStat value should be from 1 to 6.
						pPlayer should be initiated and all members 
						should have a value.
						nRuneCost should be an integer value.		   */
void levelUp(int nStat, Player* pPlayer, int nRuneCost) {

	int nSuccess = 0;

	switch(nStat) {
		case HEALTH:
			if (pPlayer->nHealth < 50) {
				pPlayer->nHealth++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case ENDURANCE:
			if (pPlayer->nEndurance < 50) {
				pPlayer->nEndurance++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case DEXTERITY:
			if (pPlayer->nDexterity < 50) {
				pPlayer->nDexterity++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case STRENGTH:
			if (pPlayer->nStrength < 50) {
				pPlayer->nStrength++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case INTELLIGENCE:
			if (pPlayer->nIntelligence < 50) {
				pPlayer->nIntelligence++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;
		case FAITH:
			if (pPlayer->nFaith < 50) {
				pPlayer->nFaith++; //Increase Player Stat by 1.
				nSuccess = 1;
			}
			break;

	}

	if(nSuccess) {
		pPlayer->nLevel++;
		pPlayer->nRunes -= nRuneCost; printf("%d", nRuneCost);
	} else {
		displayLevelUpScreen(MAXED_OUT, pPlayer, nRuneCost);
	}
	
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayLevelUpScreen 	Displays the Level up Screen.
	
	@param nPrompt 			An integer variable containing the player's input 
							from the Level Up Screen.
	@param pPlayer			The Player Structure containing all of the 
							Player's statistics and items.
	@param nRuneCost		An integer variable containing the current page 
							of the inventory the Player is on.

	Pre-condition			nPrompt should be an integer value from 1-9.
							pPlayer should be initiated and all members 
							should have a value.	  					
							nRuneCost should be an integer value.          	   */
void displayLevelUpScreen(int nPrompt, Player* pPlayer, int nRuneCost) {
	
	system("cls");

	printHeader("LEVEL UP", 8);

	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("YOUR RUNES ► %d\n", pPlayer->nRunes);
	printf("\n");

	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("┌ JOB       ► %s \n", pPlayer->strJobClass);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("├ LEVEL     ► %*d  ┬ HEALTH        ► %d \n", 2, pPlayer->nLevel, pPlayer->nHealth);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("│                 ├ ENDURANCE     ► %d \n", pPlayer->nEndurance);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("│                 ├ DEXTERITY     ► %d \n", pPlayer->nDexterity);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("│                 ├ STRENGTH      ► %d \n", pPlayer->nStrength);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("│                 ├ INTELLIGENCE  ► %d \n", pPlayer->nIntelligence);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("│                 ├ FAITH         ► %d \n", pPlayer->nFaith);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("└ RUNE COST ► %d\n", nRuneCost);

	printOption(1, "HEALTH");
	printOption(2, "ENDURANCE");
	printOption(3, "DEXTERITY");
	printOption(4, "STRENGTH");
	printOption(5, "INTELLIGENCE");
	printOption(6, "FAITH");
	printOption(0, "BACK");

	printf("\n");

	switch(nPrompt) {
		case HEALTH:
			printSystemMessage("You have levelled up your Health.");
			break;
		case ENDURANCE:
			printSystemMessage("You have levelled up your Endurance.");
			break;
		case DEXTERITY:
			printSystemMessage("You have levelled up your Dexterity.");
			break;
		case STRENGTH:
			printSystemMessage("You have levelled up your Strength.");
			break;
		case INTELLIGENCE:
			printSystemMessage("You have levelled up your Intelligence.");
			break;
		case FAITH:
			printSystemMessage("You have levelled up your Faith.");
			break;
		case INSUFFICIENT_RUNES:
			printSystemMessage("You don't have enough runes :(");
			break;
		case MAXED_OUT:
			printSystemMessage("You have reached the maximum level for this stat.");
			break;
		case 9:
			break;
	}
}