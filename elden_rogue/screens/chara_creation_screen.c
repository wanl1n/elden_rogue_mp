#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"

#include "../driver.h"

#include "../config/settings.h"

void displayCharacterCreationScreen(int pPrompt, Player* pPlayer) {
	
	//system("cls");

	printf("-------CHARACTER CREATION-------\n\n"
			"[1] NAME: %s\n"
			"[2] JOB CLASS: %s\n"
			"[3] CONFIRM\n"
			"[0] BACK\n\n"
			"SYSTEM MESSAGE: ",
			pPlayer->cName, pPlayer->cJobClass);
	
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
			printf("You set your name to %s.", pPlayer->cName);
			break;
		case SET_JOB:
			printf("You set your job to %s.", pPlayer->cJobClass);
			break;
		case 6:
			break;
	}

	printf("\n\nINPUT: ");

	Sleep(DELAY);
}

void displayJobScreen(int pPrompt, Player* pPlayer) {

	//system("cls");

	printf("-------JOB CLASS: %s-------\n\n"
			"OPTIONS:\n"
			"[1] VAGABOND      [4] HERO\n"
			"[2] SAMURAI	  [5] PROPHET\n"
			"[3] WARRIOR	  [6] ASTROLOGER\n\n"
			"SYSTEM MESSAGE: ", pPlayer->cJobClass);
	
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
		case 7:
			break;
	}

	printf("\n\nINPUT: ");

	Sleep(DELAY);
}

void displayJobClassScreen(int nJobClass) {

	printf("-------JOB CLASS: -------\n\n");

	switch(nJobClass) {
		case VAGABOND:
			printf("VAGABOND\n\n"
				"LEVEL			09\n"
				"HEALTH			15 	ENDURANCE		11\n"
				"DEXTERITY		13	STRENGTH		14\n"
				"INTELLIGENCE	09 	FAITH			09\n\n");
			break;
		case SAMURAI:
			printf("SAMURAI\n\n"
				"LEVEL			09\n"
				"HEALTH			12 	ENDURANCE		13\n"
				"DEXTERITY		15	STRENGTH		12\n"
				"INTELLIGENCE	09	FAITH			08\n\n");
			break;
		case WARRIOR:
			printf("WARRIOR\n\n"
				"LEVEL			08\n"
				"HEALTH			11 	ENDURANCE		11\n"
				"DEXTERITY		16	STRENGTH		10\n"
				"INTELLIGENCE	10	FAITH			08\n\n");
			break;
		case HERO:
			printf("HERO\n\n"
				"LEVEL			07\n"
				"HEALTH			14 	ENDURANCE		12\n"
				"DEXTERITY		09	STRENGTH		16\n"
				"INTELLIGENCE	07	FAITH			08\n\n");
			break;
		case PROPHET:
			printf("PROPHET\n\n"
				"LEVEL			07\n"
				"HEALTH			10 	ENDURANCE		08\n"
				"DEXTERITY		10	STRENGTH		11\n"
				"INTELLIGENCE	07	FAITH			16\n\n");
			break;
		case ASTROLOGER:
			printf("ASTROLOGER\n\n"
				"LEVEL			06\n"
				"HEALTH			09 	ENDURANCE		09\n"
				"DEXTERITY		12	STRENGTH		08\n"
				"INTELLIGENCE	16	FAITH			07\n\n");
			break;
	}

	printf("[0] BACK			[1] CONFIRM\n");
	
}

void setJobClass(int nInput, Player* pPlayer) {
	char *cJobClass;

	cJobClass = malloc(sizeof(int) * 10);

	switch(nInput) {
		case VAGABOND:		
			strcpy(pPlayer->cJobClass, "VAGABOND");
			pPlayer->nLevel = 9;
			pPlayer->nHealth = 15;
			pPlayer->nEndurance = 11;
			pPlayer->nDexterity = 13;
			pPlayer->nStrength = 14;
			pPlayer->nIntelligence = 9;
			pPlayer->nFaith = 9;
			break;
		case SAMURAI:
			strcpy(pPlayer->cJobClass, "SAMURAI");
			pPlayer->nLevel = 9;
			pPlayer->nHealth = 12;
			pPlayer->nEndurance = 13;
			pPlayer->nDexterity = 15;
			pPlayer->nStrength = 12;
			pPlayer->nIntelligence = 9;
			pPlayer->nFaith = 8;
			break;
		case WARRIOR:
			strcpy(pPlayer->cJobClass, "WARRIOR");
			pPlayer->nLevel = 8;
			pPlayer->nHealth = 11;
			pPlayer->nEndurance = 11;
			pPlayer->nDexterity = 16;
			pPlayer->nStrength = 10;
			pPlayer->nIntelligence = 10;
			pPlayer->nFaith = 8;
			break;
		case HERO:
			strcpy(pPlayer->cJobClass, "HERO");
			pPlayer->nLevel = 7;
			pPlayer->nHealth = 14;
			pPlayer->nEndurance = 12;
			pPlayer->nDexterity = 9;
			pPlayer->nStrength = 16;
			pPlayer->nIntelligence = 7;
			pPlayer->nFaith = 8;
			break;
		case PROPHET:
			strcpy(pPlayer->cJobClass, "PROPHET");
			pPlayer->nLevel = 7;
			pPlayer->nHealth = 10;
			pPlayer->nEndurance = 8;
			pPlayer->nDexterity = 10;
			pPlayer->nStrength = 11;
			pPlayer->nIntelligence = 7;
			pPlayer->nFaith = 16;
			break;
		case ASTROLOGER:
			strcpy(pPlayer->cJobClass, "ASTROLOGER");
			pPlayer->nLevel = 6;
			pPlayer->nHealth = 9;
			pPlayer->nEndurance = 9;
			pPlayer->nDexterity = 12;
			pPlayer->nStrength = 8;
			pPlayer->nIntelligence = 16;
			pPlayer->nFaith = 7;
			break;
	}
}


void openCharacterCreationScreen(Player* pPlayer) {
	
	int nInput;
	char aInputName[25];
	char aInputJob[10];

	int nComplete = 0;

	while(!nComplete) {
		//printf("chara"); // for debugging purposes
		displayCharacterCreationScreen(6, pPlayer);
		nInput = scanIntInput(0, 3);

		switch(nInput) {
			case NAME:
				printf("NAME: ");
				scanf("%s", aInputName);
				strcpy(pPlayer->cName, aInputName);
				displayCharacterCreationScreen(SET_NAME, pPlayer);
				break;

			case JOB:
				//printf("job option lmao"); //for debugging only
				openJobScreen(pPlayer);
				displayCharacterCreationScreen(SET_JOB, pPlayer);
				break;

			case CC_CONFIRM:
				if (!strcmp(pPlayer->cName, "")) {

					printf("Please set your name");

					if (!strcmp(pPlayer->cJobClass, ""))
						printf(" and job");
					
					printf(" first.\n");

				} else if (!strcmp(pPlayer->cJobClass, "")) {
					printf("Please set your job first.\n");
				} else {
					nComplete = 1;
					openRoundTableHoldScreen(pPlayer);
				}
					
				break;

			case CC_BACK:
				openTitleScreen(pPlayer);
				break;
		}	
	}
}

void openJobScreen(Player* pPlayer) {
	displayJobScreen(7, pPlayer);

	int nInputJob, nChoice;
	int nSetJob = 0;

	while(!nSetJob) {
		nInputJob = scanIntInput(1, 6); //scanner input
		displayJobClassScreen(nInputJob); //player can see the details

		nChoice = scanIntInput(0, 1); //CONFIRM CHOSEN CLASS
		
		if (nChoice) {//confirm
			
			setJobClass(nInputJob, pPlayer);
			nSetJob = 1;

		} else {
			printf("ok u changed ur mind."); //for debugging only
			displayJobScreen(7, pPlayer);
		}
	}
}