#include "title_screen.h"


/*********** User Interface *************/
void displayTitleScreen(int* pPrompt) {
	
	printf("ELDEN ROGUE\n\n",
			"[1] START\n",
			"[2] CONTINUE\n",
			"[0] EXIT\n\n",
			"SYSTEM MESSAGE: ");
	
	switch(*pPrompt) {
		case PROMPT_START:
			printf("Starting game...");
			break;
		case PROMPT_CONTINUE:
			printf("Continuing previously saved progress...");
			break;
		case PROMPT_EXIT:
			printf("Exiting game...");
	}

	sleep(DELAY);
}

void openTitleScreen() {
	displayTitleScreen(0);

	int nInput;

	nInput = scanIntInput(0, 2);
	
	switch(nInput) {
		case START:
			openCharacterCreationScreen();
			break;
		case CONTINUE:
			openRoundtableHoldScreen();
			break;
		case EXIT:
			break;
	}
}