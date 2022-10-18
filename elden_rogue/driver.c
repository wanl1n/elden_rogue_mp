#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/prompter.c"
#include "utility/colors.c"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"
#include "screens/"

/*** UI ***/

void displayCharacterCreationScreen(int *pPrompt) {
	
	printf("CHARACTER CREATION\n\n",
			"[1] NAME: \n", //limited to 1 to 25 characters
			"[2] JOB CLASS: \n",
			"[3] CONFIRM\n",
			"[0] BACK\n\n",
			"SYSTEM MESSAGE: \n");
	
	switch(*pPrompt) {
		case PROMPT:
			break;
	}
}

void displayJobScreen(int* pPrompt) {

	printf("JOB CLASS: \n\n",
			"OPTIONS\n",
			"[1] VAGABOND     [4] HERO\n",
			"[2] SAMURAI	  [5] PROPHET\n",
			"[3] WARRIOR	  [6] ASTROLOGER\n\n",
			"SYSTEM MESSAGE: \n");
	
	switch(*pPrompt) {
		case PROMPT:
			break;
	}
}

void displayJobClassScreen(int nJobClass) {

	printf("JOB CLASS: \n\n");

	switch(nJobClass) {
		case VAGABOND:
		case SAMURAI:
		case WARRIOR:
		case HERO:
		case PROPHET:
		case ASTROLOGER:
			printf("ASTROLOGER\n\n",
					"LEVEL			%d 	STRENGTH		%d\n",
					"HEALTH			%d 	INTELLIGENCE	%d\n",
					"ENDURANCE		%d 	FAITH			%d\n",
					"DEXTERITY		%d\n\n",
					"SYSTEM MESSAGE: \n");
			break;
	}

	printf("[0] BACK	[1] CONFIRM\n");
	
}




void openCharacterCreationScreen() {
	displayCharacterCreationScreen(0);
	
	int nInput;

	nInput = scanIntInput(0, 3);

}

void openJobScreen() {
	displayJobScreen(0);

	int nInput;

	//scanner input

	//player can choose what job

	//job class details pop up

	//player either confirms or goes back to choose

	//if back, go back to job screen to choose another job class
	//if confirm, player goes back to chara creation. set and show stats.
		//if confirm again, player continues to roundtable hold
		//if back, player goes back to title screen

	//sPlayer = {};

}

struct sPlayerStats {

	int nJobClass;
	int nLevel;
	int nHealth;
	int nEndurance;
	int nDexterity;
	int nStrength;
	int nIntelligence;
	int nFaith;

};

int main() {

	struct sPlayerStats sPlayer;

	resetColors();
	openTitleScreen();

	return 0;
}