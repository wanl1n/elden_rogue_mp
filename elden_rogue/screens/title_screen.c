#include "roundtable_screen.h"
#include "chara_creation_screen.h"
#include "title_screen.h"

#include "../config/settings.h"

#include "../driver.h"

/*********** User Interface *************/
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