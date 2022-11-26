#include "../chara_creation_screen.h"
#include "../title_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"
#include "inventory_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

void displaySellShop(int nPrompt, Player* pPlayer, Weapon sWeapon, int nProfit) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\n\t\tInput the index of the weapon you want to sell.");

	printInventoryGrid(pPlayer);

	printOption(0, "BACK");

	switch(nPrompt) {
		case SUCCESSFUL:
			printf("\n\t\tYou sold %s for %d runes.", sWeapon.strWeaponName, nProfit);
			break;
		case UNSUCCESSFUL:
			printSystemMessage("You don't have a weapon at that index.");
			break;
		default:
			break;
	}
}

void openSellScreen(Player* pPlayer) {

	int nInputIndex = 100;
	Weapon* pSelectedWeapon = NULL;
	int nWeaponSRP = 0;

	int nTemp;

	//Getting the price of the weapon.
	Stock* pStockWeaponFromType;
	Stock sStockWeapon;

	displaySellShop(-1, pPlayer, *pSelectedWeapon, 0);

	while (nInputIndex != 0) {

		nInputIndex = scanf("%d", &nInputIndex);
		
		//find the weapon from inventory at the inputted index.
		pSelectedWeapon = findWeapon(nInputIndex, pPlayer);
		
		//if the weapon exists,
		if(pSelectedWeapon != NULL) {

			//get the stock list for that type.
			pStockWeaponFromType = getStocksFromType(nInputIndex); //Array of 4 weapons + their cost.
			//get the weapon from that specific type.
			for(nTemp = 0; nTemp < 4; nTemp++) {
				if (*(pStockWeaponFromType + nTemp)->sWeapon.nWeaponType == pSelectedWeapon->nWeaponType) {
					nWeaponSRP = *(pStockWeaponFromType + nTemp).nCost;
				}
			}

			removeWeaponFromInventory(*pSelectedWeapon, pPlayer);
			pPlayer->nRunes += nWeaponSRP / 2;

			displaySellShop(SUCCESSFUL, pPlayer, *pSelectedWeapon, nWeaponSRP / 2);

		} else {
			displaySellShop(UNSUCCESSFUL, pPlayer, *pSelectedWeapon, 0);
		}
	}

}