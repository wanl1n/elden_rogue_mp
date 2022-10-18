#include "title_screen.h"


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

void openTitleScreen(struct sPlayer sPlayer) {
	displayTitleScreen(0);

	int nInput;

	nInput = scanIntInput(0, 2);
	
	switch(nInput) {
		case START:
			openCharacterCreationScreen(sPlayer);
			break;
		case CONTINUE:
			openRoundtableHoldScreen(sPlayer);
			break;
		case EXIT:
			break;
	}
}