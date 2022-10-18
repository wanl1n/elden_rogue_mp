
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "printer.h"

#include "../config/settings.h"
#include "../utility/colors.h"

void printOption(int nNumber, char strName[]) {
	printf("\n");
	printMultiple(" ", SCREEN_PADDING + OPTION_PADDING);
	printf("[%d] %s", nNumber, strName);
}

void printMultiple(char strText[], int nTimes) {
	int i;
	for(i = 0; i < nTimes; i++)
		printf("%s", strText);
}

void printInputError() {
	colorText(COLOR_PRINTER_ERROR);
	printSystemMessage("Please enter a valid input.");
	resetColors();
}

void printInputTag() {
	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	printf("[INPUT]: ");
}

void printScreenDivider() {
	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	printMultiple("─", SCREEN_WIDTH);
	printf("\n");
}

void printMessage(char strTag[], char strMessage[], int nColor) {
	printf("\n");
	printMultiple(" ", SCREEN_PADDING);
	if(nColor != -1) {
		colorText(nColor);
	}
	printf("[%s]: %s", strTag, strMessage);
	resetColors();
}

void printSystemMessage(char strMessage[]) {
	printMessage("SYSTEM MESSAGE", strMessage, -1);
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
	printMultiple(" ", SCREEN_PADDING + nHeaderPadding);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%s", strHeader);
	printMultiple(" ", HEADER_WIDTH - nSpaces - nLength);
	printf("│\n");

	// Print bottom border.
	printMultiple(" ", SCREEN_PADDING + nHeaderPadding);
	printf("╚");
	printMultiple("═", HEADER_WIDTH);
	printf("╝\n");

	printf("\n");
}