
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PRINTER
#define PRINTER

#define COLOR_PRINTER_ERROR 196

void printOption(int nNumber, char strName[]);

void printMultiple(char strText[], int nTimes);
void printInputError();
void printInputTag();
void printScreenDivider();

void printMessage(char strTag[], char strMessage[], int nColor);
void printSystemMessage(char strMessage[]);
void printHeader(char strHeader[], int nLength);

#endif