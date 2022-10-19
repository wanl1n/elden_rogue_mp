#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "windows.h"
#include "unistd.h"

#include "utility/printer.c"
#include "utility/scanner.c"
#include "utility/colors.c"
#include "driver.h"

#include "screens/title_screen.c"
#include "screens/chara_creation_screen.c"

int main() {

	sPlayer* sNewPlayer;

	resetColors();
	openTitleScreen(sNewPlayer);

	return 0;
}