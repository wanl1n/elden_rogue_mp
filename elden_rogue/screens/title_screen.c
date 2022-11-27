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



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayTitleScreen	Prints the User Interface of the Title Screen.
	
	@param	nPrompt		An integer value containing the prompt integer
						code.										   */
void displayTitleScreen(int nPrompt) {
	
	system("cls");

	printHeader("ELDEN ROGUE", 11);
	printOption(1, "START");
	printOption(2, "CONTINUE");
	printOption(0, "EXIT");
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
		case 3:
			break;
	}

	printInputTag();

	Sleep(DELAY);
}

