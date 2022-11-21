
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                        DO NOT EDIT THIS SCRIPT.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COLORS
#define COLORS

#define ENABLE   1

#define COLOR_TILE_EMPTY        231
#define COLOR_TILE_OUT          234
#define COLOR_TILE_FAST_TRAVEL  40
#define COLOR_TILE_DOOR_NEXT    220
#define COLOR_TILE_DOOR_BACK    208
#define COLOR_TILE_SPECIAL      51
#define COLOR_TILE_BOSS         196
#define COLOR_TILE_CREDITS      180
#define COLOR_TILE_PLAYER       82

void resetColors();
void colorText(int nColor);
void colorBackground(int nColor);

#endif
