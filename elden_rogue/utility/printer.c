
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "printer.h"

#include "../config/settings.h"
#include "../utility/colors.h"

void printOption(int nNumber, char strName[]) {
	printf("\n");
	
	printMultiple(" ", ((SCREEN_WIDTH - OPTION_WIDTH) / 2)+1);
	printf("┌");
	printMultiple("—", OPTION_WIDTH);
	printf("┐");
	printf("\n");

	printMultiple(" ", ((SCREEN_WIDTH - OPTION_WIDTH) / 2)+1);
	printf("│  %d  ►  %-*.*s │", nNumber, OPTION_WIDTH-9, OPTION_WIDTH-9, strName);
	printf("\n");

	printMultiple(" ", ((SCREEN_WIDTH - OPTION_WIDTH) / 2)+1);
	printf("└");
	printMultiple("—", OPTION_WIDTH);
	printf("┘");
	
}

void printMultiple(char strText[], int nTimes) {
	int i;
	for(i = 0; i < nTimes; i++)
		printf("%s", strText);
}

void printInputError() {
	colorText(COLOR_PRINTER_ERROR);
	printSystemMessage("That's not a valid input.");
	resetColors();
}

void printInputTag() {

	printf("\n");

	// Print bottom border.
	printMultiple(" ", SCREEN_PADDING);
	printf("╚");
	printMultiple("═", SCREEN_WIDTH);
	printf("╝\n\n");

	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("What do you wanna do? ► ");
}

void printScreenDivider() {
	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	printMultiple("─", SCREEN_WIDTH);
	printf("\n");
}

void printMessage(char strTag[], char strMessage[], int nColor) {
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	if(nColor != -1) {
		colorText(nColor);
	}
	printf("%s says ►  %s", strTag, strMessage);
	printf("\n");
	resetColors();
}

void printSystemMessage(char strMessage[]) {
	printMessage("The elder", strMessage, -1);
}

void printHeader(char strHeader[], int nLength) {
	int nSpaces;
	int nHeaderPadding;

	// Compute the left space to center the title box.
	nHeaderPadding = (SCREEN_WIDTH - (HEADER_WIDTH + 2)) / 2;
	nSpaces = (HEADER_WIDTH - nLength) / 2;

	printf("\n");

	// Print top border.
	printMultiple(" ", SCREEN_PADDING + nHeaderPadding);
	printf("╔");
	printMultiple("═", HEADER_WIDTH);
	printf("╗\n");

	// Print center text.
	printMultiple(" ", SCREEN_PADDING);
	printf("╒");
	printMultiple("═", nHeaderPadding - 1);
	printf("╡");
	printMultiple(" ", nSpaces);
	printf("%s", strHeader);
	printMultiple(" ", HEADER_WIDTH - nSpaces - nLength);
	printf("╞");
	printMultiple("═", nHeaderPadding - 1);
	printf("╕\n");

	// Print bottom border.
	printMultiple(" ", SCREEN_PADDING + nHeaderPadding);
	printf("╚");
	printMultiple("═", HEADER_WIDTH);
	printf("╝\n");

	printf("\n");
}