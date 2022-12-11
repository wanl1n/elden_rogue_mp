// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "../roundtable_screen.h" //When Player goes back.
#include "inventory_screen.h" //For altering inventory.
#include "sell_screen.h"//Contains constants for sell screen.

#include "../../driver.h" //Contains all the structure definitions.

#include "../../config/settings.h" //Contains printing settings.


// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/*	openSellScreen		Opens the Sell Screen.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openSellScreen(Player* pPlayer) {

	int nInputIndex = -1;
	int nWeaponCost = 0;
	Slot* pSelectedWeapon = NULL;

	int i;

	//Getting the price of the weapon.
	Stock* pStockOfType;

	Weapon* pPlaceholder = createPlaceholderWeapon();

	displaySellShop(-1, pPlayer, *pPlaceholder, 0);

	while (nInputIndex != 0) {

		printInputTag();
		scanf("%d", &nInputIndex); // Index of the weapon in inventory.
		
		//find the weapon from inventory at the inputted index.
		if (nInputIndex != 0) {
			

			pSelectedWeapon = findWeaponSlot(nInputIndex, pPlayer->pInventory);

			//if the weapon exists,
			if(pSelectedWeapon != NULL) {

				//get the stock list for that type.
				pStockOfType = getStocksFromType(pSelectedWeapon->sWeapon.nWeaponType); //Array of 4 weapons + their cost.
				//get the weapon from that specific type.
				
				for(i = 0; i < 4; i++) {
					if (!strcmp(pSelectedWeapon->sWeapon.strWeaponName, pStockOfType[i].sWeapon.strWeaponName)) 
						nWeaponCost = pStockOfType[i].nCost;
				}

				removeWeapon(pSelectedWeapon, &(pPlayer->pInventory));
				pPlayer->nRunes += nWeaponCost / 2;

				displaySellShop(SUCCESSFUL, pPlayer, pSelectedWeapon->sWeapon, nWeaponCost / 2);

			} else 
				displaySellShop(UNSUCCESSFUL, pPlayer, pSelectedWeapon->sWeapon, 0);
		}
	}

	printf("lol2");
	openRoundTableHoldScreen(pPlayer);
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	createPlaceholderWeapon		Creates an empty instance of a weapon.

	@returns					Returns a Weapon pointer variable. 	   */
Weapon* createPlaceholderWeapon() {

	Weapon* pWeapon = malloc(sizeof(Weapon));

	pWeapon->nWeaponIndex = 0;
	strcpy(pWeapon->strWeaponName, "NONE");

	pWeapon->nWeaponType = 0;

	pWeapon->nDexReq = 0;
	pWeapon->nHP = 0;
	pWeapon->nInt = 0;
	pWeapon->nEnd = 0;
	pWeapon->nStr = 0;
	pWeapon->nFth = 0;

	return pWeapon;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/*	displaySellShop		Displays the sell shop.
	
	@param nPrompt 		An integer variable containing the player's input 
						from the Sell Screen.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param sWeapon		A weapon variable containing the weapon the
						Player sold.
	@param nProfit		An integer variable containing the runes the 
						Player gained from the transaction.

	Pre-condition		nPrompt should be an integer value from 1 or 7.
						pPlayer should be initiated and all members 
						should have a value.	  					
						sWeapon should contain a valid weapon.
						nProfit should be a valid integer value.  	   */
void displaySellShop(int nPrompt, Player* pPlayer, Weapon sWeapon, int nProfit) {
	
	system("cls");

	printHeader("SELL WEAPON", 11);
	
	printf("\n\t\tInput the index of the weapon you want to sell.");

	printInventoryGrid(pPlayer, 1);

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