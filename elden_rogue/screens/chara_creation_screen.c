// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "title_screen.h" //When Player Goes Back.
#include "chara_creation_screen.h" //Contains the needed constants.
#include "roundtable_screen.h" // When Player finishes character creation.

#include "../driver.h" //Contains all the structures used in the code.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openCharacterCreationScreen		Opens the Character Creation Screen.
	
	@param	pPlayer					The Player Structure containing all 
									of the Player's statistics and items. 

	Pre-condition					pPlayer should be initiated and all 
									members should have a value.	   */
void openCharacterCreationScreen(Player* pPlayer) {
	
	displayCharacterCreationScreen(6, pPlayer);
	
	int nInput;
	char aInputName[26];
	int nCatcher;

	int nComplete = 0;

	while(!nComplete) {
		nInput = scanIntInput(0, 3);

		switch(nInput) {

			case NAME:

				printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
				printf("What do you want to be called? ► ");
				scanf(" %25[^\n]s", aInputName);
				
				// Catches the excess characters over 25.
				while ((nCatcher = fgetc(stdin)) != '\n' && nCatcher != EOF);

				strcpy(pPlayer->strName, aInputName);
				displayCharacterCreationScreen(SET_NAME, pPlayer);

				break;

			case JOB:

				openJobScreen(pPlayer);
				displayCharacterCreationScreen(SET_JOB, pPlayer);
				break;

			case CC_CONFIRM:

				if (!strcmp(pPlayer->strName, "")) {

					printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
					printf("Please set your name");

					if (!strcmp(pPlayer->strJobClass, ""))
						printf(" and job");
					
					printf(" first.\n");

				} else if (!strcmp(pPlayer->strJobClass, "")) {

					printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
					printf("Please set your job first.\n");

				} else {
					nComplete = 1;
					openRoundTableHoldScreen(pPlayer);
				}
					
				break;

			case CC_BACK:
				strcpy(pPlayer->strName, "");
				strcpy(pPlayer->strJobClass, "");
				pPlayer->nLevel = 0;
				pPlayer->nHealth = 0;
				pPlayer->nEndurance = 0;
				pPlayer->nDexterity = 0;
				pPlayer->nStrength = 0;
				pPlayer->nIntelligence = 0;
				pPlayer->nFaith = 0;

				nComplete = 1;
				openTitleScreen(pPlayer);
				break;
		}	
	}
}

/* 	openJobScreen		Opens the Job Classes Screen.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items. 

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
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
			displayJobScreen(7, pPlayer);
		}
	}
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/* 	setJobClass			Set's the Player's statistics to the chosen Job
						Class statistics.

	@param	nInput		An integer variable containing the integer value
						of the chosen job class.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void setJobClass(int nInput, Player* pPlayer) {

	switch(nInput) {
		case VAGABOND:		
			strcpy(pPlayer->strJobClass, "VAGABOND");
			pPlayer->nLevel = 9;
			pPlayer->nHealth = 15;
			pPlayer->nEndurance = 11;
			pPlayer->nDexterity = 13;
			pPlayer->nStrength = 14;
			pPlayer->nIntelligence = 9;
			pPlayer->nFaith = 9;
			break;
		case SAMURAI:
			strcpy(pPlayer->strJobClass, "SAMURAI");
			pPlayer->nLevel = 9;
			pPlayer->nHealth = 12;
			pPlayer->nEndurance = 13;
			pPlayer->nDexterity = 15;
			pPlayer->nStrength = 12;
			pPlayer->nIntelligence = 9;
			pPlayer->nFaith = 8;
			break;
		case WARRIOR:
			strcpy(pPlayer->strJobClass, "WARRIOR");
			pPlayer->nLevel = 8;
			pPlayer->nHealth = 11;
			pPlayer->nEndurance = 11;
			pPlayer->nDexterity = 16;
			pPlayer->nStrength = 10;
			pPlayer->nIntelligence = 10;
			pPlayer->nFaith = 8;
			break;
		case HERO:
			strcpy(pPlayer->strJobClass, "HERO");
			pPlayer->nLevel = 7;
			pPlayer->nHealth = 14;
			pPlayer->nEndurance = 12;
			pPlayer->nDexterity = 9;
			pPlayer->nStrength = 16;
			pPlayer->nIntelligence = 7;
			pPlayer->nFaith = 8;
			break;
		case PROPHET:
			strcpy(pPlayer->strJobClass, "PROPHET");
			pPlayer->nLevel = 7;
			pPlayer->nHealth = 10;
			pPlayer->nEndurance = 8;
			pPlayer->nDexterity = 10;
			pPlayer->nStrength = 11;
			pPlayer->nIntelligence = 7;
			pPlayer->nFaith = 16;
			break;
		case ASTROLOGER:
			strcpy(pPlayer->strJobClass, "ASTROLOGER");
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



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayCharacterCreationScreen	Prints the User Interface of the 
									Character Creation Screen.
	
	@param	nPrompt					An integer value containing the 
									prompt integer code.
	@param	pPlayer					The Player Structure containing all 
									of the Player's statistics and items. 

	Pre-condition					pPlayer should be initiated and all 
									members should have a value.	   */
void displayCharacterCreationScreen(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("CHARACTER CREATION", 18);

	printMultiple(" ", ((SCREEN_WIDTH - NAME_WIDTH) / 2)+1);
	printf("╓");
	printMultiple("—", NAME_WIDTH);
	printf("╖\n");

	printMultiple(" ", ((SCREEN_WIDTH - NAME_WIDTH) / 2)+1);
	printf("║");
	printMultiple(" ", 2);
	printf("NAME  →  %-*.*s", NAME_WIDTH-13, NAME_WIDTH-13, pPlayer->strName);
	printMultiple(" ", 2);
	printf("║\n");

	printMultiple(" ", ((SCREEN_WIDTH - NAME_WIDTH) / 2)+1);
	printf("╟");
	printMultiple("—", NAME_WIDTH);
	printf("╢\n");
	
	printMultiple(" ", ((SCREEN_WIDTH - NAME_WIDTH) / 2)+1);
	printf("║");
	printMultiple(" ", 2);
	printf("JOB   →  %-*.*s", NAME_WIDTH-13, NAME_WIDTH-13, pPlayer->strJobClass);
	printMultiple(" ", 2);
	printf("║\n");

	printMultiple(" ", ((SCREEN_WIDTH - NAME_WIDTH) / 2)+1);
	printf("╙");
	printMultiple("—", NAME_WIDTH);
	printf("╜\n");

	printOption(1, "NAME");
	printOption(2, "JOB CLASS");
	printOption(3, "CONFIRM");
	printOption(0, "BACK");
	printf("\n\n");
	
	switch(nPrompt) {
		case NAME:
			printSystemMessage("Input your name.");
			break;
		case JOB:
			printSystemMessage("Choose your job.");
			break;
		case CC_CONFIRM:
			printSystemMessage("Saving character...");
			break;
		case CC_BACK:
			printSystemMessage("Going back to title screen...");
			break;
		case SET_NAME:
			printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
			printf("The elder says ►  Nice to meet you, %s.\n", pPlayer->strName);
			break;
		case SET_JOB:
			printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
			printf("The elder says ►  You're a/an %s now.\n", pPlayer->strJobClass);
			break;
		case 6:
			break;
	}

	Sleep(DELAY);
}

/* 	displayJobScreen	Prints the User Interface of the Job List 
						Screen.
	
	@param	nPrompt		An integer value containing the prompt integer
						code.										   
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items. 

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					 */
void displayJobScreen(int nPrompt, Player* pPlayer) {

	system("cls");

	printHeader("JOB CLASS", 9);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("Current Job  ► %s\n\n", pPlayer->strJobClass);

	printOption(1, "VAGABOND");
	printOption(2, "SAMURAI");
	printOption(3, "WARRIOR");
	printOption(4, "HERO");
	printOption(5, "PROPHET");
	printOption(6, "ASTROLOGER");

	printf("\n");
	
	printMultiple(" ", SCREEN_PADDING);
	
	switch(nPrompt) {
		case VAGABOND:
			printSystemMessage("Showing Vagabond stats.");
			break;
		case SAMURAI:
			printSystemMessage("Showing Samurai stats.");
			break;
		case WARRIOR:
			printSystemMessage("Showing Warrior stats.");
			break;
		case HERO:
			printSystemMessage("Showing Hero stats.");
			break;
		case PROPHET:
			printSystemMessage("Showing Prophet stats.");
			break;
		case ASTROLOGER:
			printSystemMessage("Showing Astrologer stats.");
			break;
		case 7:
			break;
	}

	Sleep(DELAY);
}

/* 	displayJobClassScreen	Prints the User Interface of the Job Class 
							Screen.
	
	@param	nJobClass		An integer value containing the Player's
							chosen Job Class.						   */
void displayJobClassScreen(int nJobClass) {
	
	system("cls");

	printHeader("JOB CLASS", 9);

	switch(nJobClass) {
		case VAGABOND:
			printf("\tCLASS TITLE: VAGABOND		   █   ██,,,,,██\n"
				"                          		  █ █  █ : : : █\n"
				"                          		  █ █   █: : :█\n"
				"                          		█ █ █ █  █ : █\n"
				"                          		 █████    █:█\n"
				"                          		   █       █\n"
				"\tLEVEL			09\n"
				"\tHEALTH			15 	ENDURANCE		11\n"
				"\tDEXTERITY		13	STRENGTH		14\n"
				"\tINTELLIGENCE		09 	FAITH			09\n\n");
			break;
		case SAMURAI:
			printf("\tSAMURAI		 █      █\n"
				"       		         ██     ███  \n"
				"       		         █ █    █:█  \n"
				"       		         █:█    █:█  \n"
				"       		        █████  █████\n"
				"       		                 █\n"
				"\tLEVEL			09\n"
				"\tHEALTH			12 	ENDURANCE		13\n"
				"\tDEXTERITY		15	STRENGTH		12\n"
				"\tINTELLIGENCE		09	FAITH			08\n\n");
			break;
		case WARRIOR:
			printf("\tWARRIOR	   █     █\n"
				"       		   ███  █  █\n"
				"       		   █:█    █:█\n"
				"       		   █:█     █:█\n"
				"       		  █████   ████\n"
				"       		    █      ██"
				"\tLEVEL			08\n"
				"\tHEALTH			11 	ENDURANCE		11\n"
				"\tDEXTERITY		16	STRENGTH		10\n"
				"\tINTELLIGENCE		10	FAITH			08\n\n");
			break;
		case HERO:
			printf("\tHERO	 █  █  ██      ███\n"
				"    		█:█ █ █ :█    █ : █\n"
				"    		█:████  ::█ █ : : : █\n"
				"    		 █  █ █ :█  █ : : : █\n"
				"    		    █  ██   █ : : : █\n"
				"    		    █         █ : █\n"
				"    		    █          ███\n"
				"\tLEVEL			07\n"
				"\tHEALTH			14 	ENDURANCE		12\n"
				"\tDEXTERITY		09	STRENGTH		16\n"
				"\tINTELLIGENCE		07	FAITH			08\n\n");
			break;
		case PROPHET:
			printf("\tPROPHET	  █     ████\n"
				"       		 ███   █    █\n"
				"       		  █     █;;█\n"
				"       		  █     █ ██   ███\n"
				"       		  █    ████ ███   █\n"
				"       		  █    █ █    ;   █\n"
				"       		  █    ███████████ \n"
				"\tLEVEL			07\n"
				"\tHEALTH			10 	ENDURANCE		08\n"
				"\tDEXTERITY		10	STRENGTH		11\n"
				"\tINTELLIGENCE		07	FAITH			16\n\n");
			break;
		case ASTROLOGER:
			printf("\tASTROLOGER	   ██         ███\n"
				"          		   ██        █ : █\n"
				"          		   █████    █: : :█\n"
				"          		   ██      █ : : : █\n"
				"          		   ██       █: : :█\n"
				"          		   ██        █ : █\n"
				"          		   ██         ███\n"
				"\tLEVEL			06\n"
				"\tHEALTH			09 	ENDURANCE		09\n"
				"\tDEXTERITY		12	STRENGTH		08\n"
				"\tINTELLIGENCE		16	FAITH			07\n\n");
			break;
	}

	printOption(1, "CONFIRM");
	printOption(0, "BACK");

	printf("\n");
}



