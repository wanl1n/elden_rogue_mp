#include "../chara_creation_screen.h"
#include "../title_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

void displayBuyShop(Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("		____SHOP____	RUNES: %d\n"
		"[1] SHORT SWORD		$1000 	DEX: 13\n"
		"[2] ROGIER'S RAPIER	$2000 	DEX: 18\n"
		"[3] CODED SWORD		$4000 	DEX: 21\n"
		"[4] NIGHT & FLAME		$8000 	DEX: 25\n"
		"[0] BACK\n\n"
		"INPUT: ", pPlayer->nRunes);
	
}

void openBuyScreen(Player* pPlayer) {
	displayBuyShop(pPlayer);

	int nInputBuy = 100;

	while (nInputBuy != 0) {
		nInputBuy = scanIntInput(0, 4);

		switch(nInputBuy) {
			case :
				break;
		}
	}
}