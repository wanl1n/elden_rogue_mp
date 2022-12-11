/**
 * @Author: Candy
 * @Date Created: April 13, 2022
 * @Description:
 * 
 * GDPROG1 and CCPROG1 Machine Project utilty file for AY 21-22.
 * GDPROG2 provided utility file for AY 22-23.
 * Please read the notes below:
 * 
 * FOR WINDOWS USERS, Please run the following in CMD or
 * PowerShell to enable colours.
 *  REG ADD HKCU\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1
 *
 * Answer provided by BrainSlugs83, via StackOverflow:
 *  https://stackoverflow.com/questions/16755142/how-to-make-win32-console-recognize-ansi-vt100-escape-sequences
 * 
 * ALTERNATIVELY, you may set the ENABLE constant to 0 to
 * disable all printed ANSI colors. See colors.h for constant definitions.
 * 
 * More colors here:
 *  https://en.wikipedia.org/wiki/ANSI_escape_code
 */


#include "colors.h"

void resetColors() {
    if(ENABLE) {
        printf("\x1b[0m");
    }
}

void colorText(int nColor) {
    if(ENABLE) {
        printf("\x1b[38;5;%dm", nColor);
    }
}

void colorBackground(int nColor) {
    if(ENABLE) {
        printf("\x1b[48;5;%dm", nColor);
    }
}
