#include "..\utility/prompts.h"
#include "chara_creation_screen.h"
#include "..\driver.h"

/*********** User Interface *************/
void displayTitleScreen(int pPrompt) {
	
	printf("ELDEN ROGUE\n\n",
			"[1] START\n",
			"[2] CONTINUE\n",
			"[0] EXIT\n\n",
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
	}

	sleep(DELAY);
}

void openTitleScreen(sPlayer sNewPlayer) {
	displayTitleScreen(0);

	int nInput;

	nInput = scanIntInput(0, 2);
	
	switch(nInput) {
		case START:
			openCharacterCreationScreen(sNewPlayer);
			break;
		case CONTINUE:
			openRoundtableHoldScreen(sNewPlayer);
			break;
		case EXIT:
			break;
	}
}