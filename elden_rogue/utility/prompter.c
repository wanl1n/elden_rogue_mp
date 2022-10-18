
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "prompter.h"

#include "printer.h"

void prompt(int nType) {
	switch(nType) {
		case PROMPT_THORNS:
			printMessage("PROMPT", "You got hurt by THORNS!", COLOR_PROMPT_THORNS);
			break;

		case PROMPT_FLOWER:
			printMessage("PROMPT", "You picked up a FLOWER.", COLOR_PROMPT_FLOWER);
			break;

		case PROMPT_EMPTY:
			printMessage("PROMPT", "There's NOTHING there...", -1);
			break;
	}
}
