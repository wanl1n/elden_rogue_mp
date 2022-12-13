// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "title_screen.h" //Contains constants needed for Title Screen.
#include "chara_creation_screen.h" //When Player chooses Play.
#include "roundtable_screen.h" // When Player chooses Continue.
#include "../driver.h" //Contains all the structures used in the code.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openTitleScreen		Opens the Title Screen.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openTitleScreen(Player* pPlayer) {
	displayTitleScreen(3);

	int nInput;

	nInput = scanIntInput(0, 2);

	displayTitleScreen(nInput);

	switch(nInput) {

		case START:

			if (!strcmp(pPlayer->strName, "") || !strcmp(pPlayer->strJobClass, ""))
				openCharacterCreationScreen(pPlayer);
			else
				openRoundTableHoldScreen(pPlayer);
			break;

		case CONTINUE:

			loadData(pPlayer);

			if (!strcmp(pPlayer->strName, "") || !strcmp(pPlayer->strJobClass, "")) {
				printf("You do not have saved data. Redirecting you to character creation.\n");
				openCharacterCreationScreen(pPlayer);
			} else
				openRoundTableHoldScreen(pPlayer);			
			break;

		case EXIT:
			break;
	}
}


void loadData(Player* pPlayer) {

	FILE* fp;
	Slot* pTempHead = malloc(sizeof(Slot));
	Slot* pNewSlot = malloc(sizeof(Slot));

	fp = fopen("saves/save.dat", "rb");

	fread(pPlayer, sizeof(Player), 1, fp); // player stats
	fread(pTempHead, sizeof(Slot), 1, fp); // apply the head

	pPlayer->pInventory = pTempHead; //set head to player inventory

	while(fread(pNewSlot, sizeof(Slot), 1, fp)) {
		pTempHead->pNext = pNewSlot;
		pTempHead = pTempHead->pNext;
		pNewSlot = malloc(sizeof(Slot));
	}

	pTempHead->pNext = NULL;

	fclose(fp);
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayTitleScreen	Prints the User Interface of the Title Screen.
	
	@param	nPrompt		An integer value containing the prompt integer
						code.										   */
void displayTitleScreen(int nPrompt) {
	
	system("cls");

	printf("\e[1;93m					 █                   █\n");
	printf("					  ███             ███\n");
	printf("					     ██	        ██\n");
	printf("					       █████████\n");
	printf("					           █    \n");
	printf("					           █    \n");
	printf("					        ███████  \n");
	printf("					      ██   █   ██ \n");
	printf("					   ███   █████   ███ \n");
	printf("					  █    ██  █  ██    █\n");
	printf("	 _______  _        ______   _______  _          _______  _______  _______           _______ \n");
	printf("	(  ____ %c( %c      (  __  %c (  ____ %c( (    /|  (  ____ )(  ___  )(  ____ %c|%c     /|(  ____ %c\n", 92, 92, 92, 92, 92, 92, 92);
	printf("	| (    %c/| (      | (  %c  )| (    %c/|  %c  ( |  | (    )|| (   ) || (    %c/| )   ( || (    %c/\n", 92, 92, 92, 92, 92, 92);
	printf("	| (__    | |      | |   ) || (__    |   %c | |  | (____)|| |   | || |      | |   | || (__    \n", 92);
	printf("	|  __)   | |      | |   | ||  __)   | (%c %c) |  |     __)| |   | || | ____ | |   | ||  __)   \n", 92, 92);
	printf("	| (      | |      | |   ) || (      | | %c   |  | (%c (   | |   | || | %c_  )| |   | || (      \n", 92, 92, 92);
	printf("	| (____/%c| (____/%c| (__/  )| (____/%c| )  %c  |  | ) %c %c__| (___) || (___) || (___) || (____/%c\n", 92, 92, 92, 92, 92, 92, 92);
	printf("	(_______/(_______/(______/ (_______/|/    )_)  |/   %c__/(_______)(_______)(_______)(_______%c\e[0m\n", 92, 92);
	printf("                                                                                 \n");
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m1\e[0m\e[1;94m]\e[0m \e[1;93mSTART\e[0m    \e[1;94m%c\e[0m\n",186,186);
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m2\e[0m\e[1;94m]\e[0m \e[1;93mCONTINUE\e[0m  \e[1;94m%c\e[0m\n",186,186);
	printf("					      \e[1;94m%c                  %c\e[0m\n",186,186);
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m0\e[0m\e[1;94m]\e[0m \e[1;93mExit\e[0m          \e[1;94m%c\e[0m\n",186,186);

	printf("\n\n");

	switch(nPrompt) {
		case START:
			printSystemMessage("Starting game...");
			break;
		case CONTINUE:
			printSystemMessage("Continuing previously saved progress...");
			break;
		case EXIT:
			printSystemMessage("Exiting game...");
			break;
		default:
			break;
	}

	Sleep(DELAY);
}

