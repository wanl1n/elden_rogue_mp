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