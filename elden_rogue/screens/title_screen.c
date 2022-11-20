#include "roundtable_screen.h"
#include "chara_creation_screen.h"
#include "title_screen.h"

#include "../config/settings.h"

#include "../driver.h"

/*********** User Interface *************/
void displayTitleScreen(int pPrompt) {
	
	printf("-------ELDEN ROGUE-------\n\n"
			"[1] START\n"
			"[2] CONTINUE\n"
			"[0] EXIT\n\n"
			"SYSTEM MESSAGE: ");
	
	switch(pPrompt) {
		case START:
			printf("Starting game...");
			break;
		case CONTINUE:
			printf("Continuing previously saved progress...");
			break;
		case EXIT:
			printf("Exiting game...");
			break;
		case 3:
			break;
	}

	printf("\n\nINPUT: ");

	Sleep(DELAY);
}

void openTitleScreen(Player* pPlayer) {
	displayTitleScreen(3);

	int nInput;

	nInput = scanIntInput(0, 2);
	
	switch(nInput) {
		case START:
			openCharacterCreationScreen(pPlayer);
			break;
		case CONTINUE:
			openRoundTableHoldScreen(pPlayer);
			break;
		case EXIT:
			break;
	}
}