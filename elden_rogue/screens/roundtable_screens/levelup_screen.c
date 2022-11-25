#include "../title_screen.h"
#include "../chara_creation_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

void displayLevelUpScreen(int nPrompt, Player* pPlayer, int nRuneCost) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);

	printf("	LEVEL UP:			RUNES: %d\n"
		"	Current Job Class: %s\n\n"
		"	STATISTICS:			[1] HEALTH			%d\n"
		"   LEVEL		%d 		[2] ENDURANCE			%d\n"
		"   RUNE COST		%d		[3] DEXTERITY			%d\n"
		"					[4] STRENGTH			%d\n"
		"					[5] INTELLIGENCE		%d\n"
		"					[6] FAITH			%d\n\n"
		"					[0] BACK\n\n", 
		pPlayer->nRunes, pPlayer->strJobClass,
		pPlayer->nHealth,
		pPlayer->nLevel, pPlayer->nEndurance,
		nRuneCost, pPlayer->nDexterity,
		pPlayer->nStrength, pPlayer->nIntelligence, pPlayer->nFaith);

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
	
	printInputTag();
}

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