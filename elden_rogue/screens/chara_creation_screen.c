#include "chara_creation_screen.h"
#include "title_screen.h"

#include "../driver.h"

#include "../config/settings.h"

void displayCharacterCreationScreen(int pPrompt, sPlayer* sNewPlayer) {
	
	printf("CHARACTER CREATION\n\n",
			
			"[1] NAME: %s\n", sNewPlayer->cName,
			"[2] JOB CLASS: %s\n", sNewPlayer->cJobClass,
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
		case SET_NAME:
			printf("You set your name to %s", sNewPlayer->cName);
			break;
		case SET_JOB:
			printf("You set your job to %s", sNewPlayer->cJobClass);
			break;
	}

	sleep(DELAY);
}

void displayJobScreen(int pPrompt, sPlayer* sNewPlayer) {

	printf("JOB CLASS: %s\n\n", sNewPlayer->cJobClass,
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

	printf("[0] BACK			[1] CONFIRM\n");
	
}

void setJobClass(int nInput) {
	char *cJobClass;

	*cJobClass = malloc(sizeof(int) * 10);

	switch(nInput) {
		case VAGABOND:
			strcopy(sNewPlayer->cJobClass, "VAGABOND");
			sNewPlayer->nLevel = 9;
			sNewPlayer->nHealth = 15;
			sNewPlayer->nEndurance = 11;
			sNewPlayer->nDexterity = 13;
			sNewPlayer->nStrength = 14;
			sNewPlayer->nIntelligence = 9;
			sNewPlayer->nFaith = 9;
			break;
		case SAMURAI:
			strcopy(sNewPlayer->cJobClass, "SAMURAI");
			sNewPlayer->nLevel = 9;
			sNewPlayer->nHealth = 12;
			sNewPlayer->nEndurance = 13;
			sNewPlayer->nDexterity = 15;
			sNewPlayer->nStrength = 12;
			sNewPlayer->nIntelligence = 9;
			sNewPlayer->nFaith = 8;
			break;
		case WARRIOR:
			strcopy(sNewPlayer->cJobClass, "WARRIOR");
			sNewPlayer->nLevel = 8;
			sNewPlayer->nHealth = 11;
			sNewPlayer->nEndurance = 11;
			sNewPlayer->nDexterity = 16;
			sNewPlayer->nStrength = 10;
			sNewPlayer->nIntelligence = 10;
			sNewPlayer->nFaith = 8;
			break;
		case HERO:
			strcopy(sNewPlayer->cJobClass, "HERO");
			sNewPlayer->nLevel = 7;
			sNewPlayer->nHealth = 14;
			sNewPlayer->nEndurance = 12;
			sNewPlayer->nDexterity = 9;
			sNewPlayer->nStrength = 16;
			sNewPlayer->nIntelligence = 7;
			sNewPlayer->nFaith = 8;
			break;
		case PROPHET:
			strcopy(sNewPlayer->cJobClass, "PROPHET");
			sNewPlayer->nLevel = 7;
			sNewPlayer->nHealth = 10;
			sNewPlayer->nEndurance = 8;
			sNewPlayer->nDexterity = 10;
			sNewPlayer->nStrength = 11;
			sNewPlayer->nIntelligence = 7;
			sNewPlayer->nFaith = 16;
			break;
		case ASTROLOGER:
			strcopy(sNewPlayer->cJobClass, "ASTROLOGER");
			sNewPlayer->nLevel = 6;
			sNewPlayer->nHealth = 9;
			sNewPlayer->nEndurance = 9;
			sNewPlayer->nDexterity = 12;
			sNewPlayer->nStrength = 8;
			sNewPlayer->nIntelligence = 16;
			sNewPlayer->nFaith = 7;
			break;
	}
}


void openCharacterCreationScreen(sPlayer* sNewPlayer) {

	displayCharacterCreationScreen(0, sNewPlayer);
	
	int nInput;
	char aInputName[25];
	char aInputJob[10];

	int nComplete = 0;

	while(!nComplete) {
		nInput = scanIntInput(0, 3);

		switch(nInput) {
			case NAME:
				scanf("%[^\n]s", nInputName);
				strcopy(*sNewPlayer.cName, nInputName);
				displayCharacterCreationScreen(SET_NAME, sNewPlayer);
				break;
			case JOB:
				openJobScreen(sNewPlayer);
				strcopy(*sNewPlayer.cJobClass, nInputJob);
				displayCharacterCreationScreen(SET_JOB, sNewPlayer);
				break;
			case CC_CONFIRM:
				if (!nComplete) { //If missing name or job
					if (*sNewPlayer.cName == NULL) {
						printf("Please set your name");
						if (*sNewPlayer.cJobClass == NULL)
							printf(" and job");
						printf(" first.\n");
					}
				} else
					printf("openRoundtableHoldScreen();");
				break;
			case CC_BACK:
				openTitleScreen(sNewPlayer);
				break;
		}

		if (*sNewPlayer.cName != NULL && *sNewPlayer.cJobClass != NULL)
			nComplete = 1;
	}
}

void openJobScreen(sPlayer* sNewPlayer) {
	displayJobScreen(0, sNewPlayer);

	int nInputJob, nChoice;
	int nSetJob;

	while(!nSetJob) {
		nInputJob = scanIntInput(1, 6); //scanner input
		displayJobClassScreen(nInput); //player can see the details

		nChoice = scanIntInput(0, 1);
		if (nChoice) {//confirm
			setJobClass(nInputJob, sNewPlayer);
			displayCharacterCreationScreen(SET_JOB, sNewPlayer);
			nSetJob = 1;
		} else {
			displayJobScreen(0, sNewPlayer);
		}
	}
		//if confirm again, player continues to roundtable hold
		//openRoundtableHoldScreen(sNewPlayer);
		//if back, player goes back to title screen (reset stats)


}