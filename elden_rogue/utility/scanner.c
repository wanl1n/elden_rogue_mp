
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "scanner.h"
#include "printer.h"

int scanIntInput(int nMin, int nMax) {
	int nInput;

	do {
		printInputTag();
		scanf("%d", &nInput);
		printf("\n");

		if(nInput < nMin || nInput > nMax) {
			printInputError();
		}

	} while(nInput < nMin || nInput > nMax);

	return nInput;
}

char scanCharInput(char aValidCharacters[], int nLength) {
	char cInput;

	do {
		printInputTag();
		scanf(" %c", &cInput);
		printf("\n");

		if(!hasCharMatch(cInput, aValidCharacters, nLength)) {
			printInputError();
		}

	} while(!hasCharMatch(cInput, aValidCharacters, nLength));

	return cInput;
}

int hasCharMatch(char cKey, char aList[], int nLength) {
	int i;
	int nMatch;

	nMatch = 0;
	for(i = 0; i < nLength && !nMatch; i++) {
		if(aList[i] == cKey) {
			nMatch = 1;
		}
	}

	return nMatch;
}
