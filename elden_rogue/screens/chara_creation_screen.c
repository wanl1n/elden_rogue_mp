#include "chara_creation_screen.h"
#include "title_screen.h"
#include "..\driver.h"

void displayCharacterCreationScreen(int pPrompt, sPlayer sNewPlayer) {
	
	printf("CHARACTER CREATION\n\n",
			
			"[1] NAME: %s\n", sNewPlayer.cName,
			"[2] JOB CLASS: %s\n", sNewPlayer.cJobClass,
			"[3] CONFIRM\n",
			"[0] BACK\n\n",
			
			"SYSTEM MESSAGE: \n");
	
	switch(pPrompt) {
		case NAME:
			printf("Input your name.");
			break;
		case JOB:
			printf("Choose your job.");
			break;
		case CC_CONFIRM:
			printf("Saving character...");
			break;
		case CC_BACK:
			printf("Going back to title screen...");
			break;
	}

	sleep(DELAY);
}

void displayJobScreen(int pPrompt, sPlayer sNewPlayer) {

	printf("JOB CLASS: %s\n\n", sNewPlayer.cJobClass,
			"OPTIONS\n",
			"[1] VAGABOND     [4] HERO\n",
			"[2] SAMURAI	  [5] PROPHET\n",
			"[3] WARRIOR	  [6] ASTROLOGER\n\n",
			"SYSTEM MESSAGE: \n");
	
	switch(pPrompt) {
		case VAGABOND:
			printf("Showing Vagabond stats...");
			break;
		case SAMURAI:
			printf("Showing Samurai stats...");
			break;
		case WARRIOR:
			printf("Showing Warrior stats...");
			break;
		case HERO:
			printf("Showing Hero stats...");
			break;
		case PROPHET:
			printf("Showing Prophet stats...");
			break;
		case ASTROLOGER:
			printf("Showing Astrologer stats...");
			break;
	}

	sleep(DELAY);
}

void displayJobClassScreen(int nJobClass) {

	printf("JOB CLASS: \n\n");

	switch(nJobClass) {
		case VAGABOND:
			printf("VAGABOND\n\n",
				"LEVEL			09\n",
				"HEALTH			15 	ENDURANCE		11\n",
				"DEXTERITY		13	STRENGTH		14\n",
				"INTELLIGENCE	09 	FAITH			09\n\n");
			break;
		case SAMURAI:
			printf("SAMURAI\n\n",
				"LEVEL			09\n",
				"HEALTH			12 	ENDURANCE		13\n",
				"DEXTERITY		15	STRENGTH		12\n",
				"INTELLIGENCE	09	FAITH			08\n\n");
			break;
		case WARRIOR:
			printf("WARRIOR\n\n",
				"LEVEL			08\n",
				"HEALTH			11 	ENDURANCE		11\n",
				"DEXTERITY		16	STRENGTH		10\n",
				"INTELLIGENCE	10	FAITH			08\n\n");
			break;
		case HERO:
			printf("HERO\n\n",
				"LEVEL			07\n",
				"HEALTH			14 	ENDURANCE		12\n",
				"DEXTERITY		09	STRENGTH		16\n",
				"INTELLIGENCE	07	FAITH			08\n\n");
			break;
		case PROPHET:
			printf("PROPHET\n\n",
				"LEVEL			07\n",
				"HEALTH			10 	ENDURANCE		08\n",
				"DEXTERITY		10	STRENGTH		11\n",
				"INTELLIGENCE	07	FAITH			16\n\n");
			break;
		case ASTROLOGER:
			printf("ASTROLOGER\n\n",
				"LEVEL			06\n",
				"HEALTH			09 	ENDURANCE		09\n",
				"DEXTERITY		12	STRENGTH		08\n",
				"INTELLIGENCE	16	FAITH			07\n\n");
			break;
	}

	// printf("LEVEL			%d\n",
	// 		"HEALTH			%d 	ENDURANCE		%d\n",
	// 		"DEXTERITY		%d	STRENGTH		%d\n",
	// 		"INTELLIGENCE	%d 	FAITH			%d\n\n");

	printf("[0] BACK			[1] CONFIRM\n");
	
}


void openCharacterCreationScreen(sPlayer sNewPlayer) {

	displayCharacterCreationScreen(0);
	
	int nInput;

	nInput = scanIntInput(0, 3);

	switch(nInput) {
		case PROMPT_NAME:
			break;
	}

}

void openJobScreen(sPlayer sNewPlayer) {
	displayJobScreen(0);

	int nInput;

	//scanner input
	nInput = scanIntInput(1, 6);

	//player can choose what job

	//job class details pop up

	//player either confirms or goes back to choose

	//if back, go back to job screen to choose another job class
	//if confirm, player goes back to chara creation. set and show stats.
	//SET PLAYER STATS BASED ON JOB CLASS
	sNewPlayer.cJobClass = "VAGABOND";
	sNewPlayer.nLevel = 9;
	sNewPlayer.nHealth = 15;
	sNewPlayer.nEndurance = 11;
	sNewPlayer.nDexterity = 13;
	sNewPlayer.nStrength = 14;
	sNewPlayer.nIntelligence = 9;
	sNewPlayer.nFaith = 9;

		//if confirm again, player continues to roundtable hold
		openRoundtableHoldScreen(sNewPlayer);
		//if back, player goes back to title screen (reset stats)


}